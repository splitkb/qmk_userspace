// Copyright 2026 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#undef ENCODER_RESOLUTION

#if NUM_ENCODERS == 2
#    define ENCODER_RESOLUTION 4
#elif NUM_ENCODERS == 4
#    define ENCODER_RESOLUTIONS {2, 4}
#elif NUM_ENCODERS == 6
#    define ENCODER_RESOLUTIONS {2, 2, 4}
#elif NUM_ENCODERS == 8
#    define ENCODER_RESOLUTIONS {2, 2, 2, 4}
#endif
