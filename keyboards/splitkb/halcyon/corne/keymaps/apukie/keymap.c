// ============================================================
//  urob-inspired QWERTY keymap for splitkb Halcyon Corne rev2
//  Features:
//   - Timeless homerow mods (GASC order)
//   - 6 layers: BASE / NAV / NUM / SYM / FUN / SYS
//   - Combos for brackets, escape, caps word, and SPC+ENT→SYS
//   - Num Word (smart num layer that auto-deactivates)
//   - Key overrides: Shift+, → ;   Shift+. → :
//   - NAV cluster hold-taps (tap=nav, hold=extended nav)
//   - FUN left home row: hold-tap F-keys (tap=Fkey, hold=mod)
//   - FUN right home row: hold-tap desktop keys (tap=desktop, hold=mod)
//   - Thumb cluster:
//       Left:  [Bspc/NAV]  [MO(NUM)]  [Spc]
//       Right: [Ent]       [MO(FUN)]  [OSft/SYM]
// ============================================================

#include QMK_KEYBOARD_H

// ─────────────────────────────────────────
// Layer index
// ─────────────────────────────────────────
enum layers {
    BASE,
    NAV,
    NUM,
    SYM,
    FUN,
    SYS,
};

// ─────────────────────────────────────────
// Desktop management macros
// Defaults are macOS. Adjust for your OS:
//   Windows: LCTL(LGUI(KC_LEFT/RIGHT)), LGUI(KC_TAB)
// ─────────────────────────────────────────
#define DSK_PREV  LCTL(KC_LEFT)    // Previous desktop (macOS: Ctrl+Left)
#define DSK_NEXT  LCTL(KC_RGHT)    // Next desktop     (macOS: Ctrl+Right)
#define DSK_MGR   LCTL(KC_UP)      // Mission Control  (macOS: Ctrl+Up)
#define PIN_APP   LALT(KC_GRV)     // Cycle same-app windows (macOS: Alt+`)
#define PIN_WIN   LGUI(LCTL(KC_F)) // Move window to all spaces (macOS shortcut)

// ─────────────────────────────────────────
// Custom keycodes
// ─────────────────────────────────────────
enum custom_keycodes {
    NUM_WORD = SAFE_RANGE, // Smart num layer toggle

    // NAV cluster hold-taps
    // Tap = nav key  |  Hold = extended navigation
    NAV_LEFT,   // tap: ←         | hold: Home       (start of line)
    NAV_RGHT,   // tap: →         | hold: End        (end of line)
    NAV_UP,     // tap: ↑         | hold: Ctrl+Home  (start of document)
    NAV_DOWN,   // tap: ↓         | hold: Ctrl+End   (end of document)
    NAV_BSPC,   // tap: Backspace | hold: Ctrl+Bspc  (delete word back)
    NAV_DEL,    // tap: Delete    | hold: Ctrl+Del   (delete word forward)

    // FUN right home row hold-taps
    // Tap = desktop/media key  |  Hold = modifier
    FUN_DPREV,  // tap: Prev Desktop | hold: Ctrl
    FUN_VOLD,   // tap: Vol↓         | hold: Shift
    FUN_DNEXT,  // tap: Next Desktop | hold: Alt

    // Right outer thumb
    OSFT_SYM,   // tap: One-shot Shift | hold: SYM layer
};

// ─────────────────────────────────────────
// Homerow mod aliases  (GASC = GUI·Alt·Shift·Ctrl)
// Left hand:  A=GUI  S=Alt  D=Shift  F=Ctrl
// Right hand: J=Ctrl K=Shift L=Alt  ;=GUI
// ─────────────────────────────────────────
#define HRM_A    LGUI_T(KC_A)
#define HRM_S    LALT_T(KC_S)
#define HRM_D    LSFT_T(KC_D)
#define HRM_F    LCTL_T(KC_F)

#define HRM_J    RCTL_T(KC_J)
#define HRM_K    RSFT_T(KC_K)
#define HRM_L    LALT_T(KC_L)
#define HRM_SCLN LGUI_T(KC_SCLN)

// ─────────────────────────────────────────
// FUN left home row hold-tap F-keys
// Tap = F-key  |  Hold = modifier
// Pinky=GUI/F11  Ring=Alt/F4  Middle=Shift/F5  Index=Ctrl/F6
// ─────────────────────────────────────────
#define FUN_F11  LGUI_T(KC_F11)
#define FUN_F4   LALT_T(KC_F4)
#define FUN_F5   LSFT_T(KC_F5)
#define FUN_F6   LCTL_T(KC_F6)

// ─────────────────────────────────────────
// Thumb aliases
//   Left:  BSPC_NAV = tap Bspc, hold NAV layer
//   Left:  MO(NUM)  = momentary NUM (used directly)
//   Right: MO(FUN)  = momentary FUN (used directly)
//   Right: OSFT_SYM = custom keycode (see process_record_user)
// ─────────────────────────────────────────
#define BSPC_NAV LT(NAV, KC_BSPC)

// ─────────────────────────────────────────
// Hold-tap tapping term for NAV cluster and
// FUN right home row — 220ms, snappy for nav.
// ─────────────────────────────────────────
#define NAV_TAPPING_TERM 220

// ─────────────────────────────────────────
// Combo indices — must match key_combos[] order
// ─────────────────────────────────────────
enum combos {
    COMBO_JK,
    COMBO_KL,
    COMBO_DF,
    COMBO_UI,
    COMBO_IO,
    COMBO_MCOMM,
    COMBO_COMMDOT,
    COMBO_UJ,
    COMBO_IK,
    COMBO_OL,
    COMBO_PSCLN,
    COMBO_SYS,   // SPC + ENT → momentary SYS layer
};

// ─────────────────────────────────────────
// Combo key sequences
// ─────────────────────────────────────────
const uint16_t PROGMEM combo_jk[]       = {HRM_J,   HRM_K,    COMBO_END};
const uint16_t PROGMEM combo_kl[]       = {HRM_K,   HRM_L,    COMBO_END};
const uint16_t PROGMEM combo_df[]       = {HRM_D,   HRM_F,    COMBO_END};
const uint16_t PROGMEM combo_ui[]       = {KC_U,    KC_I,     COMBO_END};
const uint16_t PROGMEM combo_io[]       = {KC_I,    KC_O,     COMBO_END};
const uint16_t PROGMEM combo_mcomm[]    = {KC_M,    KC_COMM,  COMBO_END};
const uint16_t PROGMEM combo_commdot[]  = {KC_COMM, KC_DOT,   COMBO_END};
const uint16_t PROGMEM combo_uj[]       = {KC_U,    HRM_J,    COMBO_END};
const uint16_t PROGMEM combo_ik[]       = {KC_I,    HRM_K,    COMBO_END};
const uint16_t PROGMEM combo_ol[]       = {KC_O,    HRM_L,    COMBO_END};
const uint16_t PROGMEM combo_pscln[]    = {KC_P,    HRM_SCLN, COMBO_END};
const uint16_t PROGMEM combo_sys[]      = {KC_SPC,  KC_ENT,   COMBO_END};

combo_t key_combos[] = {
    // Horizontal
    [COMBO_JK]       = COMBO(combo_jk,      KC_ESC),
    [COMBO_KL]       = COMBO(combo_kl,      CW_TOGG),
    [COMBO_DF]       = COMBO(combo_df,      KC_CAPS),
    [COMBO_UI]       = COMBO(combo_ui,      KC_LBRC),
    [COMBO_IO]       = COMBO(combo_io,      KC_RBRC),
    [COMBO_MCOMM]    = COMBO(combo_mcomm,   KC_MINS),
    [COMBO_COMMDOT]  = COMBO(combo_commdot, KC_EQL),
    // Vertical
    [COMBO_UJ]       = COMBO(combo_uj,      KC_LPRN),
    [COMBO_IK]       = COMBO(combo_ik,      KC_RPRN),
    [COMBO_OL]       = COMBO(combo_ol,      KC_LCBR),
    [COMBO_PSCLN]    = COMBO(combo_pscln,   KC_RCBR),
    // SYS layer (COMBO_ACTION — handled in process_combo_event)
    [COMBO_SYS]      = COMBO_ACTION(combo_sys),
};

// ─────────────────────────────────────────
// process_combo_event
// Activates SYS layer while SPC+ENT are
// held together; deactivates on release.
// ─────────────────────────────────────────
void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case COMBO_SYS:
            if (pressed) {
                layer_on(SYS);
            } else {
                layer_off(SYS);
            }
            break;
    }
}

// ─────────────────────────────────────────
// Key overrides
//   Shift + ,  →  ;
//   Shift + .  →  :
// ─────────────────────────────────────────
const key_override_t comma_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
const key_override_t dot_override   = ko_make_basic(MOD_MASK_SHIFT, KC_DOT,  KC_COLN);

const key_override_t *key_overrides[] = {
    &comma_override,
    &dot_override,
    NULL,
};

// ─────────────────────────────────────────
// Keymaps
// ─────────────────────────────────────────

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// ┌─────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ BASE – QWERTY with timeless homerow mods                                                        │
// │                                                                                                 │
// │  TAB   Q    W    E    R    T    ║   Y    U    I    O    P   [FUN]                               │
// │  ESC   A*   S*   D*   F*   G   ║   H    J*   K*   L*   ;*   '                                  │
// │  LCTL  Z    X    C    V    B   ║   N    M    ,    .    /   LALT                                 │
// │         Bspc/NAV  NUM   Spc    ║      Ent   FUN  OSft/SYM                                      │
// │              ─    ─    ^^^big  ║      ^^^big  ─    ─                                            │
// │                                                                                                 │
// │  SPC + ENT held together → SYS layer (combo)                                                   │
// └─────────────────────────────────────────────────────────────────────────────────────────────────┘
  [BASE] = LAYOUT_split_3x6_3(
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    MO(FUN),
    KC_ESC,   HRM_A,   HRM_S,   HRM_D,   HRM_F,   KC_G,         KC_H,    HRM_J,   HRM_K,   HRM_L,   HRM_SCLN,KC_QUOT,
    KC_LCTL,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LALT,
                                BSPC_NAV,MO(NUM), KC_SPC,       KC_ENT,  MO(FUN), OSFT_SYM
  ),

// ┌─────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ NAV – Navigation + editing (urob-style)                                                         │
// │                                                                                                 │
// │  ─── ClsWin PrvTab AltTab  ───  ───  ║  ───  PGUP  BSPC*   UP*  DEL*  ───                      │
// │  ─── OS⌘   OS⌥   OS⇧   OS⌃   ───  ║  ───  PGDN  LEFT*  DWN*   →*   ENT                       │
// │  ─── UNDO  REDO   ───    ───   ───  ║  ───   ───    ───   ───   ───   ───                       │
// │          [NAV]   NUM    Spc         ║      Ent    FUN  OSft/SYM                                 │
// │                                                                                                 │
// │  * hold-taps:  BSPC→Ctrl+Bspc  DEL→Ctrl+Del                                                    │
// │                LEFT→Home  →→End  ↑→Ctrl+Home  ↓→Ctrl+End                                       │
// └─────────────────────────────────────────────────────────────────────────────────────────────────┘
  [NAV] = LAYOUT_split_3x6_3(
    _______, LALT(KC_F4),   LSFT(KC_TAB),  LALT(KC_TAB),  _______, _______,      _______, KC_PGUP,  NAV_BSPC, NAV_UP,   NAV_DEL,  _______,
    _______, OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LSFT), OSM(MOD_LCTL), _______,_______, KC_PGDN,  NAV_LEFT, NAV_DOWN, NAV_RGHT, KC_ENT,
    _______, KC_UNDO,       KC_AGIN,       _______,        _______, _______,      _______, _______,  _______,  _______,  _______,  _______,
                                           _______,        _______, _______,      _______, _______,  _______
  ),

// ┌─────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ NUM – GASC mods on left, numpad on right                                                        │
// │                                                                                                 │
// │  ───   ───   ───   ───   ───   ───  ║  ───   7    8    9    ───  BSPC                           │
// │  ───   GUI   ALT   SFT   CTL   ───  ║  ───   4    5    6    +    *                              │
// │  ───   ───   ───   ───   ───   ───  ║   0    1    2    3    .    /                              │
// │          Bspc/NAV [NUM]  Spc        ║      Ent    FUN  OSft/SYM                                 │
// └─────────────────────────────────────────────────────────────────────────────────────────────────┘
  [NUM] = LAYOUT_split_3x6_3(
    _______, _______, _______, _______, _______, _______,      _______, KC_7,    KC_8,    KC_9,    _______, KC_BSPC,
    _______, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, _______,      _______, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_ASTR,
    _______, _______, _______, _______, _______, _______,      KC_0,    KC_1,    KC_2,    KC_3,    KC_DOT,  KC_SLSH,
                               _______, _______, _______,      _______, _______, _______
  ),

// ┌─────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ SYM – Symbols                                                                                   │
// │                                                                                                 │
// │  ───    !    @    #    $    %   ║   ^    &    *    (    )    ───                                 │
// │  ───   GRV  TILD PIPE BSLS  _  ║   -    =    +   LCB  RCB   "                                  │
// │  ───   ───  ───  ───  ───  ───  ║  ───  ───   [    ]    :    ;                                  │
// │          Bspc/NAV  NUM   Spc    ║      Ent    FUN [SYM]                                         │
// └─────────────────────────────────────────────────────────────────────────────────────────────────┘
  [SYM] = LAYOUT_split_3x6_3(
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, KC_GRV,  KC_TILD, KC_PIPE, KC_BSLS, KC_UNDS,      KC_MINS, KC_EQL,  KC_PLUS, KC_LCBR, KC_RCBR, KC_DQUO,
    _______, _______, _______, _______, _______, _______,      _______, _______, KC_LBRC, KC_RBRC, KC_COLN, KC_SCLN,
                               _______, _______, _______,      _______, _______, _______
  ),

// ┌─────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ FUN – F-keys + desktop management (urob-style)                                                  │
// │                                                                                                 │
// │  ───  F12   F7    F8    F9    ───  ║  ───  MPRV  VOLU  MNXT  MUTE  ───                          │
// │  ─── F11/⌘ F4/⌥  F5/⇧  F6/⌃  ───  ║  ─── DPrv/⌃ VDn/⇧ DNxt/⌥  ───  ───                        │
// │  ───  F10   F1    F2    F3    ───  ║  ─── PinApp PinWin DskMgr ───  ───                         │
// │          Bspc/NAV  NUM   Spc       ║      Ent   [FUN]  OSft/SYM                                 │
// └─────────────────────────────────────────────────────────────────────────────────────────────────┘
  [FUN] = LAYOUT_split_3x6_3(
    _______, KC_F12,   KC_F7,   KC_F8,   KC_F9,   _______,      _______, KC_MPRV,  KC_VOLU,  KC_MNXT,  KC_MUTE, _______,
    _______, FUN_F11,  FUN_F4,  FUN_F5,  FUN_F6,  _______,      _______, FUN_DPREV,FUN_VOLD, FUN_DNEXT,_______, _______,
    _______, KC_F10,   KC_F1,   KC_F2,   KC_F3,   _______,      _______, PIN_APP,  PIN_WIN,  DSK_MGR,  _______, _______,
                                _______, _______, _______,      _______, _______,  _______
  ),

// ┌─────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ SYS – System (accessed by holding SPC + ENT simultaneously)                                     │
// │                                                                                                 │
// │  ───   ───   ───   ───   ───   ───  ║  ───   ───   ───   ───   ───   ───                        │
// │  ───   ───   ───   ───   ───   ───  ║  ───   ───  BOOT  RESET EECLR  ───                        │
// │  ───   ───   ───   ───   ───   ───  ║  ───   ───   ───   ───   ───   ───                        │
// │                   [SYS combo]       ║             [SYS combo]                                   │
// └─────────────────────────────────────────────────────────────────────────────────────────────────┘
  [SYS] = LAYOUT_split_3x6_3(
    _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,      _______, _______, QK_BOOT, QK_RBT,  EE_CLR,  _______,
    _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
                               _______, _______, _______,      _______, _______, _______
  ),
};
// clang-format on

// ─────────────────────────────────────────
// Timeless HRM: per-key tapping term
// HRMs: 280ms — insensitive to typing speed.
// All MT/LT hold-tap keys: TAPPING_TERM (200ms).
// ─────────────────────────────────────────
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HRM_A:
        case HRM_S:
        case HRM_D:
        case HRM_F:
        case HRM_J:
        case HRM_K:
        case HRM_L:
        case HRM_SCLN:
            return 280;
        default:
            return TAPPING_TERM;
    }
}

// ─────────────────────────────────────────
// Quick tap term
// HRMs + FUN hold-tap keys: 175ms
//   → double-tap within 175ms = key repeat
// Everything else: 0 (no repeat)
// ─────────────────────────────────────────
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HRM_A:
        case HRM_S:
        case HRM_D:
        case HRM_F:
        case HRM_J:
        case HRM_K:
        case HRM_L:
        case HRM_SCLN:
        case FUN_F11:
        case FUN_F4:
        case FUN_F5:
        case FUN_F6:
            return 175;
        default:
            return 0;
    }
}

// ─────────────────────────────────────────
// Permissive hold (per key)
// HRMs + FUN hold-tap F-keys: OFF (no misfire on rolls)
// Thumb LT keys: ON (layer activates immediately on
//   next keypress while held)
// ─────────────────────────────────────────
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HRM_A:
        case HRM_S:
        case HRM_D:
        case HRM_F:
        case HRM_J:
        case HRM_K:
        case HRM_L:
        case HRM_SCLN:
        case FUN_F11:
        case FUN_F4:
        case FUN_F5:
        case FUN_F6:
            return false;
        case BSPC_NAV:
            return true;
        default:
            return false;
    }
}

// ─────────────────────────────────────────
// Hold on other key press (per key)
// HRMs + FUN hold-tap F-keys: OFF (tap-preferred)
// BSPC_NAV: ON (NAV activates as soon as another
//   key is pressed while held)
// ─────────────────────────────────────────
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HRM_A:
        case HRM_S:
        case HRM_D:
        case HRM_F:
        case HRM_J:
        case HRM_K:
        case HRM_L:
        case HRM_SCLN:
        case FUN_F11:
        case FUN_F4:
        case FUN_F5:
        case FUN_F6:
            return false;
        case BSPC_NAV:
            return true;
        default:
            return false;
    }
}

// ─────────────────────────────────────────
// Hold-tap timers
// One per NAV cluster key and FUN right home row key.
// Held past NAV_TAPPING_TERM (220ms) → hold action.
// ─────────────────────────────────────────
static uint16_t nav_timers[6];
static uint16_t fun_r_timers[3];

// ─────────────────────────────────────────
// OSFT_SYM state
// Tracks whether the key was held long enough
// to activate SYM layer.
// ─────────────────────────────────────────
static uint16_t osft_sym_timer;
static bool     osft_sym_layer_active = false;

// ─────────────────────────────────────────
// Num Word state
// ─────────────────────────────────────────
static bool num_word_active = false;

static bool is_num_word_continuation(uint16_t keycode) {
    switch (keycode) {
        case KC_1 ... KC_0:
        case KC_PLUS:
        case KC_MINS:
        case KC_ASTR:
        case KC_SLSH:
        case KC_PERC:
        case KC_EQL:
        case KC_DOT:
        case KC_COMM:
        case KC_LPRN:
        case KC_RPRN:
        case KC_BSPC:
        case KC_DEL:
        case KC_LSFT ... KC_RGUI:
        case KC_LEFT_CTRL ... KC_RIGHT_GUI:
            return true;
        default:
            return false;
    }
}

// ─────────────────────────────────────────
// process_record_user
// ─────────────────────────────────────────
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // ── Num Word toggle ──────────────────
    if (keycode == NUM_WORD) {
        if (record->event.pressed) {
            num_word_active = !num_word_active;
            num_word_active ? layer_on(NUM) : layer_off(NUM);
        }
        return false;
    }

    // ── Num Word auto-exit ───────────────
    if (num_word_active && record->event.pressed) {
        if (!is_num_word_continuation(keycode)) {
            layer_off(NUM);
            num_word_active = false;
        }
    }

    switch (keycode) {

        // ── OSFT_SYM ─────────────────────
        // Press: start timer + activate SYM immediately
        //   (so hold feels instant — no delay)
        // Release < TAPPING_TERM: deactivate SYM + fire OSM shift
        // Release >= TAPPING_TERM: deactivate SYM only
        case OSFT_SYM:
            if (record->event.pressed) {
                osft_sym_timer = timer_read();
                osft_sym_layer_active = true;
                layer_on(SYM);
            } else {
                layer_off(SYM);
                osft_sym_layer_active = false;
                if (timer_elapsed(osft_sym_timer) < TAPPING_TERM) {
                    set_oneshot_mods(MOD_BIT(KC_LSFT)); // tap: one-shot shift
                }
            }
            return false;

        // ── NAV cluster hold-taps ────────
        case NAV_LEFT:
            if (record->event.pressed) { nav_timers[0] = timer_read(); }
            else {
                timer_elapsed(nav_timers[0]) < NAV_TAPPING_TERM
                    ? tap_code(KC_LEFT)             // tap: ←
                    : tap_code(KC_HOME);            // hold: Home
            }
            return false;

        case NAV_RGHT:
            if (record->event.pressed) { nav_timers[1] = timer_read(); }
            else {
                timer_elapsed(nav_timers[1]) < NAV_TAPPING_TERM
                    ? tap_code(KC_RGHT)             // tap: →
                    : tap_code(KC_END);             // hold: End
            }
            return false;

        case NAV_UP:
            if (record->event.pressed) { nav_timers[2] = timer_read(); }
            else {
                timer_elapsed(nav_timers[2]) < NAV_TAPPING_TERM
                    ? tap_code(KC_UP)               // tap: ↑
                    : tap_code16(LCTL(KC_HOME));    // hold: Ctrl+Home (doc start)
            }
            return false;

        case NAV_DOWN:
            if (record->event.pressed) { nav_timers[3] = timer_read(); }
            else {
                timer_elapsed(nav_timers[3]) < NAV_TAPPING_TERM
                    ? tap_code(KC_DOWN)             // tap: ↓
                    : tap_code16(LCTL(KC_END));     // hold: Ctrl+End (doc end)
            }
            return false;

        case NAV_BSPC:
            if (record->event.pressed) { nav_timers[4] = timer_read(); }
            else {
                timer_elapsed(nav_timers[4]) < NAV_TAPPING_TERM
                    ? tap_code(KC_BSPC)             // tap: Backspace
                    : tap_code16(LCTL(KC_BSPC));    // hold: Ctrl+Bspc (delete word)
            }
            return false;

        case NAV_DEL:
            if (record->event.pressed) { nav_timers[5] = timer_read(); }
            else {
                timer_elapsed(nav_timers[5]) < NAV_TAPPING_TERM
                    ? tap_code(KC_DEL)              // tap: Delete
                    : tap_code16(LCTL(KC_DEL));     // hold: Ctrl+Del (delete word)
            }
            return false;

        // ── FUN right home row hold-taps ─
        // Tap = desktop/media  |  Hold = one-shot mod
        case FUN_DPREV:
            if (record->event.pressed) { fun_r_timers[0] = timer_read(); }
            else {
                timer_elapsed(fun_r_timers[0]) < NAV_TAPPING_TERM
                    ? tap_code16(DSK_PREV)                      // tap: Prev Desktop
                    : set_oneshot_mods(MOD_BIT(KC_LCTL));       // hold: one-shot Ctrl
            }
            return false;

        case FUN_VOLD:
            if (record->event.pressed) { fun_r_timers[1] = timer_read(); }
            else {
                timer_elapsed(fun_r_timers[1]) < NAV_TAPPING_TERM
                    ? tap_code(KC_VOLD)                         // tap: Vol↓
                    : set_oneshot_mods(MOD_BIT(KC_LSFT));       // hold: one-shot Shift
            }
            return false;

        case FUN_DNEXT:
            if (record->event.pressed) { fun_r_timers[2] = timer_read(); }
            else {
                timer_elapsed(fun_r_timers[2]) < NAV_TAPPING_TERM
                    ? tap_code16(DSK_NEXT)                      // tap: Next Desktop
                    : set_oneshot_mods(MOD_BIT(KC_LALT));       // hold: one-shot Alt
            }
            return false;
    }

    return true;
}
