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

#ifdef LEDMAP_V2
#include "avr/ledmap_avr.h"
#endif
#include "ledmap.h"
#include "ledmap_in_eeprom.h"
#include "led.h"
#include "hook.h"
#include "debug.h"
#ifdef SOFTPWM_LED_ENABLE
#include "softpwm_led.h"
#endif
#ifdef RGB_LED_ENABLE
#include "rgb_led.h"
#endif

static led_state_t led_state_last = 0;
static led_binding_t usb_led_binding = 0;
static led_binding_t default_layer_binding = 0;
static led_binding_t layer_binding = 0;
static led_binding_t backlight_binding = 0;
static led_binding_t reverse_binding = 0;
static led_binding_t rgb_led_binding = 0;
static led_pack_t active_level = 0;
#ifdef SOFTPWM_LED_ENABLE
extern uint8_t softpwm_state;
extern led_pack_t softpwm_led_state;
#endif
#ifdef RGB_LED_ENABLE
static uint8_t rgb_led_count[LED_COUNT] = {0};
#endif

static void update_led_state(led_state_t state, uint8_t force);

#ifdef LEDMAP_V2
void ledmap_led_high(uint8_t index);
void ledmap_led_low(uint8_t index);

void ledmap_led_init(void)
{
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        if ((rgb_led_binding & LED_BIT(i)) == 0) {
            ledmap_led_off(i);
        }
    }
    #if LED_COUNT >= 1
        LED1_OUT();
    #endif
    #if LED_COUNT >= 2
        LED2_OUT();
    #endif
    #if LED_COUNT >= 3
        LED3_OUT();
    #endif
    #if LED_COUNT >= 4
        LED4_OUT();
    #endif
    #if LED_COUNT >= 5
        LED5_OUT();
    #endif
    #if LED_COUNT >= 6
        LED6_OUT();
    #endif
    #if LED_COUNT >= 7
        LED7_OUT();
    #endif
    #if LED_COUNT >= 8
        LED8_OUT();
    #endif
}

inline
void ledmap_led_on(uint8_t index)
{
    if (active_level & LED_BIT(index)) {
        ledmap_led_high(index);
    }
    else {
        ledmap_led_low(index);
    }
}

inline
void ledmap_led_off(uint8_t index)
{
    if (active_level & LED_BIT(index)) {
        ledmap_led_low(index);
    }
    else {
        ledmap_led_high(index);
    }
}

inline
void ledmap_led_high(uint8_t index) {
    switch (index) {
    #if LED_COUNT >= 1
        case 0: LED1_HI(); return;
    #endif
    #if LED_COUNT >= 2
        case 1: LED2_HI(); return;
    #endif
    #if LED_COUNT >= 3
        case 2: LED3_HI(); return;
    #endif
    #if LED_COUNT >= 4
        case 3: LED4_HI(); return;
    #endif
    #if LED_COUNT >= 5
        case 4: LED5_HI(); return;
    #endif
    #if LED_COUNT >= 6
        case 5: LED6_HI(); return;
    #endif
    #if LED_COUNT >= 7
        case 6: LED7_HI(); return;
    #endif
    #if LED_COUNT >= 8
        case 7: LED8_HI(); return;
    #endif
    }
}

inline
void ledmap_led_low(uint8_t index) {
    switch (index) {
    #if LED_COUNT >= 1
        case 0: LED1_LO(); return;
    #endif
    #if LED_COUNT >= 2
        case 1: LED2_LO(); return;
    #endif
    #if LED_COUNT >= 3
        case 2: LED3_LO(); return;
    #endif
    #if LED_COUNT >= 4
        case 3: LED4_LO(); return;
    #endif
    #if LED_COUNT >= 5
        case 4: LED5_LO(); return;
    #endif
    #if LED_COUNT >= 6
        case 5: LED6_LO(); return;
    #endif
    #if LED_COUNT >= 7
        case 6: LED7_LO(); return;
    #endif
    #if LED_COUNT >= 8
        case 7: LED8_LO(); return;
    #endif
    }
}

#endif

void ledmap_init(void)
{
    uint8_t rgb_led_max_count = 0;
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        ledmap_t ledmap = ledmap_get_code(i);
#ifdef RGB_LED_ENABLE
        if (ledmap.rgb) {
            LED_BIT_SET(rgb_led_binding, i);
            rgb_led_count[i] = ledmap.param;
            if (rgb_led_count[i] > rgb_led_max_count) {
                rgb_led_max_count = rgb_led_count[i];
            }
            continue;
        }
#endif
        if (ledmap.active_level) {
            LED_BIT_SET(active_level, i);
        }
        if (ledmap.reverse) {
            LED_BIT_SET(reverse_binding, i);
        }
        if (ledmap.backlight) {
            LED_BIT_SET(backlight_binding, i);
        }
        switch (ledmap.binding) {
            case LEDMAP_BINDING_DEFAULT_LAYER:
                LED_BIT_SET(default_layer_binding, i);
                break;
            case LEDMAP_BINDING_LAYER:
                LED_BIT_SET(layer_binding, i);
                break;
            case LEDMAP_BINDING_USB_LED:
                LED_BIT_SET(usb_led_binding, i);
                break;
        }
    }
    ledmap_led_init();
    update_led_state(0, 1);
#ifdef RGB_LED_ENABLE
    rgb_led_set_count(rgb_led_max_count);
#endif
}

void hook_keyboard_leds_change(uint8_t usb_led)
{
    if (usb_led_binding) {
        led_state_t led_state = led_state_last;
        for (uint8_t i = 0; i < LED_COUNT; i++) {
            if (usb_led_binding & LED_BIT(i)) {
                uint8_t param = ledmap_get_code(i).param;
                (usb_led & (1 << param)) ? LED_BIT_SET(led_state, i) : LED_BIT_CLEAR(led_state, i);
            }
        }
        update_led_state(led_state, 0);
    }
}

#ifndef NO_ACTION_LAYER
void hook_default_layer_change(uint32_t state)
{
    if (default_layer_binding) {
        led_state_t led_state = led_state_last;
        for (uint8_t i = 0; i < LED_COUNT; i++) {
            if (default_layer_binding & LED_BIT(i)) {
                uint8_t param = ledmap_get_code(i).param;
                (state & (1UL << param)) ? LED_BIT_SET(led_state, i) : LED_BIT_CLEAR(led_state, i);
            }
        }
        update_led_state(led_state, 0);
    }
}

void hook_layer_change(uint32_t state)
{
    if (layer_binding) {
        led_state_t led_state = led_state_last;
        for (uint8_t i = 0; i < LED_COUNT; i++) {
            if (layer_binding & LED_BIT(i)) {
                uint8_t param = ledmap_get_code(i).param;
                (state & (1UL << param)) ? LED_BIT_SET(led_state, i) : LED_BIT_CLEAR(led_state, i);
            }
        }
        update_led_state(led_state, 0);
    }
}
#endif

#ifdef SOFTPWM_LED_ENABLE
void softpwm_led_init(void)
{
}

void softpwm_led_on(uint8_t index)
{
    if (backlight_binding & LED_BIT(index)) {
        ledmap_led_on(index);
    }
}

void softpwm_led_off(uint8_t index)
{
    if (backlight_binding & LED_BIT(index)) {
        ledmap_led_off(index);
    }
}

void softpwm_state_change(uint8_t state)
{
    if (backlight_binding) {
        update_led_state(led_state_last, 1);
    }
}
#endif

#ifdef RGB_LED_ENABLE
void rgb_led_setleds(rgb_t *colors, uint8_t count)
{
#if 1
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        if (rgb_led_binding & LED_BIT(i)) {
            switch (i) {
            #if LED_COUNT >= 1
                case 0: LED1_RGB(colors, rgb_led_count[0]); break;
            #endif
            #if LED_COUNT >= 2
                case 1: LED2_RGB(colors, rgb_led_count[1]); break;
            #endif
            #if LED_COUNT >= 3
                case 2: LED3_RGB(colors, rgb_led_count[2]); break;
            #endif
            #if LED_COUNT >= 4
                case 3: LED4_RGB(colors, rgb_led_count[3]); break;
            #endif
            #if LED_COUNT >= 5
                case 4: LED5_RGB(colors, rgb_led_count[4]); break;
            #endif
            #if LED_COUNT >= 6
                case 5: LED6_RGB(colors, rgb_led_count[5]); break;
            #endif
            #if LED_COUNT >= 7
                case 6: LED7_RGB(colors, rgb_led_count[6]); break;
            #endif
            #if LED_COUNT >= 8
                case 7: LED8_RGB(colors, rgb_led_count[7]); break;
            #endif
            }
        }
    }
#endif
}
#endif

void update_led_state(led_state_t state, uint8_t force)
{
    led_state_t diff = led_state_last ^ state;
    if (force || diff) {
        for (uint8_t i = 0; i < LED_COUNT; i++) {
#ifdef RGB_LED_ENABLE
            if (rgb_led_binding & LED_BIT(i)) {
                continue;
            }
#endif
#ifdef SOFTPWM_LED_ENABLE
            if ((softpwm_led_state & LED_BIT(i)) && (backlight_binding & LED_BIT(i))) {
                continue;
            }
#endif
            if (force || diff & LED_BIT(i)) {
                if ((state ^ reverse_binding) & LED_BIT(i)) {
                    ledmap_led_on(i);
                }
                else {
                    ledmap_led_off(i);
                }
            }
        }
        led_state_last = state;
    }
}
