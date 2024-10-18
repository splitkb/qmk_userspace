// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "util.h"
#include "split_util.h"
#include "matrix.h"
#include "debounce.h"
#include "atomic_util.h"

#ifdef SPLIT_KEYBOARD
#    define ROWS_PER_HAND (MATRIX_ROWS / 2)
#else
#    define ROWS_PER_HAND (MATRIX_ROWS)
#endif

#ifdef MATRIX_ROW_PINS_RIGHT
#    define SPLIT_MUTABLE_ROW
#else
#    define SPLIT_MUTABLE_ROW const
#endif
#ifdef MATRIX_COL_PINS_RIGHT
#    define SPLIT_MUTABLE_COL
#else
#    define SPLIT_MUTABLE_COL const
#endif

#ifndef MATRIX_INPUT_PRESSED_STATE
#    define MATRIX_INPUT_PRESSED_STATE 0
#endif

#ifdef DIRECT_PINS
static SPLIT_MUTABLE pin_t direct_pins[ROWS_PER_HAND][MATRIX_COLS] = DIRECT_PINS;
#elif (DIODE_DIRECTION == ROW2COL) || (DIODE_DIRECTION == COL2ROW)
#    ifdef MATRIX_ROW_PINS
static SPLIT_MUTABLE_ROW pin_t row_pins[ROWS_PER_HAND] = MATRIX_ROW_PINS;
#    endif // MATRIX_ROW_PINS
#    ifdef MATRIX_COL_PINS
static SPLIT_MUTABLE_COL pin_t col_pins[MATRIX_COLS]   = MATRIX_COL_PINS;
#    endif // MATRIX_COL_PINS
#endif

void matrix_init_kb(void) {

    gpio_set_pin_input_high(HLC_ENCODER_BUTTON);

    // Also need to define here otherwise right half is swapped
    if (!isLeftHand) {
        #    ifdef MATRIX_ROW_PINS_RIGHT
                const pin_t row_pins_right[ROWS_PER_HAND] = MATRIX_ROW_PINS_RIGHT;
                for (uint8_t i = 0; i < ROWS_PER_HAND; i++) {
                    row_pins[i] = row_pins_right[i];
                }
        #    endif
        #    ifdef MATRIX_COL_PINS_RIGHT
                const pin_t col_pins_right[MATRIX_COLS] = MATRIX_COL_PINS_RIGHT;
                for (uint8_t i = 0; i < MATRIX_COLS; i++) {
                    col_pins[i] = col_pins_right[i];
                }
        #    endif
    }
}

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(pin);
        gpio_write_pin_low(pin);
    }
}

static inline void setPinOutput_writeHigh(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(pin);
        gpio_write_pin_high(pin);
    }
}

static inline void setPinInputHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_input_high(pin);
    }
}

static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return (gpio_read_pin(pin) == MATRIX_INPUT_PRESSED_STATE) ? 0 : 1;
    } else {
        return 1;
    }
}

// THIS FUNCTION IS CHANGED, removed NO_PIN check
static bool select_row(uint8_t row) {
    pin_t pin = row_pins[row];
    setPinOutput_writeLow(pin);
    return true;
}

static void unselect_row(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
#            ifdef MATRIX_UNSELECT_DRIVE_HIGH
        setPinOutput_writeHigh(pin);
#            else
        setPinInputHigh_atomic(pin);
#            endif
    }
}

void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    if (!select_row(current_row)) { // Select row
        return;                     // skip NO_PIN row
    }
    matrix_output_select_delay();

    // ↓↓↓ THIS HAS BEEN ADDED/CHANGED
    if (current_row == (ROWS_PER_HAND - 1)) {
        current_row_value |= ((!gpio_read_pin(HLC_ENCODER_BUTTON)) & 1) << 0;
    } else {
        // For each col...
        matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
        for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++, row_shifter <<= 1) {
            uint8_t pin_state = readMatrixPin(col_pins[col_index]);

            // Populate the matrix row with the state of the col pin
            current_row_value |= pin_state ? 0 : row_shifter;
        }
    } 
    // ↑↑↑ THIS HAS BEEN ADDED/CHANGED

    // Unselect row
    unselect_row(current_row);
    matrix_output_unselect_delay(current_row, current_row_value != 0); // wait for all Col signals to go HIGH

    // Update the matrix
    current_matrix[current_row] = current_row_value;
}