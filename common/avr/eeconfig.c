#include <stdint.h>
#include <stdbool.h>
#include <avr/eeprom.h>
#include "eeconfig.h"
#ifdef BACKLIGHT_ENABLE
#include "backlight.h"
#endif
#ifdef RGB_LED_ENABLE
#include "rgb_led.h"
#endif

void eeconfig_init(void)
{
    eeprom_write_word(EECONFIG_MAGIC,          EECONFIG_MAGIC_NUMBER);
    eeprom_write_byte(EECONFIG_DEBUG,          0);
    eeprom_write_byte(EECONFIG_DEFAULT_LAYER,  0);
    eeprom_write_byte(EECONFIG_KEYMAP,         0);
    eeprom_write_byte(EECONFIG_MOUSEKEY_ACCEL, 0);
#ifdef PS2_MOUSE_ENABLE
    eeprom_write_byte(EECONFIG_PS2_MOUSE,      0);
#endif
#ifdef BACKLIGHT_ENABLE
    eeprom_write_byte(EECONFIG_BACKLIGHT,      backlight_config_default.raw);
#endif
#ifdef RGB_LED_ENABLE
    eeprom_write_byte(EECONFIG_RGB_LED,        rgb_led_config_default.raw);
    eeprom_write_byte(EECONFIG_RGB_LED_BRIGHTNESS, rgb_led_brightness_default);
#endif
}

void eeconfig_enable(void)
{
    eeprom_write_word(EECONFIG_MAGIC, EECONFIG_MAGIC_NUMBER);
}

void eeconfig_disable(void)
{
    eeprom_write_word(EECONFIG_MAGIC, 0xFFFF);
}

bool eeconfig_is_enabled(void)
{
    return (eeprom_read_word(EECONFIG_MAGIC) == EECONFIG_MAGIC_NUMBER);
}

uint8_t eeconfig_read_debug(void)      { return eeprom_read_byte(EECONFIG_DEBUG); }
void eeconfig_write_debug(uint8_t val) { eeprom_write_byte(EECONFIG_DEBUG, val); }

uint8_t eeconfig_read_default_layer(void)      { return eeprom_read_byte(EECONFIG_DEFAULT_LAYER); }
void eeconfig_write_default_layer(uint8_t val) { eeprom_write_byte(EECONFIG_DEFAULT_LAYER, val); }

uint8_t eeconfig_read_keymap(void)      { return eeprom_read_byte(EECONFIG_KEYMAP); }
void eeconfig_write_keymap(uint8_t val) { eeprom_write_byte(EECONFIG_KEYMAP, val); }

#ifdef PS2_MOUSE_ENABLE
uint8_t eeconfig_read_ps2_mouse(void)      { return eeprom_read_byte(EECONFIG_PS2_MOUSE); }
void eeconfig_write_ps2_mouse(uint8_t val) { eeprom_write_byte(EECONFIG_PS2_MOUSE, val); }
#endif

#ifdef BACKLIGHT_ENABLE
uint8_t eeconfig_read_backlight(void)      { return eeprom_read_byte(EECONFIG_BACKLIGHT); }
void eeconfig_write_backlight(uint8_t val) { eeprom_write_byte(EECONFIG_BACKLIGHT, val); }
#endif

#ifdef RGB_LED_ENABLE
uint8_t eeconfig_read_rgb_led(void)      { return eeprom_read_byte(EECONFIG_RGB_LED); }
void eeconfig_write_rgb_led(uint8_t val) { eeprom_write_byte(EECONFIG_RGB_LED, val); }

uint8_t eeconfig_read_rgb_led_brightness(void)      { return eeprom_read_byte(EECONFIG_RGB_LED_BRIGHTNESS); }
void eeconfig_write_rgb_led_brightness(uint8_t val) { eeprom_write_byte(EECONFIG_RGB_LED_BRIGHTNESS, val); }
#endif
