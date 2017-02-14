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

#ifndef RAWHID_H
#define RAWHID_H

#include <stdint.h>
#include <stdbool.h>

#define CONSOLE_EP_SIZE 32
#define CRC_CHECK_MASK 0b01111111
#define MORE_PACKET_MASK 0b01111111
#define CRC_CHECK_POS 7
#define MORE_PACKET_POS 7
#define CONSOLE_IN_BUFFER_SIZE 64

void receiveRawHidData(void);
bool rawhid_process_console_data(uint8_t console_data[]);
bool rawhid_crc_validate(uint8_t console_data[], uint16_t crc);
void rawhid_send_in_data(uint8_t command_id, uint8_t has_crc_check , uint8_t payload_length, uint8_t more_packet,
                    uint8_t payload[], uint8_t crc_l, uint8_t crc_h);
void rawhid_send_ack_nack(uint8_t command_id,  uint8_t data_length, uint8_t has_addtional_info,
                    uint8_t ack, uint8_t info[]);
int rawhid_send_char(uint8_t c, uint8_t send_timeout);

#endif
