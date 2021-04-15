#include QMK_KEYBOARD_H
#include "cknv.h"

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Default Colemak Laylout.
    [0] = LAYOUT(
        TD(GRESC), KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL,_______,KC_BSPC,_______,\
        KC_TAB,    KC_Q,   KC_W,   KC_F,   KC_P,   KC_G,   KC_J,   KC_L,   KC_U,   KC_Y,   KC_SCLN,KC_LBRC,KC_RBRC,KC_BSLS,          DF(3),\
        KC_DEL ,   KC_A,   KC_R,   KC_S,   KC_T,   KC_D,   KC_H,   KC_N,   KC_E,   KC_I,   KC_O,   KC_QUOT,_______, KC_ENT,         OSL(4),\
        KC_LSFT,   _______,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_K,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,          KC_UP,_______,\
        KC_LCTL,   KC_LGUI,KC_LALT,            LT(1, KC_SPC),           KC_RGUI,  KC_RCTL, _______,                KC_LEFT,KC_DOWN,KC_RGHT \
    ),
    // Space activated layer, navigation and misc.
    [1] = LAYOUT(
        _______,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,_______,_______,_______,\
        _______,KC_MSTP,KC_MPLY,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,  KC_UP,XXXXXXX,XXXXXXX,KC_VOLD,KC_VOLU,XXXXXXX,        _______,\
        _______,KC_LSFT,KC_LCTL,  MO(2),   GNAV,XXXXXXX,XXXXXXX,KC_LEFT,KC_DOWN,KC_RGHT,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,        _______,\
        _______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,        _______,_______,\
        _______,_______,_______,                  _______,           _______,  _______, _______,                _______,_______,_______ \
    ),
    // Replace arrows with page up/down, home, and end.
    [2] = LAYOUT(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,RESET  ,\
        _______,_______,_______,_______,_______,_______,_______,_______,KC_PGUP,_______,_______,_______,_______,_______,        _______,\
        _______,_______,_______,_______,_______,_______,_______,KC_HOME,KC_PGDN,KC_END ,_______,_______,_______,_______,        _______,\
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,_______,\
        _______,_______,_______,                  _______,           _______,  _______, _______,                _______,_______,_______ \
    ),
    // Switch to QWERTY mode for games where remapping keys is not allowed.
    [3] = LAYOUT(
        KC_ESC,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,KC_MINS, KC_EQL,_______,KC_BSPC,_______,\
        KC_TAB,    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,KC_LBRC,KC_RBRC,KC_BSLS,          DF(0),\
        KC_CAPS,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,KC_SCLN,KC_QUOT,_______, KC_ENT,        _______,\
        KC_LSFT,_______,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,KC_RSFT,          KC_UP,_______,\
        KC_LCTL,KC_LGUI,KC_LALT,                  KC_SPC,           KC_RGUI,  KC_RCTL, _______,                 KC_LEFT,KC_DOWN,KC_RGHT \
    ),
    // DK unicode layout
    [4] = LAYOUT(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,\
        _______,KC_AE,  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,\
        _______,KC_OE,  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,\
        _______,_______,KC_AA,  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,_______,\
        _______,_______,_______,                  _______,           _______,  _______, _______,                _______,_______,_______ \
    ),
};
