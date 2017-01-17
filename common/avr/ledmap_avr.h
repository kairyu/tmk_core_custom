#ifndef LEDMAP_AVR_H
#define LEDMAP_AVR_H

#include <avr/io.h>

#define CONCAT(a,b) a##b
#define CONCAT_EXP(a,b) CONCAT(a,b)

#define LEDMAP_PORTA 0
#define LEDMAP_PORTB 0
#define LEDMAP_PORTC 0
#define LEDMAP_PORTD 0
#define LEDMAP_PORTE 0
#define LEDMAP_PORTF 0
#undef A
#undef B
#undef C
#undef D
#undef E
#undef F
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5

#if LED_COUNT >= 1
    #if defined(LED1_PORT) && defined(LED1_BIT)
        #define LED1_PORT_ CONCAT_EXP(PORT,LED1_PORT)
        #define LED1_OUT() (_SFR_IO8(_SFR_IO_ADDR(LED1_PORT_)-1) |=  (1<<LED1_BIT))
        #define LED1_HI()  (_SFR_IO8(_SFR_IO_ADDR(LED1_PORT_))   |=  (1<<LED1_BIT))
        #define LED1_LO()  (_SFR_IO8(_SFR_IO_ADDR(LED1_PORT_))   &= ~(1<<LED1_BIT))
        #define LED1_RGB(a,b) CONCAT_EXP(ws2812_setleds_PORT,LED1_PORT)(a,b,(1<<LED1_BIT))
        #if LED1_PORT == A
            #undef  LEDMAP_PORTA
            #define LEDMAP_PORTA 1
        #endif
        #if LED1_PORT == B
            #undef  LEDMAP_PORTB
            #define LEDMAP_PORTB 1
        #endif
        #if LED1_PORT == C
            #undef  LEDMAP_PORTC
            #define LEDMAP_PORTC 1
        #endif
        #if LED1_PORT == D
            #undef  LEDMAP_PORTD
            #define LEDMAP_PORTD 1
        #endif
        #if LED1_PORT == E
            #undef  LEDMAP_PORTE
            #define LEDMAP_PORTE 1
        #endif
        #if LED1_PORT == F
            #undef  LEDMAP_PORTF
            #define LEDMAP_PORTF 1
        #endif
    #else
        #error  LED1_PORT or LED1_BIT is not defined.
    #endif
#endif
#if LED_COUNT >= 2
    #if defined(LED2_PORT) && defined(LED2_BIT)
        #define LED2_PORT_ CONCAT_EXP(PORT,LED2_PORT)
        #define LED2_OUT() (_SFR_IO8(_SFR_IO_ADDR(LED2_PORT_)-1) |=  (1<<LED2_BIT))
        #define LED2_HI()  (_SFR_IO8(_SFR_IO_ADDR(LED2_PORT_))   |=  (1<<LED2_BIT))
        #define LED2_LO()  (_SFR_IO8(_SFR_IO_ADDR(LED2_PORT_))   &= ~(1<<LED2_BIT))
        #define LED2_RGB(a,b) CONCAT_EXP(ws2812_setleds_PORT,LED2_PORT)(a,b,(1<<LED2_BIT))
        #if LED2_PORT == A
            #undef  LEDMAP_PORTA
            #define LEDMAP_PORTA 1
        #endif
        #if LED2_PORT == B
            #undef  LEDMAP_PORTB
            #define LEDMAP_PORTB 1
        #endif
        #if LED2_PORT == C
            #undef  LEDMAP_PORTC
            #define LEDMAP_PORTC 1
        #endif
        #if LED2_PORT == D
            #undef  LEDMAP_PORTD
            #define LEDMAP_PORTD 1
        #endif
        #if LED2_PORT == E
            #undef  LEDMAP_PORTE
            #define LEDMAP_PORTE 1
        #endif
        #if LED2_PORT == F
            #undef  LEDMAP_PORTF
            #define LEDMAP_PORTF 1
        #endif
    #else
        #error  LED2_PORT or LED2_BIT is not defined.
    #endif
#endif
#if LED_COUNT >= 3
    #if defined(LED3_PORT) &&  defined(LED3_BIT)
        #define LED3_PORT_ CONCAT_EXP(PORT,LED3_PORT)
        #define LED3_OUT() (_SFR_IO8(_SFR_IO_ADDR(LED3_PORT_)-1) |=  (1<<LED3_BIT))
        #define LED3_HI()  (_SFR_IO8(_SFR_IO_ADDR(LED3_PORT_))   |=  (1<<LED3_BIT))
        #define LED3_LO()  (_SFR_IO8(_SFR_IO_ADDR(LED3_PORT_))   &= ~(1<<LED3_BIT))
        #define LED3_RGB(a,b) CONCAT_EXP(ws2812_setleds_PORT,LED3_PORT)(a,b,(1<<LED3_BIT))
        #if LED3_PORT == A
            #undef  LEDMAP_PORTA
            #define LEDMAP_PORTA 1
        #endif
        #if LED3_PORT == B
            #undef  LEDMAP_PORTB
            #define LEDMAP_PORTB 1
        #endif
        #if LED3_PORT == C
            #undef  LEDMAP_PORTC
            #define LEDMAP_PORTC 1
        #endif
        #if LED3_PORT == D
            #undef  LEDMAP_PORTD
            #define LEDMAP_PORTD 1
        #endif
        #if LED3_PORT == E
            #undef  LEDMAP_PORTE
            #define LEDMAP_PORTE 1
        #endif
        #if LED3_PORT == F
            #undef  LEDMAP_PORTF
            #define LEDMAP_PORTF 1
        #endif
    #else
        #error  LED3_PORT or LED3_BIT is not defined.
    #endif
#endif
#if LED_COUNT >= 4
    #if defined(LED4_PORT) &&  defined(LED4_BIT)
        #define LED4_PORT_ CONCAT_EXP(PORT,LED4_PORT)
        #define LED4_OUT() (_SFR_IO8(_SFR_IO_ADDR(LED4_PORT_)-1) |=  (1<<LED4_BIT))
        #define LED4_HI()  (_SFR_IO8(_SFR_IO_ADDR(LED4_PORT_))   |=  (1<<LED4_BIT))
        #define LED4_LO()  (_SFR_IO8(_SFR_IO_ADDR(LED4_PORT_))   &= ~(1<<LED4_BIT))
        #define LED4_RGB(a,b) CONCAT_EXP(ws2812_setleds_PORT,LED4_PORT)(a,b,(1<<LED4_BIT))
        #if LED4_PORT == A
            #undef  LEDMAP_PORTA
            #define LEDMAP_PORTA 1
        #endif
        #if LED4_PORT == B
            #undef  LEDMAP_PORTB
            #define LEDMAP_PORTB 1
        #endif
        #if LED4_PORT == C
            #undef  LEDMAP_PORTC
            #define LEDMAP_PORTC 1
        #endif
        #if LED4_PORT == D
            #undef  LEDMAP_PORTD
            #define LEDMAP_PORTD 1
        #endif
        #if LED4_PORT == E
            #undef  LEDMAP_PORTE
            #define LEDMAP_PORTE 1
        #endif
        #if LED4_PORT == F
            #undef  LEDMAP_PORTF
            #define LEDMAP_PORTF 1
        #endif
    #else
        #error  LED4_PORT or LED4_BIT is not defined.
    #endif
#endif
#if LED_COUNT >= 5
    #if defined(LED5_PORT) &&  defined(LED5_BIT)
        #define LED5_PORT_ CONCAT_EXP(PORT,LED5_PORT)
        #define LED5_OUT() (_SFR_IO8(_SFR_IO_ADDR(LED5_PORT_)-1) |=  (1<<LED5_BIT))
        #define LED5_HI()  (_SFR_IO8(_SFR_IO_ADDR(LED5_PORT_))   |=  (1<<LED5_BIT))
        #define LED5_LO()  (_SFR_IO8(_SFR_IO_ADDR(LED5_PORT_))   &= ~(1<<LED5_BIT))
        #define LED5_RGB(a,b) CONCAT_EXP(ws2812_setleds_PORT,LED5_PORT)(a,b,(1<<LED5_BIT))
        #if LED5_PORT == A
            #undef  LEDMAP_PORTA
            #define LEDMAP_PORTA 1
        #endif
        #if LED5_PORT == B
            #undef  LEDMAP_PORTB
            #define LEDMAP_PORTB 1
        #endif
        #if LED5_PORT == C
            #undef  LEDMAP_PORTC
            #define LEDMAP_PORTC 1
        #endif
        #if LED5_PORT == D
            #undef  LEDMAP_PORTD
            #define LEDMAP_PORTD 1
        #endif
        #if LED5_PORT == E
            #undef  LEDMAP_PORTE
            #define LEDMAP_PORTE 1
        #endif
        #if LED5_PORT == F
            #undef  LEDMAP_PORTF
            #define LEDMAP_PORTF 1
        #endif
    #else
        #error  LED5_PORT or LED5_BIT is not defined.
    #endif
#endif
#if LED_COUNT >= 6
    #if defined(LED6_PORT) &&  defined(LED6_BIT)
        #define LED6_PORT_ CONCAT_EXP(PORT,LED6_PORT)
        #define LED6_OUT() (_SFR_IO8(_SFR_IO_ADDR(LED6_PORT_)-1) |=  (1<<LED6_BIT))
        #define LED6_HI()  (_SFR_IO8(_SFR_IO_ADDR(LED6_PORT_))   |=  (1<<LED6_BIT))
        #define LED6_LO()  (_SFR_IO8(_SFR_IO_ADDR(LED6_PORT_))   &= ~(1<<LED6_BIT))
        #define LED6_RGB(a,b) CONCAT_EXP(ws2812_setleds_PORT,LED6_PORT)(a,b,(1<<LED6_BIT))
        #if LED6_PORT == A
            #undef  LEDMAP_PORTA
            #define LEDMAP_PORTA 1
        #endif
        #if LED6_PORT == B
            #undef  LEDMAP_PORTB
            #define LEDMAP_PORTB 1
        #endif
        #if LED6_PORT == C
            #undef  LEDMAP_PORTC
            #define LEDMAP_PORTC 1
        #endif
        #if LED6_PORT == D
            #undef  LEDMAP_PORTD
            #define LEDMAP_PORTD 1
        #endif
        #if LED6_PORT == E
            #undef  LEDMAP_PORTE
            #define LEDMAP_PORTE 1
        #endif
        #if LED6_PORT == F
            #undef  LEDMAP_PORTF
            #define LEDMAP_PORTF 1
        #endif
    #else
        #error  LED6_PORT or LED6_BIT is not defined.
    #endif
#endif
#if LED_COUNT >= 7
    #if defined(LED7_PORT) &&  defined(LED7_BIT)
        #define LED7_PORT_ CONCAT_EXP(PORT,LED7_PORT)
        #define LED7_OUT() (_SFR_IO8(_SFR_IO_ADDR(LED7_PORT_)-1) |=  (1<<LED7_BIT))
        #define LED7_HI()  (_SFR_IO8(_SFR_IO_ADDR(LED7_PORT_))   |=  (1<<LED7_BIT))
        #define LED7_LO()  (_SFR_IO8(_SFR_IO_ADDR(LED7_PORT_))   &= ~(1<<LED7_BIT))
        #define LED7_RGB(a,b) CONCAT_EXP(ws2812_setleds_PORT,LED7_PORT)(a,b,(1<<LED7_BIT))
        #if LED7_PORT == A
            #undef  LEDMAP_PORTA
            #define LEDMAP_PORTA 1
        #endif
        #if LED7_PORT == B
            #undef  LEDMAP_PORTB
            #define LEDMAP_PORTB 1
        #endif
        #if LED7_PORT == C
            #undef  LEDMAP_PORTC
            #define LEDMAP_PORTC 1
        #endif
        #if LED7_PORT == D
            #undef  LEDMAP_PORTD
            #define LEDMAP_PORTD 1
        #endif
        #if LED7_PORT == E
            #undef  LEDMAP_PORTE
            #define LEDMAP_PORTE 1
        #endif
        #if LED7_PORT == F
            #undef  LEDMAP_PORTF
            #define LEDMAP_PORTF 1
        #endif
    #else
        #error  LED7_PORT or LED7_BIT is not defined.
    #endif
#endif
#if LED_COUNT >= 8
    #if defined(LED8_PORT) &&  defined(LED8_BIT)
        #define LED8_PORT_ CONCAT_EXP(PORT,LED8_PORT)
        #define LED8_OUT() (_SFR_IO8(_SFR_IO_ADDR(LED8_PORT_)-1) |=  (1<<LED8_BIT))
        #define LED8_HI()  (_SFR_IO8(_SFR_IO_ADDR(LED8_PORT_))   |=  (1<<LED8_BIT))
        #define LED8_LO()  (_SFR_IO8(_SFR_IO_ADDR(LED8_PORT_))   &= ~(1<<LED8_BIT))
        #if LED8_PORT == A
            #undef  LEDMAP_PORTA
            #define LEDMAP_PORTA 1
        #endif
        #if LED8_PORT == B
            #undef  LEDMAP_PORTB
            #define LEDMAP_PORTB 1
        #endif
        #if LED8_PORT == C
            #undef  LEDMAP_PORTC
            #define LEDMAP_PORTC 1
        #endif
        #if LED8_PORT == D
            #undef  LEDMAP_PORTD
            #define LEDMAP_PORTD 1
        #endif
        #if LED8_PORT == E
            #undef  LEDMAP_PORTE
            #define LEDMAP_PORTE 1
        #endif
        #if LED8_PORT == F
            #undef  LEDMAP_PORTF
            #define LEDMAP_PORTF 1
        #endif
    #else
        #error  LED8_PORT or LED8_BIT is not defined.
    #endif
#endif
#if LED_COUNT >= 9
    #error  Does not support for more than 8 LEDs.
#endif

#undef A
#undef B
#undef C
#undef D
#undef E
#undef F

#ifdef DEBUG
    #ifndef VALUE_TO_STRING
        #define VALUE_TO_STRING(x) #x
        #define VALUE(x) VALUE_TO_STRING(x)
        #define VAR_NAME_VALUE(var) #var "="  VALUE(var)
    #endif
    #ifndef MESSAGE_LEDMAP_PORT
        #pragma message(VAR_NAME_VALUE(LEDMAP_PORTA))
        #pragma message(VAR_NAME_VALUE(LEDMAP_PORTB))
        #pragma message(VAR_NAME_VALUE(LEDMAP_PORTC))
        #pragma message(VAR_NAME_VALUE(LEDMAP_PORTD))
        #pragma message(VAR_NAME_VALUE(LEDMAP_PORTE))
        #pragma message(VAR_NAME_VALUE(LEDMAP_PORTF))
    #endif
#endif

#if LEDMAP_PORTA > 0
    #define WS2812_USE_PORTA
#endif
#if LEDMAP_PORTB > 0
    #define WS2812_USE_PORTB
#endif
#if LEDMAP_PORTC > 0
    #define WS2812_USE_PORTC
#endif
#if LEDMAP_PORTD > 0
    #define WS2812_USE_PORTD
#endif
#if LEDMAP_PORTE > 0
    #define WS2812_USE_PORTE
#endif
#if LEDMAP_PORTF > 0
    #define WS2812_USE_PORTF
#endif

#endif
