// ============================================================
//  config.h – urob_qwerty keymap
//  splitkb Halcyon Corne rev2
// ============================================================
#pragma once

// ─────────────────────────────────────────
// Tapping / hold-tap
// ─────────────────────────────────────────

// Base tapping term (overridden per-key in keymap.c)
#define TAPPING_TERM 200

// Enable per-key tapping term (get_tapping_term in keymap.c)
#define TAPPING_TERM_PER_KEY

// Enable per-key quick tap term (get_quick_tap_term in keymap.c)
// Quick tap allows key repeat when a hold-tap key is double-tapped
#define QUICK_TAP_TERM 0
#define QUICK_TAP_TERM_PER_KEY

// Enable per-key permissive hold (get_permissive_hold in keymap.c)
#define PERMISSIVE_HOLD_PER_KEY

// Enable per-key hold-on-other-key-press (get_hold_on_other_key_press in keymap.c)
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// ─────────────────────────────────────────
// Combos
// ─────────────────────────────────────────

// How long two keys must be held simultaneously to trigger a combo
#define COMBO_TERM 40

// With mod-tap keys in combos, require them to be tapped (not held)
// This prevents misfires when you intentionally hold a HRM near a combo
#define COMBO_MUST_HOLD_MODS

// ─────────────────────────────────────────
// Caps Word
// ─────────────────────────────────────────

// Auto-disable Caps Word after 5 seconds of inactivity
#define CAPS_WORD_IDLE_TIMEOUT 5000

// ─────────────────────────────────────────
// Key overrides
// ─────────────────────────────────────────

// No additional override config needed; handled in keymap.c
