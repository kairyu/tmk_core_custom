/*
Copyright 2016 Kai Ryu <kai1103@gmail.com>

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

#ifndef RGB_LED_H
#define RGB_LED_H

#include <stdint.h>
#include <stdbool.h>
#ifdef RGB_LED_WS2812
#include "avr/light_ws2812.h"
#endif

typedef union {
    uint8_t raw;
    struct {
        uint8_t level  :7;
        bool    enable :1;
    };
} rgb_led_config_t;

typedef struct {
    uint16_t h;
    uint8_t s;
    uint8_t b;
} hsb_t;

enum {
    RGB_LED_OFF = 0,
    RGB_LED_RED,
    RGB_LED_YELLOW,
    RGB_LED_GREEN,
    RGB_LED_CYAN,
    RGB_LED_BLUE,
    RGB_LED_MAGENTA,
    RGB_LED_WHITE,
    RGB_LED_FADE,
    RGB_LED_RAINBOW,
    RGB_LED_LEVELS = RGB_LED_RAINBOW
};

const rgb_led_config_t rgb_led_config_default;
const uint8_t rgb_led_brightness_default;

#ifndef RGB_LED_MAX_COUNT
#define RGB_LED_MAX_COUNT 32
#endif

#define RGB_LED_BRIGHTNESS_MIN 15
#define RGB_LED_BRIGHTNESS_MAX 255

#ifndef RGB_LED_CONFIG_DEFAULT_LEVEL
#define RGB_LED_CONFIG_DEFAULT_LEVEL RGB_LED_OFF
#endif

#ifndef RGB_LED_CONFIG_DEFAULT_ENABLE
#define RGB_LED_CONFIG_DEFAULT_ENABLE false
#endif

#ifndef RGB_LED_BRIGHTNESS_DEFAULT_VALUE
#define RGB_LED_BRIGHTNESS_DEFAULT_VALUE RGB_LED_BRIGHTNESS_MIN
#endif

#ifdef RGB_LED_ENABLE
void rgb_led_init(void);
void rgb_led_toggle(void);
void rgb_led_on(void);
void rgb_led_off(void);
void rgb_led_decrease(void);
void rgb_led_increase(void);
void rgb_led_step(void);
void rgb_led_set_count(uint8_t count);
void rgb_led_set_brightness(uint8_t brightness, bool save);
void rgb_led_decrease_brightness(uint8_t decrement, bool save);
void rgb_led_increase_brightness(uint8_t increment, bool save);
void rgb_led_fading(void);
void rgb_led_setleds(rgb_t *colors, uint8_t count);
#else
#define rgb_led_init()
#define rgb_led_toggle()
#define rgb_led_on()
#define rgb_led_off()
#define rgb_led_decrease()
#define rgb_led_increase()
#define rgb_led_step()
#define rgb_led_set_count()
#define rgb_led_set_brightness()
#define rgb_led_decrease_brightness()
#define rgb_led_increase_brightness()
#define rgb_led_fading()
#define rgb_led_setleds()
#endif

#endif
