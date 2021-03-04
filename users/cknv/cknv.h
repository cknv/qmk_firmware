#include QMK_KEYBOARD_H

static const uint8_t GROSS_NAV_MULTIPLIER = 8;

enum {
    GRESC,
};

enum custom_keycodes {
    GNAV = SAFE_RANGE,
};

void gross_nav(uint16_t kc);

void grave_esc_tap(qk_tap_dance_state_t *state, void *user_data);
