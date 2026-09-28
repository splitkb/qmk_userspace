// Copyright 2026 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "matrix.h"

#ifdef SPLIT_KEYBOARD
#    define ROWS_PER_HAND (MATRIX_ROWS / 2)
#else
#    define ROWS_PER_HAND (MATRIX_ROWS)
#endif

#ifndef HALCYON_LEGACY
#    define VIRTUAL_COL_START (MATRIX_COLS - 5)
#endif // HALCYON_LEGACY

extern matrix_row_t matrix[MATRIX_ROWS];

#ifndef BUTTON_PINS
#    define BUTTON_PINS \
        (const pin_t[]) {}
#endif

#define NUM_BUTTON_PINS (sizeof(BUTTON_PINS) / sizeof(BUTTON_PINS[0]))

#ifdef HALCYON_LEGACY
static void scan_legacy_buttons(void) {
    size_t num_pins = NUM_BUTTON_PINS;
    if (num_pins == 0) return;

    // Legacy layouts expect the button on the extra matrix row, zero-indexed.
    uint8_t row = is_keyboard_left() ? (ROWS_PER_HAND - 1) : (MATRIX_ROWS - 1);

    for (size_t i = 0; i < num_pins && i < MATRIX_COLS; i++) {
        if (gpio_read_pin(BUTTON_PINS[i]) == 0) {
            matrix[row] |= ((matrix_row_t)1 << i);
        } else {
            matrix[row] &= ~((matrix_row_t)1 << i);
        }
    }
}
#else
static void scan_buttons(void) {
    size_t num_pins = NUM_BUTTON_PINS;
    if (num_pins == 0) return;

    uint8_t row = is_keyboard_left() ? 0 : ROWS_PER_HAND;

    for (size_t i = 0; i < num_pins && (VIRTUAL_COL_START + i) < MATRIX_COLS; i++) {
        if (gpio_read_pin(BUTTON_PINS[i]) == 0) {
            matrix[row] |= ((matrix_row_t)1 << (VIRTUAL_COL_START + i));
        } else {
            matrix[row] &= ~((matrix_row_t)1 << (VIRTUAL_COL_START + i));
        }
    }
}
#endif

void matrix_init_kb(void) {
    size_t num_pins = sizeof(BUTTON_PINS) / sizeof(BUTTON_PINS[0]);

    for (uint8_t i = 0; i < num_pins; i++) {
        gpio_set_pin_input_high(BUTTON_PINS[i]);
    }

    matrix_init_user();
}

void matrix_scan_kb(void) {
#ifdef HALCYON_LEGACY
    scan_legacy_buttons();
#else
    scan_buttons();
#endif

    matrix_scan_user();
}

void matrix_slave_scan_kb(void) {
#ifdef HALCYON_LEGACY
    scan_legacy_buttons();
#else
    scan_buttons();
#endif

    matrix_slave_scan_user();
}

#ifndef HALCYON_LEGACY
#    if (defined(HALCYON_BUTTONS_ENABLE) || !defined(VIAL_ENABLE))
__attribute__((weak)) const uint16_t left_halcyon_buttons[10][5];
__attribute__((weak)) const uint16_t right_halcyon_buttons[10][5];

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.key.col >= VIRTUAL_COL_START) {
        uint8_t btn = record->event.key.col - VIRTUAL_COL_START;

        if (btn < 5) {
            uint8_t max_layer = get_highest_layer(layer_state | default_layer_state);

            for (int8_t l = max_layer; l >= 0; l--) {
                if (!((layer_state | default_layer_state) & (1UL << l))) continue;

                uint16_t code = KC_TRNS;

                const uint16_t (*table)[5] = record->event.key.row < ROWS_PER_HAND ? left_halcyon_buttons : right_halcyon_buttons;
                code                       = table[l][btn];

                if (code != KC_TRNS) {
                    record->event.pressed ? register_code16(code) : unregister_code16(code);
                    break;
                }
            }
        }
        return false;
    }

    return process_record_user(keycode, record);
}
#    endif // HALCYON_BUTTONS_ENABLE || VIAL_ENABLE
#endif     // HALCYON_LEGACY
