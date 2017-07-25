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

#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "eeconfig.h"
#include "softpwm_led.h"
#include "backlight.h"
#include "rgb_led.h"
#include "debug.h"

#ifdef RGB_LED_ENABLE

volatile static uint8_t rgb_led_fading_enable = 0;
static uint8_t rgb_led_initialized = 0;
const rgb_led_config_t rgb_led_config_default = {
    .level = RGB_LED_CONFIG_DEFAULT_LEVEL,
    .enable = RGB_LED_CONFIG_DEFAULT_ENABLE
};
const uint8_t rgb_led_brightnes_default = RGB_LED_BRIGHTNESS_DEFAULT_VALUE;
static rgb_led_config_t rgb_led_config;
static rgb_t rgb_led_colors[RGB_LED_MAX_COUNT];
static hsb_t rgb_led_hsb;
static uint8_t rgb_led_brightness = RGB_LED_BRIGHTNESS_MIN;
static uint8_t rgb_led_count = RGB_LED_MAX_COUNT;
static uint8_t rgb_led_rainbow = 0;

static void rgb_led_set_level(uint8_t level);
static void rgb_led_refresh(void);
static void hsb_to_rgb(uint16_t hue, uint8_t saturation, uint8_t brightness, rgb_t *rgb);

void rgb_led_init(void)
{
    /* Initialize */
    rgb_led_hsb.h = 0;
    rgb_led_hsb.s = 255;
    rgb_led_hsb.b = RGB_LED_BRIGHTNESS_MIN;

    /* Read config */
    rgb_led_config.raw = eeconfig_read_rgb_led();
    rgb_led_brightness = eeconfig_read_rgb_led_brightness();
    if (rgb_led_brightness > RGB_LED_BRIGHTNESS_MAX) {
        rgb_led_brightness = RGB_LED_BRIGHTNESS_MAX;
    }
    else if (rgb_led_brightness < RGB_LED_BRIGHTNESS_MIN) {
        rgb_led_brightness = RGB_LED_BRIGHTNESS_MIN;
    }

    /* Set LEDs */
    if (rgb_led_config.enable) {
        rgb_led_set_level(rgb_led_config.level);
        rgb_led_set_level(rgb_led_config.level); /* twice */
    }
    else {
        rgb_led_set_level(RGB_LED_OFF);
        rgb_led_set_level(RGB_LED_OFF); /* twice */
    }

    rgb_led_initialized = 1;
}

void rgb_led_toggle(void)
{
    if (rgb_led_config.enable) {
        rgb_led_off();
    }
    else {
        rgb_led_on();
    }
}

void rgb_led_on(void)
{
    rgb_led_config.enable = 1;
    if (rgb_led_config.level == RGB_LED_OFF) {
        rgb_led_config.level = RGB_LED_RED;
    }
    rgb_led_set_level(rgb_led_config.level);
    eeconfig_write_rgb_led(rgb_led_config.raw);
}

void rgb_led_off(void)
{
    rgb_led_config.enable = 0;
    rgb_led_set_level(RGB_LED_OFF);
    eeconfig_write_rgb_led(rgb_led_config.raw);
}

void rgb_led_decrease(void)
{
    if(rgb_led_config.level > 0) {
        rgb_led_config.level--;
        rgb_led_config.enable = (rgb_led_config.level != 0);
        eeconfig_write_rgb_led(rgb_led_config.raw);
    }
    rgb_led_set_level(rgb_led_config.level);
}

void rgb_led_increase(void)
{
    if(rgb_led_config.level < RGB_LED_LEVELS) {
        rgb_led_config.level++;
        rgb_led_config.enable = 1;
        eeconfig_write_rgb_led(rgb_led_config.raw);
    }
    rgb_led_set_level(rgb_led_config.level);
}

void rgb_led_step(void)
{
    rgb_led_config.level++;
    if(rgb_led_config.level > RGB_LED_LEVELS)
    {
        rgb_led_config.level = 0;
    }
    rgb_led_config.enable = (rgb_led_config.level != 0);
    eeconfig_write_rgb_led(rgb_led_config.raw);
    rgb_led_set_level(rgb_led_config.level);
}

void rgb_led_set_level(uint8_t level)
{
    dprintf("RGB LED Level: %d\n", level);
    if (level == RGB_LED_OFF) {
        rgb_led_hsb.b = 0;
    }
    else {
        rgb_led_hsb.b = rgb_led_brightness;
    }
    if (level <= RGB_LED_WHITE) {
        rgb_led_fading_enable = 0;
        rgb_led_rainbow = 0;
        if (level != RGB_LED_OFF) {
            if (level == RGB_LED_WHITE) {
                rgb_led_hsb.s = 0;
            }
            else {
                rgb_led_hsb.h = (level - 1) * 128;
                rgb_led_hsb.s = 255;
            }
        }
        rgb_led_refresh();
    }
    else {
        rgb_led_hsb.s = 255;
        rgb_led_fading_enable = 1;
        rgb_led_rainbow = (level >= RGB_LED_RAINBOW) ? 1 : 0;
    }
}

void rgb_led_set_count(uint8_t count)
{
    if (count > RGB_LED_MAX_COUNT) {
        rgb_led_count = RGB_LED_MAX_COUNT;
    }
    else {
        rgb_led_count = count;
    }
    if (rgb_led_initialized && rgb_led_config.enable) {
        rgb_led_refresh();
    }
}

void rgb_led_set_brightness(uint8_t brightness, bool save)
{
    if (rgb_led_initialized) {
        if (brightness > RGB_LED_BRIGHTNESS_MAX) {
            rgb_led_brightness = RGB_LED_BRIGHTNESS_MAX;
        }
        else if (brightness < RGB_LED_BRIGHTNESS_MIN) {
            rgb_led_brightness = RGB_LED_BRIGHTNESS_MIN;
        }
        else {
            rgb_led_brightness = brightness;
        }

        if (save) {
            eeconfig_write_rgb_led_brightness(rgb_led_brightness);
        }

        if (rgb_led_config.enable) {
            rgb_led_hsb.b = rgb_led_brightness;
            rgb_led_refresh();
        }
    }
}

void rgb_led_decrease_brightness(uint8_t decrement, bool save)
{
    uint8_t brightness = rgb_led_brightness;
    if (brightness - RGB_LED_BRIGHTNESS_MIN < decrement) {
        brightness = RGB_LED_BRIGHTNESS_MIN;
    }
    else {
        brightness -= decrement;
    }
    rgb_led_set_brightness(brightness, save);
}

void rgb_led_increase_brightness(uint8_t increment, bool save)
{
    uint8_t brightness = rgb_led_brightness;
    if (brightness > RGB_LED_BRIGHTNESS_MAX - increment) {
        brightness = RGB_LED_BRIGHTNESS_MAX;
    }
    else {
        brightness += increment;
    }
    rgb_led_set_brightness(brightness, save);
}

void rgb_led_refresh(void)
{
    rgb_t rgb;
    uint16_t hue;
    uint8_t i;
    if (rgb_led_rainbow) {
        for (i = 0; i < rgb_led_count; i++) {
            hue = rgb_led_hsb.h + (768 / rgb_led_count) * i;
            hsb_to_rgb(hue, rgb_led_hsb.s, rgb_led_hsb.b, &rgb);
            rgb_led_colors[i] = rgb;
        }
    }
    else {
        hsb_to_rgb(rgb_led_hsb.h, rgb_led_hsb.s, rgb_led_hsb.b, &rgb);
        for (i = 0; i < rgb_led_count; i++) {
            rgb_led_colors[i] = rgb;
        }
    }
    rgb_led_setleds(rgb_led_colors, rgb_led_count);
}

/*
 * original code: https://blog.adafruit.com/2012/03/14/constant-brightness-hsb-to-rgb-algorithm/
 */
void hsb_to_rgb(uint16_t hue, uint8_t saturation, uint8_t brightness, rgb_t *rgb)
{
    uint8_t temp[5];
    uint8_t n = (hue >> 8) % 3;
    uint8_t x = ((((hue & 255) * saturation) >> 8) * brightness) >> 8;
    uint8_t s = ((256 - saturation) * brightness) >> 8;
    temp[0] = temp[3] = s;
    temp[1] = temp[4] = x + s;
    temp[2] = brightness - x;
    rgb->r = temp[n + 2];
    rgb->g = temp[n + 1];
    rgb->b = temp[n];
}

void rgb_led_fading(void)
{
    static uint8_t step = 0;
    static uint16_t hue = 0;
    if (rgb_led_fading_enable) {
        if (++step > rgb_led_fading_enable) {
            step = 0;
            rgb_led_hsb.h = hue;
            rgb_led_refresh();
            if (++hue >= 768) {
                hue = 0;
            }
        }
    }
}

#endif
