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
#ifndef HID_COMMAND_H
#define HID_COMMAND_H

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint8_t  command_id;
    uint8_t  length;
    uint8_t  *payload;
    uint8_t  more_packet;
    uint8_t  has_crc_check;
    uint16_t crc;
} rawhid_data_t;

enum hid_command_id
{
    RAWHID_COMMAND_EEP_FILE = 0x10,
    RAWHID_COMMAND_DEBUG_PRINT = 0x21
};

bool rawhid_command_parse_hid_command(rawhid_data_t rawhid_data);
bool rawhid_command_parse_eep_file(rawhid_data_t rawhid_data);
void rawhid_command_print_console_data(rawhid_data_t rawhid_data);

#endif
