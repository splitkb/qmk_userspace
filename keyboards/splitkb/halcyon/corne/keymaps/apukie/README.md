# apukie — Halcyon Corne rev2 keymap

A QWERTY keymap for the **splitkb Halcyon Corne rev2** inspired by
[urob's ZMK config](https://github.com/urob/zmk-config). Ported to QMK with
timeless homerow mods, smart layers, and combos so you rarely need to leave
the home position.

---

## Building

```bash
# From your userspace root
qmk compile -kb splitkb/halcyon/corne/rev2 -km apukie

# Or flash directly (put keyboard in bootloader mode first)
qmk flash -kb splitkb/halcyon/corne/rev2 -km apukie
```

Or push to GitHub — Actions will build and publish a release automatically.

---

## Layer overview

```
BASE  →  QWERTY + timeless homerow mods
NAV   →  arrows / paging / OSM mods / window mgmt    (hold Bspc → NAV)
NUM   →  right-hand numpad + left GASC mods           (hold MO(NUM) thumb)
SYM   →  symbols                                      (hold OSft/SYM outer right thumb)
FUN   →  F-keys (numpad) + desktop + media            (hold MO(FUN) thumb)
SYS   →  system (BOOT / reset / EEPROM clear)         (hold Spc + Ent together)
```

---

## Thumb cluster

```
Left:   [ Bspc/NAV ] [ MO(NUM) ] [   Spc   ]   ← Spc is big key
Right:  [   Ent    ] [ MO(FUN) ] [ OSft/SYM]   ← Ent is big key
```

- `Bspc/NAV` — tap: Backspace, hold: NAV layer
- `MO(NUM)` — hold: NUM layer (no tap action)
- `MO(FUN)` — hold: FUN layer (no tap action)
- `OSft/SYM` — tap: one-shot Shift, hold: SYM layer
- `Spc + Ent` held together → **SYS layer** (combo)

---

## BASE

```
┌────────┬────┬────┬────┬────┬────┐     ┌────┬────┬────┬────┬────┬────────┐
│  Tab   │ Q  │ W  │ E  │ R  │ T  │     │ Y  │ U  │ I  │ O  │ P  │  FUN   │
├────────┼────┼────┼────┼────┼────┤     ├────┼────┼────┼────┼────┼────────┤
│  Esc   │A/⌘│S/⌥ │D/⇧ │F/⌃│ G  │     │ H  │J/⌃ │K/⇧ │L/⌥ │;/⌘│  '     │
├────────┼────┼────┼────┼────┼────┤     ├────┼────┼────┼────┼────┼────────┤
│  LCtl  │ Z  │ X  │ C  │ V  │ B  │     │ N  │ M  │ ,  │ .  │ /  │  LAlt  │
└────────┴────┴────┴─┬──┴─┬──┴─┬──┘     └─┬──┴─┬──┴─┬──┴────┴────┴────────┘
                     │Bspc│NUM │Spc        │Ent │FUN │OSft
                     │NAV │    │big        │big │    │SYM
                     └────┴────┴───        └────┴────┘
```

**Homerow mods (GASC order):**

| Finger | Left tap | Left hold | Right tap | Right hold |
|--------|----------|-----------|-----------|------------|
| Pinky  | `A`      | `⌘ GUI`   | `;`       | `⌘ GUI`    |
| Ring   | `S`      | `⌥ Alt`   | `L`       | `⌥ Alt`    |
| Middle | `D`      | `⇧ Shift` | `K`       | `⇧ Shift`  |
| Index  | `F`      | `⌃ Ctrl`  | `J`       | `⌃ Ctrl`   |

**Outer columns:** `Esc` (home-row left pinky), `LCtl` (bottom-left), `LAlt` (bottom-right), `MO(FUN)` (top-right — extra access to FUN without the thumb).

**Key overrides:** `Shift`+`,` → `;`   `Shift`+`.` → `:`

---

## NAV

```
┌──────┬──────┬──────┬──────┬──────┬──────┐     ┌──────┬──────┬──────┬──────┬──────┬──────┐
│      │Alt F4│SftTab│AltTab│      │      │     │      │ PgUp │ Bspc*│  ↑*  │ Del* │      │
├──────┼──────┼──────┼──────┼──────┼──────┤     ├──────┼──────┼──────┼──────┼──────┼──────┤
│      │OS ⌘  │OS ⌥  │OS ⇧ │OS ⌃ │      │     │      │ PgDn │  ←*  │  ↓*  │  →*  │ Ent  │
├──────┼──────┼──────┼──────┼──────┼──────┤     ├──────┼──────┼──────┼──────┼──────┼──────┤
│      │ Undo │ Redo │      │      │      │     │      │      │      │      │      │      │
└──────┴──────┴──────┴─┬────┴─┬────┴─┬────┘     └─┬────┴─┬────┴─┬────┴──────┴──────┴──────┘
                       │[NAV] │ NUM  │ Spc        │ Ent  │ FUN  │ OSft/SYM
                       └──────┴──────┘            └──────┴──────┘
```

**`*` = hold-tap** (hold ≥ 220ms):

| Key  | Tap        | Hold                       |
|------|------------|----------------------------|
| `←`  | Left       | `Home` (start of line)     |
| `→`  | Right      | `End` (end of line)        |
| `↑`  | Up         | `Ctrl+Home` (doc start)    |
| `↓`  | Down       | `Ctrl+End` (doc end)       |
| Bspc | Backspace  | `Ctrl+Bspc` (delete word)  |
| Del  | Delete     | `Ctrl+Del` (delete word)   |

Left hand: window mgmt on top (`Alt+F4`, `Shift+Tab`, `Alt+Tab`), one-shot mods on home row.

---

## NUM

```
┌──────┬──────┬──────┬──────┬──────┬──────┐     ┌──────┬──────┬──────┬──────┬──────┬──────┐
│      │      │      │      │      │      │     │      │  7   │  8   │  9   │      │ Bspc │
├──────┼──────┼──────┼──────┼──────┼──────┤     ├──────┼──────┼──────┼──────┼──────┼──────┤
│      │  ⌘  │  ⌥   │  ⇧   │  ⌃   │      │     │      │  4   │  5   │  6   │  +   │  *   │
├──────┼──────┼──────┼──────┼──────┼──────┤     ├──────┼──────┼──────┼──────┼──────┼──────┤
│      │      │      │      │      │      │     │  0   │  1   │  2   │  3   │  .   │  /   │
└──────┴──────┴──────┴─┬────┴─┬────┴─┬────┘     └─┬────┴─┬────┴─┬────┴──────┴──────┴──────┘
                       │[NAV] │[NUM] │ Spc        │ Ent  │ FUN  │ OSft/SYM
                       └──────┴──────┘            └──────┴──────┘
```

Numbers on the right hand. Left hand holds GASC mods for cross-hand shortcuts like `Ctrl+1`.

---

## SYM

```
┌──────┬──────┬──────┬──────┬──────┬──────┐     ┌──────┬──────┬──────┬──────┬──────┬──────┐
│      │  !   │  @   │  #   │  $   │  %   │     │  ^   │  &   │  *   │  (   │  )   │      │
├──────┼──────┼──────┼──────┼──────┼──────┤     ├──────┼──────┼──────┼──────┼──────┼──────┤
│      │  `   │  ~   │  |   │  \   │  _   │     │  -   │  =   │  +   │  {   │  }   │  "   │
├──────┼──────┼──────┼──────┼──────┼──────┤     ├──────┼──────┼──────┼──────┼──────┼──────┤
│      │      │      │      │      │      │     │      │      │  [   │  ]   │  :   │  ;   │
└──────┴──────┴──────┴─┬────┴─┬────┴─┬────┘     └─┬────┴─┬────┴─┬────┴──────┴──────┴──────┘
                       │[NAV] │ NUM  │ Spc        │ Ent  │ FUN  │[SYM]
                       └──────┴──────┘            └──────┴──────┘
```

All symbols. Top row mirrors the standard shift+number row.

---

## FUN

```
┌──────┬──────┬──────┬──────┬──────┬──────┐     ┌──────┬──────┬──────┬──────┬──────┬──────┐
│      │ F12  │  F7  │  F8  │  F9  │      │     │      │ |◀◀ │ Vol↑ │ ▶▶| │ Mute │      │
├──────┼──────┼──────┼──────┼──────┼──────┤     ├──────┼──────┼──────┼──────┼──────┼──────┤
│      │F11/⌘│ F4/⌥│ F5/⇧ │ F6/⌃ │      │     │      │DPrv/⌃│VDn/⇧ │DNxt/⌥│      │      │
├──────┼──────┼──────┼──────┼──────┼──────┤     ├──────┼──────┼──────┼──────┼──────┼──────┤
│      │ F10  │  F1  │  F2  │  F3  │      │     │      │PinApp│PinWin│DskMgr│      │      │
└──────┴──────┴──────┴─┬────┴─┬────┴─┬────┘     └─┬────┴─┬────┴─┬────┴──────┴──────┴──────┘
                       │[NAV] │ NUM  │ Spc        │ Ent  │[FUN] │ OSft/SYM
                       └──────┴──────┘            └──────┴──────┘
```

**Left hand** — F-keys in numpad arrangement. Home row hold-taps (tap = F-key, hold = mod):

| Key     | Tap | Hold    |
|---------|-----|---------|
| `F11/⌘` | F11 | `GUI`   |
| `F4/⌥`  | F4  | `Alt`   |
| `F5/⇧`  | F5  | `Shift` |
| `F6/⌃`  | F6  | `Ctrl`  |

**Right hand** — desktop + media. Home row hold-taps (tap = action, hold = one-shot mod):

| Key      | Tap           | Hold (one-shot) |
|----------|---------------|-----------------|
| `DPrv/⌃` | Prev Desktop  | `Ctrl`          |
| `VDn/⇧`  | Vol↓          | `Shift`         |
| `DNxt/⌥` | Next Desktop  | `Alt`           |

Top row: Prev/Vol↑/Next/Mute. Bottom row: `PinApp` (Alt+\`), `PinWin`, `DskMgr` (Mission Control).

> **OS note:** Desktop shortcuts default to macOS. Adjust `DSK_PREV`, `DSK_NEXT`, `DSK_MGR`, `PIN_WIN` at the top of `keymap.c`.

---

## SYS

```
┌──────┬──────┬──────┬──────┬──────┬──────┐     ┌──────┬──────┬──────┬──────┬──────┬──────┐
│      │      │      │      │      │      │     │      │      │      │      │      │      │
├──────┼──────┼──────┼──────┼──────┼──────┤     ├──────┼──────┼──────┼──────┼──────┼──────┤
│      │      │      │      │      │      │     │      │      │ BOOT │ RBT  │EECLR │      │
├──────┼──────┼──────┼──────┼──────┼──────┤     ├──────┼──────┼──────┼──────┼──────┼──────┤
│      │      │      │      │      │      │     │      │      │      │      │      │      │
└──────┴──────┴──────┴─┬────┴─┬────┴─┬────┘     └─┬────┴─┬────┴─┬────┴──────┴──────┴──────┘
                       │      │      │[SPC+ENT]   │[SPC+ENT]    │
                       └──────┴──────┘            └──────┴──────┘
```

Accessed by **holding `Spc` and `Ent` simultaneously**. All keys transparent except:

- `BOOT` — enter bootloader mode for flashing
- `RBT` — soft reset (reboot firmware)
- `EECLR` — clear EEPROM (reset all persistent settings)

The keys are placed on the right hand middle cluster to make accidental activation very unlikely.

---

## Combos

| Keys pressed       | Output          | Notes                        |
|--------------------|-----------------|------------------------------|
| `J` + `K`          | `Escape`        | Right index + middle         |
| `K` + `L`          | `Caps Word`     | Right middle + ring          |
| `D` + `F`          | `Caps Lock`     | Left middle + index          |
| `U` + `I`          | `[`             | Top row right                |
| `I` + `O`          | `]`             | Top row right                |
| `M` + `,`          | `-`             | Bottom row right             |
| `,` + `.`          | `=`             | Bottom row right             |
| `U` + `J` (vert)   | `(`             | Column 5, rows 0+1           |
| `I` + `K` (vert)   | `)`             | Column 6, rows 0+1           |
| `O` + `L` (vert)   | `{`             | Column 7, rows 0+1           |
| `P` + `;` (vert)   | `}`             | Column 8, rows 0+1           |
| `Spc` + `Ent`      | SYS layer (hold)| Both big thumb keys together |

Combos with homerow-mod keys use `COMBO_MUST_HOLD_MODS` so they only fire on quick taps, never on intentional mod holds.

---

## Tips for tuning timeless HRMs

If you get **false mod activations**:
- Same-hand rolls → increase `TAPPING_TERM` in `config.h` (currently 280ms for HRMs)
- Cross-hand rolls → try adding [Achordion](https://getreuer.info/posts/keyboards/achordion/index.html)

If HRMs **feel too slow to activate**:
- Decrease `TAPPING_TERM` (try 250ms or 220ms)

If key **repeat doesn't work** on HRM keys:
- Adjust `QUICK_TAP_TERM` in `config.h` (currently 175ms)
