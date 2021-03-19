#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _WIN 0
#define _FN1 1
#define _MAC 2
#define ENCODER_RESOLUTION 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_WIN] = LAYOUT_65_with_macro(
    KC_NO, KC_GRAVE,     KC_ESC,       KC_1,   KC_2,   KC_3,    KC_4,  KC_5,KC_6,  /**/  KC_7,  KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC,KC_DEL, KC_MUTE,\
    KC_F1, KC_F2,        KC_TAB,       KC_Q,   KC_W,   KC_E,    KC_R,  KC_T,       /**/  KC_Y,  KC_U,   KC_I,   KC_O,   KC_P,    KC_LBRC,KC_RBRC,KC_BSLS,KC_PGUP,\
    KC_F3, KC_F4,        KC_LCTL,      KC_A,   KC_S,   KC_D,    KC_F,  KC_G,       /**/  KC_H,  KC_J,   KC_K,   KC_L,   KC_SCLN, KC_QUOT,KC_ENT,         KC_PGDN,\
    KC_F5, KC_F6,        LCTL(KC_LSFT),KC_LSFT,KC_Z,   KC_X,    KC_C,  KC_V,KC_B,  /**/  KC_N,  KC_M,   KC_COMM,KC_DOT, KC_SLSH, KC_RSFT,        KC_UP,  KC_END ,\
    KC_F7, KC_F8,        KC_LCTL      ,KC_LGUI,KC_LALT,MO(_FN1),KC_SPC,            /**/  KC_SPC,KC_BSPC,        KC_RALT,KC_RCTL,MO(_FN1),KC_LEFT,KC_DOWN,KC_RGHT
  ),

  [_FN1] = LAYOUT_65_with_macro(
    KC_F9  ,KC_F10 ,     RGB_TOG, RGB_MOD, _______, _______, _______, _______, _______,  /**/  _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    KC_F11 ,KC_F12 ,     _______, _______, KC_UP,   _______, _______, _______,           /**/  _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, \
    _______,_______,     KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,           /**/  _______, _______, _______, _______, _______, _______, _______,          KC_VOLD, \
    _______,_______,     _______, _______, _______, _______, _______, _______, _______,  /**/  _______, TG(_MAC),KC_MPRV, KC_MNXT, KC_MPLY, _______,          _______, _______, \
    _______,_______,     _______, _______, _______, _______, _______,                    /**/  _______, _______,          _______, _______, _______, KC_HOME, _______, KC_END
  ),

  [_MAC] = LAYOUT_65_with_macro(
    _______,_______,     _______,      _______,_______,_______,_______,_______,_______,  /**/  _______,_______,_______,_______,_______,_______,_______,_______,_______,\
    _______,_______,     _______,      _______,_______,_______,_______,_______,          /**/  _______,_______,_______,_______,_______,_______,_______,_______,_______,\
    _______,_______,     _______,      _______,_______,_______,_______,_______,          /**/  _______,_______,_______,_______,_______,_______,_______,        _______,\
    _______,_______,     LGUI(KC_LSFT),_______,_______,_______,_______,_______,_______,  /**/  _______,_______,_______,_______,_______,_______,        _______,_______,\
    _______,_______,     _______      ,KC_LALT,KC_LGUI,_______,_______,                  /**/  _______,_______,        KC_RALT,KC_RGUI,_______,_______,_______,_______
  )
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code16(LALT(KC_RGHT));
        } else {
            tap_code16(LALT(KC_LEFT));
        }
    }
    // else if (index == 1) {
    //     if (clockwise) {
    //         tap_code(KC_VOLU);
    //     } else {
    //         tap_code(KC_VOLD);
    //     }
    // }
}
