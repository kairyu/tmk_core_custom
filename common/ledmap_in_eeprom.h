#ifndef LEDMAP_IN_EEPROM_H
#define LEDMAP_IN_EEPROM_H

#include "ledmap.h"

#ifndef EECONFIG_LEDMAP_IN_EEPROM
#ifdef PS2_MOUSE_ENABLE
#define EECONFIG_LEDMAP_IN_EEPROM 8
#else
#define EECONFIG_LEDMAP_IN_EEPROM 7
#endif
#endif

#define EECONFIG_LEDMAP (uint16_t*)EECONFIG_LEDMAP_IN_EEPROM
#define LEDMAP_SIZE (sizeof(uint16_t) * LED_COUNT)

#define LEDMAP_UNCONFIGURED 0xFFFF

#ifdef LEDMAP_IN_EEPROM_ENABLE
#define ledmap_get_code ledmap_in_eeprom_get_code
void ledmap_in_eeprom_init(void);
void write_ledmap_to_eeprom(void);
ledmap_t ledmap_in_eeprom_get_code(uint8_t index);
#else
#define ledmap_in_eeprom_init()
#define write_ledmap_to_eeprom()
#define ledmap_in_eeprom_get_code()
#endif

#endif
