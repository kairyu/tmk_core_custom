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
#include "rawhid_command.h"
#include <avr/eeprom.h>
#include "debug.h"

bool rawhid_command_parse_hid_command(rawhid_data_t rawhid_data)
{
    switch(rawhid_data.command_id) {
        case RAWHID_COMMAND_EEP_FILE:
            rawhid_command_parse_eep_file(rawhid_data);
            break;

        default:
            print("command id is invalid\n");
            break;
    }
    return true;
}

bool rawhid_command_parse_eep_file(rawhid_data_t rawhid_data)
{
    rawhid_command_print_rawhid_data(rawhid_data);

    static uint16_t address = 0x0;
    static bool more_packet = false;
    uint8_t real_data_pos = 0;

    if(rawhid_data.more_packet && (!more_packet)) {
        address = (rawhid_data.payload[1] << 8) + rawhid_data.payload[0];
        real_data_pos = 2;
        more_packet = true;
    } else if(!rawhid_data.more_packet && more_packet) {
        more_packet = false;
    } else if(!rawhid_data.more_packet && !more_packet) {
        address = (rawhid_data.payload[1] << 8) + rawhid_data.payload[0];
        real_data_pos = 2;
    }

    //write data
    for(uint8_t i=0; i<rawhid_data.length-real_data_pos; i++) {
        eeprom_update_byte((uint8_t *)address, rawhid_data.payload[i+real_data_pos]);
        address++;
    }
    return true;
}

void rawhid_command_print_rawhid_data(rawhid_data_t rawhid_data)
{
    print("======= data =======\n");
    print("command id: ");
    phex(rawhid_data.command_id);
    print("\n");
    print("length: ");
    phex(rawhid_data.length);
    print("\n");
    print("more packet: ");
    phex(rawhid_data.more_packet);
    print("\n");
    print("has CRC: ");
    phex(rawhid_data.has_crc_check);
    print("\n");
    print("data: ");
    for(uint8_t i=0; i<rawhid_data.length; i++) {
        phex(rawhid_data.payload[i]);
        print(" ");
    }
    print("\n");
    print("====================\n");
}
