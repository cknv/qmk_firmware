#include "cknv.h"

static bool is_gross_nav_active = false;
static uint16_t gross_nav_kc = 0;
static uint16_t gross_nav_timer = 0;

qk_tap_dance_action_t tap_dance_actions[] = {
    [GRESC] = ACTION_TAP_DANCE_FN(grave_esc_tap),
    [M45] = ACTION_TAP_DANCE_DOUBLE(KC_BTN4, KC_BTN5),
};

const uint32_t PROGMEM unicode_map[] = {
    [UPPER_AE] = 0x00C6,
    [LOWER_AE] = 0x00E6,
    [UPPER_OE] = 0x00D8,
    [LOWER_OE] = 0x00F8,
    [UPPER_AA] = 0x00C5,
    [LOWER_AA] = 0x00E5,
};

// Repeats a keycode a bunch of times.
void gross_nav(uint16_t kc) {
    for (int i = 0; i < GROSS_NAV_MULTIPLIER; i++) {
        tap_code(kc);
    }
}

// Custom grave/esc tap logic.
// Press once for one grave, twice for esc, and three times for three graves.
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
    // Retrigger gross navigation at key matrix scan.
    if (gross_nav_kc != 0 && timer_elapsed(gross_nav_timer) > 150) {
            gross_nav_timer = timer_read();
            gross_nav(gross_nav_kc);
    }
}
