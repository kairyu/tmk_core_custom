#ifndef LEDMAP_IN_EEPROM_H
#define LEDMAP_IN_EEPROM_H

#include "eeconfig.h"
#include "ledmap.h"

#define LEDMAP_SIZE (sizeof(uint16_t) * LED_COUNT)
#ifndef EECONFIG_LEDMAP_IN_EEPROM
#   define EECONFIG_LEDMAP_IN_EEPROM        EECONFIG_END
#endif

#ifdef LEDMAP_IN_EEPROM_ENABLE
#   define EECONFIG_LEDMAP_IN_EEPROM_END    EECONFIG_LEDMAP_IN_EEPROM + LEDMAP_SIZE
#else
#   define EECONFIG_LEDMAP_IN_EEPROM_END    EECONFIG_LEDMAP_IN_EEPROM
#endif

#ifdef DEBUG
#   ifndef VALUE_TO_STRING
#       define VALUE_TO_STRING(x) #x
#       define VALUE(x) VALUE_TO_STRING(x)
#       define VAR_NAME_VALUE(var) #var "="  VALUE(var)
#   endif
#   ifndef MESSAGE_EECONFIG_LEDMAP_IN_EEPROM
#       define MESSAGE_EECONFIG_LEDMAP_IN_EEPROM
#       pragma message(VAR_NAME_VALUE(EECONFIG_LEDMAP_IN_EEPROM))
#   endif
#endif

#define EECONFIG_LEDMAP (uint16_t*)(EECONFIG_LEDMAP_IN_EEPROM)

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
