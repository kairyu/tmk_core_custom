/*
 * light weight WS2812 lib include
 *
 * Version 2.3  - Nev 29th 2015
 * Author: Tim (cpldcpu@gmail.com) 
 *
 * Please do not change this file! All configuration is handled in "ws2812_config.h"
 *
 * License: GNU GPL v2 (see License.txt)
 +
 */ 

#ifndef LIGHT_WS2812_H_
#define LIGHT_WS2812_H_

#include <stdint.h>

typedef struct { uint8_t g; uint8_t r; uint8_t b; } rgb_t;

#ifdef WS2812_USE_PORTA
void ws2812_setleds_PORTA(rgb_t *ledarray, uint16_t number_of_leds, uint8_t pinmask);
#else
#define ws2812_setleds_PORTA()
#endif

#ifdef WS2812_USE_PORTB
void ws2812_setleds_PORTB(rgb_t *ledarray, uint16_t number_of_leds, uint8_t pinmask);
#else
#define ws2812_setleds_PORTB()
#endif

#ifdef WS2812_USE_PORTC
void ws2812_setleds_PORTC(rgb_t *ledarray, uint16_t number_of_leds, uint8_t pinmask);
#else
#define ws2812_setleds_PORTC()
#endif

#ifdef WS2812_USE_PORTD
void ws2812_setleds_PORTD(rgb_t *ledarray, uint16_t number_of_leds, uint8_t pinmask);
#else
#define ws2812_setleds_PORTD()
#endif

#ifdef WS2812_USE_PORTE
void ws2812_setleds_PORTE(rgb_t *ledarray, uint16_t number_of_leds, uint8_t pinmask);
#else
#define ws2812_setleds_PORTE()
#endif

#ifdef WS2812_USE_PORTF
void ws2812_setleds_PORTF(rgb_t *ledarray, uint16_t number_of_leds, uint8_t pinmask);
#else
#define ws2812_setleds_PORTF()
#endif

#endif /* LIGHT_WS2812_H_ */
