#include QMK_KEYBOARD_H

static const uint8_t GROSS_NAV_MULTIPLIER = 8;

enum {
    GRESC,
};

enum custom_keycodes {
    GNAV = SAFE_RANGE,
};

enum unicode_names {
    UPPER_AE,
    LOWER_AE,
    UPPER_OE,
    LOWER_OE,
    UPPER_AA,
    LOWER_AA,
};

#define KC_AE XP(LOWER_AE, UPPER_AE)
#define KC_OE XP(LOWER_OE, UPPER_OE)
#define KC_AA XP(LOWER_AA, UPPER_AA)

void gross_nav(uint16_t kc);

void grave_esc_tap(qk_tap_dance_state_t *state, void *user_data);
