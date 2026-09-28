// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

// Any QMK options should go here

#pragma once

#define HLC_ENCODER

#define HLC_ENCODER_BUTTON 16

#define ENCODER_RESOLUTION 2

#define BUTTON_PINS        \
    (const pin_t[]) {      \
        HLC_ENCODER_BUTTON \
    }

#undef HLC_ENCODER_A
#define HLC_ENCODER_A 27
#undef HLC_ENCODER_B
#define HLC_ENCODER_B 26
