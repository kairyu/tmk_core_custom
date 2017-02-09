/*
Copyright 2016 Chen Yang <adamyoung.2333@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "rawhid.h"
#include "rawhid_command.h"
#include "debug.h"
#include "lufa.h"
#include "descriptor.h"
#include "console_ring_buffer.h"

/*
    proocess data from CONSOLE_EP_OUT endpoint
    data format:
    command_id length payload crc
    available command id:
    0x10 write eep
    0x21 debug print
*/

void receiveRawHidData(void)
{
    uint8_t ep = Endpoint_GetCurrentEndpoint();
    Endpoint_SelectEndpoint(CONSOLE_OUT_EPNUM);
    /* Check to see if a packet has been sent from the host */
    if (Endpoint_IsOUTReceived())
    {
        /* Check to see if the packet contains data */
        if (Endpoint_IsReadWriteAllowed())
        {
            /* Create a temporary buffer to hold the read in report from the host */
            uint8_t ConsoleData[CONSOLE_EPSIZE];

            /* Read Console Report Data */
            Endpoint_Read_Stream_LE(&ConsoleData, sizeof(ConsoleData), NULL);

            /* Process Console Report Data */
            rawhid_process_console_data(ConsoleData);
        }

        /* Finalize the stream transfer to send the last packet */
        Endpoint_ClearOUT();
    }

    Endpoint_SelectEndpoint(ep);

}

bool rawhid_process_console_data(uint8_t console_data[])
{
    //process raw data
    uint8_t command_id = console_data[0];
    uint8_t length = console_data[1];
    uint8_t payload[length];
    uint8_t has_crc_check = command_id >> CRC_CHECK_POS;
    uint8_t more_packet = length >> MORE_PACKET_POS;

    command_id &= MORE_PACKET_MASK;
    length &= CRC_CHECK_MASK;
    //assemble crc data
    uint16_t crc = 0;
    if(has_crc_check) {
        crc = (console_data[length + 3] << 8) + (console_data[length + 3]);
    } else {
        crc = 0;
    }

    for(uint8_t i=2, j=0; j<length; i++,j++) {
        payload[j] = console_data[i];
    }

    rawhid_data_t console_data_body;
    console_data_body.command_id = command_id;
    console_data_body.more_packet = more_packet;
    console_data_body.length = length;
    console_data_body.payload = payload;
    console_data_body.has_crc_check = has_crc_check;
    console_data_body.crc = crc;

    if(!rawhid_crc_validate(console_data, crc)) {
        return false;
    }
    //for further process
    rawhid_command_parse_hid_command(console_data_body);

    return true;
}

void rawhid_send_in_data(uint8_t command_id, uint8_t has_crc_check , uint8_t payload_length, uint8_t more_packet,
                        uint8_t payload[], uint8_t crc_l, uint8_t crc_h)
{
    uint8_t current_ep =  Endpoint_GetCurrentEndpoint();
    Endpoint_SelectEndpoint(CONSOLE_IN_EPNUM);

    if (!Endpoint_IsEnabled() || !Endpoint_IsConfigured()) {
        Endpoint_SelectEndpoint(current_ep);
        return;
    }

    //if(Endpoint_IsINReady()) {
        //Endpoint_ClearIN();
    //}

    if(Endpoint_IsReadWriteAllowed()) {
        Endpoint_Write_8((has_crc_check << CRC_CHECK_POS) + command_id);
        Endpoint_Write_8((more_packet << MORE_PACKET_POS) + payload_length);

        for(int i=0; i<payload_length; i++) {
            Endpoint_Write_8(payload[i]);
        }

        Endpoint_Write_8(crc_l);
        Endpoint_Write_8(crc_h);

        while(Endpoint_IsReadWriteAllowed()) {
            Endpoint_Write_8(0);
        }

        if (Endpoint_IsINReady()) {
            Endpoint_ClearIN();
        }
    }

    Endpoint_SelectEndpoint(current_ep);

}

int rawhid_send_char(uint8_t c, uint8_t send_timeout)
{
    static bool timeouted = false;

    if (USB_DeviceState != DEVICE_STATE_Configured)
        return -1;

    uint8_t ep = Endpoint_GetCurrentEndpoint();
    Endpoint_SelectEndpoint(CONSOLE_IN_EPNUM);
    if (!Endpoint_IsEnabled() || !Endpoint_IsConfigured()) {
        goto ERROR_EXIT;
    }

    if (timeouted && !Endpoint_IsReadWriteAllowed()) {

        goto ERROR_EXIT;
    }

    timeouted = false;

    uint8_t timeout = send_timeout;
    while (!Endpoint_IsReadWriteAllowed()) {
        if (USB_DeviceState != DEVICE_STATE_Configured) {
            goto ERROR_EXIT;
        }
        if (Endpoint_IsStalled()) {
            goto ERROR_EXIT;
        }
        if (!(timeout--)) {
            timeouted = true;
            goto ERROR_EXIT;
        }
        _delay_ms(1);
    }

    rbuf_enqueue(c);

    Endpoint_SelectEndpoint(ep);
    return 0;
ERROR_EXIT:
    Endpoint_SelectEndpoint(ep);
    return -1;
}

//DPG2 or other hash algorithm
bool rawhid_crc_validate(uint8_t console_data[], uint16_t crc)
{
    //TODO: implement crc validation
    return true;
}
