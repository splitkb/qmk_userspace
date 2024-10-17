// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VIAL_KEYBOARD_UID {0xEA, 0x55, 0x2E, 0xF9, 0x02, 0xA3, 0x12, 0x94}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 5 }
#define VIAL_UNLOCK_COMBO_COLS { 1, 1 }

// Increase the EEPROM size for layout options
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

#define DYNAMIC_KEYMAP_LAYER_COUNT 8