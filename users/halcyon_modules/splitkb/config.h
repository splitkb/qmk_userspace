// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define HALCYON_ENABLE

#define SPLIT_TRANSACTION_IDS_KB MODULE_SYNC

#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_COMBINED

#define HLC_BACKLIGHT_TIMEOUT 120000

#define BACKLIGHT_PWM_DRIVER PWMD5
#define BACKLIGHT_LEVELS 10
#define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_B

#define BACKLIGHT_PIN 2          // NOT CONNECTED
#define POINTING_DEVICE_CS_PIN 2 // NOT CONNECTED
#define HLC_ENCODER_A NO_PIN
#define HLC_ENCODER_B NO_PIN

#define SPLIT_MODS_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_LAYER_STATE_ENABLE

// Make it easier to enter the bootloader
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET

#ifndef HALCYON_LEGACY
#    if MATRIX_COLS == 3
#        undef MATRIX_COLS
#        define MATRIX_COLS 8 // 5 extra columns for buttons
#    elif MATRIX_COLS == 4
#        undef MATRIX_COLS
#        define MATRIX_COLS 9
#    elif MATRIX_COLS == 5
#        undef MATRIX_COLS
#        define MATRIX_COLS 10
#    elif MATRIX_COLS == 6
#        undef MATRIX_COLS
#        define MATRIX_COLS 11
#    elif MATRIX_COLS == 7
#        undef MATRIX_COLS
#        define MATRIX_COLS 12
#    elif MATRIX_COLS == 8
#        undef MATRIX_COLS
#        define MATRIX_COLS 13
#    elif MATRIX_COLS == 9
#        undef MATRIX_COLS
#        define MATRIX_COLS 14
#    elif MATRIX_COLS == 10
#        undef MATRIX_COLS
#        define MATRIX_COLS 15
#    endif // May need to be expanded in the future
#endif     // HALCYON_LEGACY

//// VIK

// GPIO1 = 27
// GPIO2 = 26
// CS = 13

#undef I2C_DRIVER
#undef I2C1_SDA_PIN
#undef I2C1_SCL_PIN
#define I2C_DRIVER I2C0
#define I2C1_SDA_PIN 16
#define I2C1_SCL_PIN 17

#undef SPI_DRIVER
#undef SPI_SCK_PIN
#undef SPI_MOSI_PIN
#undef SPI_MISO_PIN
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN 14
#define SPI_MOSI_PIN 15
#define SPI_MISO_PIN 12

// Increase SERIAL_SPEED to handle 16 bit int matrix better on single wire USART
#define SELECT_SOFT_SERIAL_SPEED 0

// Keyboard redefines
#undef ENCODER_A_PINS
#undef ENCODER_B_PINS

// Kyria
#ifdef KEYBOARD_splitkb_halcyon_kyria_rev4
#    define ENCODER_A_PINS {GP23, HLC_ENCODER_A}
#    define ENCODER_B_PINS {GP22, HLC_ENCODER_B}
#endif

#ifdef KEYBOARD_splitkb_kyria_rev3
#    define ENCODER_A_PINS {F4, HLC_ENCODER_A}
#    define ENCODER_B_PINS {F5, HLC_ENCODER_B}
#    undef ENCODER_A_PINS_RIGHT
#    undef ENCODER_B_PINS_RIGHT
#    define ENCODER_A_PINS_RIGHT {F4, HLC_ENCODER_A}
#    define ENCODER_B_PINS_RIGHT {F5, HLC_ENCODER_B}
#endif

// Elora
#ifdef KEYBOARD_splitkb_halcyon_elora_rev2
#    define ENCODER_A_PINS {GP22, HLC_ENCODER_A}
#    define ENCODER_B_PINS {GP18, HLC_ENCODER_B}
#endif

// Corne
#ifdef KEYBOARD_splitkb_halcyon_corne_rev2
#    define ENCODER_A_PINS {GP24, HLC_ENCODER_A}
#    define ENCODER_B_PINS {GP23, HLC_ENCODER_B}
#endif

#ifdef KEYBOARD_splitkb_aurora_corne_rev1
#    define ENCODER_A_PINS {D4, HLC_ENCODER_A}
#    define ENCODER_B_PINS {C6, HLC_ENCODER_B}
#    undef ENCODER_A_PINS_RIGHT
#    undef ENCODER_B_PINS_RIGHT
#    define ENCODER_A_PINS_RIGHT {F6, HLC_ENCODER_A}
#    define ENCODER_B_PINS_RIGHT {F7, HLC_ENCODER_B}
#endif

// Lily58
#ifdef KEYBOARD_splitkb_halcyon_lily58_rev2
#    define ENCODER_A_PINS {GP24, HLC_ENCODER_A}
#    define ENCODER_B_PINS {GP23, HLC_ENCODER_B}
#endif

#ifdef KEYBOARD_splitkb_aurora_lily58_rev1
#    define ENCODER_A_PINS {C6, HLC_ENCODER_A}
#    define ENCODER_B_PINS {D4, HLC_ENCODER_B}
#    undef ENCODER_A_PINS_RIGHT
#    undef ENCODER_B_PINS_RIGHT
#    define ENCODER_A_PINS_RIGHT {F7, HLC_ENCODER_A}
#    define ENCODER_B_PINS_RIGHT {F6, HLC_ENCODER_B}
#endif

// Ferris
#ifdef KEYBOARD_splitkb_halcyon_ferris_rev1
#    define ENCODER_A_PINS {HLC_ENCODER_A}
#    define ENCODER_B_PINS {HLC_ENCODER_B}
#endif

#ifdef KEYBOARD_splitkb_aurora_sweep_rev1
#    define ENCODER_A_PINS {B5, B3, HLC_ENCODER_A}
#    define ENCODER_B_PINS {B4, B2, HLC_ENCODER_B}
#    undef ENCODER_A_PINS_RIGHT
#    undef ENCODER_B_PINS_RIGHT
#    define ENCODER_A_PINS_RIGHT {B2, F5, HLC_ENCODER_A}
#    define ENCODER_B_PINS_RIGHT {B6, D4, HLC_ENCODER_B}
#endif

// Helix
#ifdef KEYBOARD_splitkb_aurora_helix_rev1
#    define ENCODER_A_PINS {B4, HLC_ENCODER_A}
#    define ENCODER_B_PINS {E6, HLC_ENCODER_B}

#    undef ENCODER_A_PINS_RIGHT
#    undef ENCODER_B_PINS_RIGHT
#    define ENCODER_A_PINS_RIGHT {B2, HLC_ENCODER_A}
#    define ENCODER_B_PINS_RIGHT {B3, HLC_ENCODER_B}
#endif

// Sofle v2
#ifdef KEYBOARD_splitkb_aurora_sofle_v2_rev1
#    define ENCODER_A_PINS {B2, HLC_ENCODER_A}
#    define ENCODER_B_PINS {B6, HLC_ENCODER_B}

#    undef ENCODER_A_PINS_RIGHT
#    undef ENCODER_B_PINS_RIGHT
#    define ENCODER_A_PINS_RIGHT {B2, HLC_ENCODER_A}
#    define ENCODER_B_PINS_RIGHT {B6, HLC_ENCODER_B}
#endif
