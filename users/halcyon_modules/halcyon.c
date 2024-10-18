// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "halcyon.h"
#include "transactions.h"
#include "print.h"
#include "split_util.h"
#include "pointing_device.h"

__attribute__((weak)) bool module_post_init_kb(void) {
    return module_post_init_user();
}
__attribute__((weak)) bool module_housekeeping_task_kb(void) {
    return module_housekeeping_task_user();
}
__attribute__((weak)) bool display_module_housekeeping_task_kb(bool second_display) {
    return display_module_housekeeping_task_user(second_display);
}

__attribute__((weak)) bool module_post_init_user(void) {
    return true;
}
__attribute__((weak)) bool module_housekeeping_task_user(void) {
    return true;
}
__attribute__((weak)) bool display_module_housekeeping_task_user(bool second_display) {
    return true;
}

module_t module;
#ifdef HLC_NONE
    module_t module = hlc_none;
#endif
#ifdef HLC_CIRQUE_TRACKPAD
    module_t module = hlc_cirque_trackpad;
#endif
#ifdef HLC_ENCODER
    module_t module = hlc_encoder;
#endif
#ifdef HLC_TFT_DISPLAY
    module_t module = hlc_tft_display;
#endif

void module_sync_slave_handler(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(module)) {
        memcpy(&module_master, initiator2target_buffer, sizeof(module_master));
    }
}

void keyboard_post_init_kb(void) {
    // Register module sync split transaction
    transaction_register_rpc(MODULE_SYNC, module_sync_slave_handler);

    // Do any post init for modules
    module_post_init_kb();

    // User post init
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    if (is_keyboard_master()) {
        static bool synced = 0;
        if(is_transport_connected() && synced == 0) {
            transaction_rpc_send(MODULE_SYNC, sizeof(module), &module); // Sync to slave
            synced = 1;
        }
        display_module_housekeeping_task_kb(false); // Is master so can never be the second display
    }
    if (!is_keyboard_master()) {
        if (module_master == hlc_tft_display) {
            display_module_housekeeping_task_kb(true); // If there is a display on master, become the second display
        } else {
            display_module_housekeeping_task_kb(false); // Otherwise be the main display
        }
    }
    module_housekeeping_task_kb();

    housekeeping_task_user();
}

report_mouse_t pointing_device_task_combined_kb(report_mouse_t left_report, report_mouse_t right_report) {
    // Only runs on master
    // Fixes the following bug: If master is right and master is NOT a cirque trackpad, the inputs would be inverted.
    if(module != hlc_cirque_trackpad && !is_keyboard_left()) {
        mouse_xy_report_t x = left_report.x;
        mouse_xy_report_t y = left_report.y;
        left_report.x = -x;
        left_report.y = -y;
    }
    return pointing_device_task_combined_user(left_report, right_report);
}

// Kyria
#if defined(PRODUCT_ID) && PRODUCT_ID == 0x7FCE
#ifdef RGB_MATRIX_ENABLE
#include "rgb_matrix.h"
led_config_t g_led_config = {
  {
    { NO_LED, 25, 26, 27, 28, 29, 30 },
    { NO_LED, 19, 20, 21, 22, 23, 24 },
    { 11, 13, 14, 15, 16, 17, 18 },
    { 6, 8, 9, 12, 10, 7, NO_LED },
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED, 56, 57, 58, 59, 60, 61 },
    { NO_LED, 50, 51, 52, 53, 54, 55 },
    { 42, 44, 45, 46, 47, 48, 49 },
    { 37, 39, 40, 43, 41, 38, NO_LED },
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  },
  { {75, 2}, {50, 1}, {14, 4}, {25, 45}, {58, 49}, {94, 53}, {94, 64}, {79, 60}, {65, 53}, {51, 49}, {36, 49}, {101, 49}, {87, 45}, {72, 38}, {58, 34}, {43, 30}, {29, 34}, {14, 41}, {0, 41}, {72, 23}, {58, 19}, {43, 15}, {29, 19}, {14, 26}, {0, 26}, {72, 8}, {58, 4}, {43, 0}, {29, 4}, {14, 11}, {0, 11}, {149, 2}, {174, 1}, {210, 4}, {199, 45}, {166, 49}, {130, 53}, {130, 64}, {145, 60}, {159, 53}, {173, 49}, {188, 49}, {123, 49}, {137, 45}, {152, 38}, {166, 34}, {181, 30}, {195, 34}, {210, 41}, {224, 41}, {152, 23}, {166, 19}, {181, 15}, {195, 19}, {210, 26}, {224, 26}, {152, 8}, {166, 4}, {181, 0}, {195, 4}, {210, 11}, {224, 11} },
  { 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
};
#endif

#ifdef MATRIX_MASKED
const matrix_row_t matrix_mask[] = {
    0b1111110,
    0b1111110,
    0b1111111,
    0b0111111,
    0b0011111,
    0b1111110,
    0b1111110,
    0b1111111,
    0b0111111,
    0b0011111,
};
#endif
#endif