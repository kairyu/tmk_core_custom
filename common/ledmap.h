/*
Copyright 2017 Kai Ryu <kai1103@gmail.com>

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

#ifndef LEDMAP_H
#define LEDMAP_H

#include "stdint.h"
#include "stdbool.h"
#include "led.h"

typedef led_pack_t led_state_t;
typedef led_pack_t led_binding_t;

enum ledmap_binding {
    LEDMAP_BINDING_NO = 0,
    LEDMAP_BINDING_DEFAULT_LAYER,
    LEDMAP_BINDING_LAYER,
    LEDMAP_BINDING_USB_LED
};

enum ledmap_usb_led {
    LEDMAP_USB_LED_NUM_LOCK = 0,
    LEDMAP_USB_LED_CAPS_LOCK,
    LEDMAP_USB_LED_SCROLL_LOCK,
    LEDMAP_USB_LED_COMPOSE,
    LEDMAP_USB_LED_KANA,
};

enum ledmap_active_level {
    LEDMAP_ACTIVE_LEVEL_LOW = 0,
    LEDMAP_ACTIVE_LEVEL_HIGH
};

typedef union {
    uint16_t code;
    struct {
        uint8_t param:      8;
        uint8_t binding:    4;
        bool reverse:       1;
        bool backlight:     1;
        bool active_level:  1;
        bool rgb:           1;
    };
} ledmap_t;

#define LEDMAP_DEFAULT_LAYER(layer) (LEDMAP_BINDING_DEFAULT_LAYER<<8 | layer)
#define LEDMAP_LAYER(layer)         (LEDMAP_BINDING_LAYER<<8 | layer )
#define LEDMAP_NUM_LOCK             (LEDMAP_BINDING_USB_LED<<8 | LEDMAP_USB_LED_NUM_LOCK)
#define LEDMAP_CAPS_LOCK            (LEDMAP_BINDING_USB_LED<<8 | LEDMAP_USB_LED_CAPS_LOCK)
#define LEDMAP_SCROLL_LOCK          (LEDMAP_BINDING_USB_LED<<8 | LEDMAP_USB_LED_SCROLL_LOCK)
#define LEDMAP_REVERSE              (1<<12)
#define LEDMAP_BACKLIGHT            (1<<13)
#define LEDMAP_ACTIVE_LEVEL         (1<<14)
#define LEDMAP_ACTIVE_LOW           (LEDMAP_ACTIVE_LEVEL_LOW<<14)
#define LEDMAP_ACTIVE_HIGH          (LEDMAP_ACTIVE_LEVEL_HIGH<<14)
#define LEDMAP_RGB_LED              (1<<15)
#define LEDMAP_RGB_LED_COUNT(count) (count & 0xFF)

void ledmap_init(void);

#ifdef LEDMAP_ENABLE
ledmap_t ledmap_get_code(uint8_t index);
void ledmap_led_init(void);
void ledmap_led_on(uint8_t index);
void ledmap_led_off(uint8_t index);
#else
#define ledmap_get_code()
#define ledmap_led_init()
#define ledmap_led_on()
#define ledmap_led_off()
#endif

#endif
