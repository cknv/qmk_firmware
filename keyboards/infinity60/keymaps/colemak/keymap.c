#include QMK_KEYBOARD_H

#define TAPPING_TERM 175

enum custom_keycodes {
    GNAV = SAFE_RANGE,
};
bool is_gross_nav_active = false;

enum {
    GRESC,
};
qk_tap_dance_action_t tap_dance_actions[] = {
    [GRESC] = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_ESC),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Bksp|  |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  F|  P|  G|  J|  L|  U|  Y|  ;|  [|  ]| \   |
     * |-----------------------------------------------------------|
     * |Bksp  |  A|  R|  S|  T|  D|  H|  N|  E|  I|  O|  '|Enter   |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  K|  M|  ,|  .|  /|Shift |   |
     * |-----------------------------------------------------------'
     * |Ctrl |Gui|Alt  |         Space         |Alt  |Gui|Fn2|Fn1  |
     * `-----------------------------------------------------------'
     */
    [0] = LAYOUT_60_ansi_split_bs_rshift(
      TD(GRESC), KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC, _______,\
      KC_TAB,    KC_Q,   KC_W,   KC_F,   KC_P,   KC_G,   KC_J,   KC_L,   KC_U,   KC_Y,   KC_SCLN,KC_LBRC,KC_RBRC,KC_BSLS, \
      LT(2, KC_BSPC),   KC_A,   KC_R,   KC_S,   KC_T,   KC_D,   KC_H,   KC_N,   KC_E,   KC_I,   KC_O,   KC_QUOT,KC_ENT,  \
      KC_LSFT,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_K,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,KC_NO, \
      KC_LCTL,   KC_LGUI,KC_LALT,          LT(3, KC_SPC),       KC_RALT,KC_RGUI,LT(2, KC_DOWN), LT(1, KC_UP)),

    /* Layer 1: Navigation
     * ,-----------------------------------------------------------.
     * |   | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Del|   |
     * |-----------------------------------------------------------|
     * |     |   |Up |   |   |   |   |   |   |   |   |   |   |     |
     * |-----------------------------------------------------------|
     * |      |Lef|Dow|Rig|   |   |   |   |   |   |   |   |        |
     * |-----------------------------------------------------------|
     * |        |   |   |   |   |   |   |   |   |   |   | GNAV |   |
     * `-----------------------------------------------------------'
     * |     |   |     |                       |     |   |   |     |
     * `-----------------------------------------------------------'
     */
    [1] = LAYOUT_60_ansi_split_bs_rshift(
      _______,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, _______, \
      _______,_______,  KC_UP,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, \
      _______,KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,_______,_______,_______,_______,_______,_______,_______,            \
      _______,_______,_______,_______,_______,_______,_______,_______,_______, _______,_______,GNAV,_______,            \
      _______,_______,_______,          _______,               _______,_______,_______,_______),

    /* Layer 2: Unused
     * ,-----------------------------------------------------------.
     * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * |-----------------------------------------------------------|
     * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
     * |-----------------------------------------------------------|
     * |      |   |   |   |   |   |   |   |   |   |   |   |        |
     * |-----------------------------------------------------------|
     * |        |   |   |   |   |   |   |   |   |   |   |      |   |
     * `-----------------------------------------------------------'
     * |     |   |     |                       |     |   |   |     |
     * `-----------------------------------------------------------'
     */
    [2] = LAYOUT_60_ansi_split_bs_rshift(
      _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   \
      _______,_______,_______,_______,_______,_______,_______,_______,KC_UP  ,_______,_______,_______,_______,_______,      \
      _______,_______,_______,_______,_______,_______,_______,KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,_______,            \
      _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,            \
      _______,_______,_______,          _______,               _______,_______,_______,_______),


    [3] = LAYOUT_60_ansi_split_bs_rshift(
      _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   \
      _______,_______,_______,_______,_______,_______,_______,_______,KC_UP  ,_______,_______,_______,_______,_______,      \
      GNAV,  _______,_______,_______,_______,_______,_______,KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,_______,            \
      _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,            \
      _______,_______,_______,          _______,               _______,_______,_______,_______),
};

void gross_nav(keyrecord_t *record, uint16_t fine, uint16_t gross) {
    if (is_gross_nav_active) {
        if (record->event.pressed) {
            register_code(gross);
        } else {
            unregister_code(gross);
        }
    } else {
        if (record->event.pressed) {
            register_code(fine);
        } else {
            unregister_code(fine);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GNAV:
            // Set gross navigations as active
            // overriding "arrows" keys to their page up/down, home and end equivalents
            is_gross_nav_active = record->event.pressed;
            return true;
            break;
        case KC_UP:
            // Override up to page up, when gross navigation is active
            gross_nav(record, KC_UP, KC_PGUP);
            return false;
            break;
        case KC_DOWN:
            // Override down to page down, when gross navigation is active
            gross_nav(record, KC_DOWN, KC_PGDN);
            return false;
            break;
        case KC_LEFT:
            // Override left to home, when gross navigation is active
            gross_nav(record, KC_LEFT, KC_HOME);
            return false;
            break;
        case KC_RGHT:
            // Override right to end, when gross navigation is active
            gross_nav(record, KC_RGHT, KC_END);
            return false;
            break;
    }

    return true;
}
