// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H

typedef enum module { none, hlc_none, hlc_cirque_trackpad, hlc_encoder, hlc_tft_display } module_t;

extern module_t module_master;

bool module_post_init_kb(void);
bool module_housekeeping_task_kb(void);
bool display_module_housekeeping_task_kb(bool second_display);
bool module_post_init_user(void);
bool module_housekeeping_task_user(void);
bool display_module_housekeeping_task_user(bool second_display);
