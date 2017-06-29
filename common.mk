COMMON_DIR = common
SRC +=	$(COMMON_DIR)/host.c \
	$(COMMON_DIR)/keyboard.c \
	$(COMMON_DIR)/action.c \
	$(COMMON_DIR)/action_tapping.c \
	$(COMMON_DIR)/action_macro.c \
	$(COMMON_DIR)/action_layer.c \
	$(COMMON_DIR)/action_util.c \
	$(COMMON_DIR)/print.c \
	$(COMMON_DIR)/debug.c \
	$(COMMON_DIR)/util.c \
	$(COMMON_DIR)/hook.c \
	$(COMMON_DIR)/avr/suspend.c \
	$(COMMON_DIR)/avr/xprintf.S \
	$(COMMON_DIR)/avr/timer.c \
	$(COMMON_DIR)/avr/bootloader.c


# Option modules
ifdef ACTIONMAP_ENABLE
    SRC += $(COMMON_DIR)/actionmap.c
    OPT_DEFS += -DACTIONMAP_ENABLE
else
    SRC += $(COMMON_DIR)/keymap.c
endif

ifdef BOOTMAGIC_ENABLE
    SRC += $(COMMON_DIR)/bootmagic.c
    SRC += $(COMMON_DIR)/avr/eeconfig.c
    OPT_DEFS += -DBOOTMAGIC_ENABLE
endif

ifdef MOUSEKEY_ENABLE
    SRC += $(COMMON_DIR)/mousekey.c
    OPT_DEFS += -DMOUSEKEY_ENABLE
    OPT_DEFS += -DMOUSE_ENABLE
endif

ifdef EXTRAKEY_ENABLE
    OPT_DEFS += -DEXTRAKEY_ENABLE
endif

ifdef CONSOLE_ENABLE
    OPT_DEFS += -DCONSOLE_ENABLE
else
    OPT_DEFS += -DNO_PRINT
    OPT_DEFS += -DNO_DEBUG
endif

ifdef COMMAND_ENABLE
    SRC += $(COMMON_DIR)/command.c
    OPT_DEFS += -DCOMMAND_ENABLE
endif

ifdef NKRO_ENABLE
    OPT_DEFS += -DNKRO_ENABLE
endif

ifdef USB_6KRO_ENABLE
    OPT_DEFS += -DUSB_6KRO_ENABLE
endif

ifdef KEYBOARD_LOCK_ENABLE
    OPT_DEFS += -DKEYBOARD_LOCK_ENABLE
endif

ifdef SLEEP_LED_ENABLE
    SRC += $(COMMON_DIR)/avr/sleep_led.c
    OPT_DEFS += -DSLEEP_LED_ENABLE
    OPT_DEFS += -DNO_SUSPEND_POWER_DOWN
endif

ifdef SOFTPWM_LED_ENABLE
    SRC += $(COMMON_DIR)/avr/softpwm_led.c
    OPT_DEFS += -DSOFTPWM_LED_ENABLE
ifdef FADING_LED_ENABLE
    OPT_DEFS += -DFADING_LED_ENABLE
endif
ifdef BREATHING_LED_ENABLE
    OPT_DEFS += -DBREATHING_LED_ENABLE
endif
else
ifdef BREATHING_LED_ENABLE
    SRC += $(COMMON_DIR)/breathing_led.c
    OPT_DEFS += -DBREATHING_LED_ENABLE
endif
endif

ifdef RGB_LED_ENABLE
    SRC += $(COMMON_DIR)/avr/eeconfig.c
    SRC += $(COMMON_DIR)/avr/light_ws2812.c
    SRC += $(COMMON_DIR)/rgb_led.c
    OPT_DEFS += -DRGB_LED_ENABLE
    OPT_DEFS += -DRGB_LED_WS2812
endif

ifdef BACKLIGHT_ENABLE
    SRC += $(COMMON_DIR)/avr/eeconfig.c
    SRC += $(COMMON_DIR)/backlight.c
    OPT_DEFS += -DBACKLIGHT_ENABLE
endif

ifdef LEDMAP_ENABLE
    SRC += $(COMMON_DIR)/ledmap.c
    OPT_DEFS += -DLEDMAP_ENABLE
ifdef LEDMAP_IN_EEPROM_ENABLE
    SRC += $(COMMON_DIR)/ledmap_in_eeprom.c
    OPT_DEFS += -DLEDMAP_IN_EEPROM_ENABLE
endif
endif

ifdef KEYMAP_IN_EEPROM_ENABLE
    SRC += $(COMMON_DIR)/keymap_in_eeprom.c
    OPT_DEFS += -DKEYMAP_IN_EEPROM_ENABLE
endif

ifdef KEYMAP_SECTION_ENABLE
    OPT_DEFS += -DKEYMAP_SECTION_ENABLE

    ifeq ($(strip $(MCU)),atmega32u2)
	EXTRALDFLAGS = -Wl,-L$(TMK_DIR),-Tldscript_keymap_avr35.x
    else ifeq ($(strip $(MCU)),atmega32u4)
	EXTRALDFLAGS = -Wl,-L$(TMK_DIR),-Tldscript_keymap_avr5.x
    else
	EXTRALDFLAGS = $(error no ldscript for keymap section)
    endif
endif

ifdef RAWHID_ENABLE
    SRC += $(COMMON_DIR)/rawhid_command.c
    OPT_DEFS += -DRAWHID_ENABLE
endif

# Version string
VERSION := $(shell (git describe --always --dirty || echo 'unknown') 2> /dev/null)
OPT_DEFS += -DVERSION=$(VERSION)


# Search Path
VPATH += $(TMK_DIR)/common
