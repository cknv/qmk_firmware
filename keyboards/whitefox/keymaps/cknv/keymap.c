#include QMK_KEYBOARD_H

#define TAPPING_TERM 100
#define TAP_CODE_DELAY 10

enum {
    GRESC,
};

enum custom_keycodes {
    GNAV = SAFE_RANGE,
};
bool is_gross_nav_active = false;
uint16_t gross_nav_kc = 0;
uint16_t gross_nav_timer = 0;
static const uint8_t GROSS_NAV_MULTIPLIER = 8;

// Custom grave/esc tap logic.
// Press once for one grace, twice for esc, and three times for three graves.
void grave_esc_tap(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code(KC_GRV);
            break;
        case 2:
            tap_code(KC_ESC);
            break;
        case 3:
            tap_code(KC_GRV);
            tap_code(KC_GRV);
            tap_code(KC_GRV);
            break;
    }
    reset_tap_dance(state);
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [GRESC] = ACTION_TAP_DANCE_FN(grave_esc_tap),
};


const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Default Colemak Laylout.
    [0] = LAYOUT(
        TD(GRESC), KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL,_______,KC_BSPC,_______,\
        KC_TAB,    KC_Q,   KC_W,   KC_F,   KC_P,   KC_G,   KC_J,   KC_L,   KC_U,   KC_Y,   KC_SCLN,KC_LBRC,KC_RBRC,KC_BSLS,          DF(3),\
        KC_BSPC,   KC_A,   KC_R,   KC_S,   KC_T,   KC_D,   KC_H,   KC_N,   KC_E,   KC_I,   KC_O,   KC_QUOT,_______, KC_ENT,        _______,\
        KC_LSFT,   _______,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_K,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,          KC_UP,_______,\
        KC_LCTL,   KC_LGUI,KC_LALT,            LT(1, KC_SPC),           KC_RGUI,  KC_RCTL, _______,                KC_LEFT,KC_DOWN,KC_RGHT \
    ),
    // Space activated layer, navigation and misc.
    [1] = LAYOUT(
        _______,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,_______, KC_DEL,_______,\
        _______,KC_MSTP,KC_MPLY,_______,_______,_______,_______,_______,  KC_UP,_______,_______,KC_VOLD,KC_VOLU,_______,        _______,\
        _______,KC_LSFT,KC_LCTL,  MO(2),   GNAV,_______,_______,KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,_______,_______,        _______,\
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,_______,\
        _______,_______,_______,                  _______,           _______,  _______, _______,                _______,_______,_______ \
    ),
    // Replace arrows with page up/down, home, and end.
    [2] = LAYOUT(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,\
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
};

// Repeats a keycode a bunch of times.
// This enables a style of navigation that between up/down and page up/down.
void gross_nav(uint16_t kc) {
    for (int i = 0; i < GROSS_NAV_MULTIPLIER; i++) {
        tap_code(kc);
    }
}

// Starts a gross navigation loop if GNAV and the event is pressed.
// Otherwise resets gross_nav_kc, which stops the loop.
// The loop consists of registering some data that the matrix_scan_user picks up on.
bool register_gross_nav(keyrecord_t *record, uint16_t kc) {
    if (is_gross_nav_active && record->event.pressed) {
        gross_nav_kc = kc;
        gross_nav_timer = timer_read();
        gross_nav(gross_nav_kc);
        return false;
    }
    gross_nav_kc = 0;
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GNAV:
            // Set gross navigations as active
            is_gross_nav_active = record->event.pressed;
            if (!record->event.pressed) {
                gross_nav_kc = 0;
            }
            return true;
            break;
        case KC_UP:
        case KC_DOWN:
        case KC_LEFT:
        case KC_RGHT:
            return register_gross_nav(record, keycode);
            break;
    }

    return true;
}

void matrix_scan_user(void) {
    if (gross_nav_kc != 0 && timer_elapsed(gross_nav_timer) > 150) {
            gross_nav(gross_nav_kc);
            gross_nav_timer = timer_read();
    }
}
