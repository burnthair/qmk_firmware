// Below layout is based upon /u/That-Canadian's planck layout
#include QMK_KEYBOARD_H

bool is_alt_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.

enum custom_keycodes {          // Make sure have the awesome keycode ready
  CMD_TAB = SAFE_RANGE,
  EMAIL,
  PASSWORD
};

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
//#define _QWERTY 0
//#define _FUNC 15

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * ,---------------------------.
 * | f5 shift   | f1 layer 2   |
 * |------------+--------------|
 * | f6 cmd + c | f2 email     |
 * |------------+--------------|
 * | f7 cmd + f | f3 password  |
 * |------------+--------------|
 * | f8 cmd + p | f4 cmd + tab |
 * `---------------------------'
 */
[0] = LAYOUT( \
    KC_LSHIFT , MO(1),  \
    LGUI(KC_C), KC_4, \
    LGUI(KC_F), KC_6, \
    LGUI(KC_P), CMD_TAB \
),

/*
 * ,-------------.
 * | f5   | f1   |
 * |------+------|
 * | f6   | f2   |
 * |------+------|
 * | f7   | f3   |
 * |------+------|
 * | f8   | f4   |
 * `-------------'
 */
[1] = LAYOUT( \
    _______, _______, \
    _______, _______, \
    _______, _______, \
    _______, _______  \
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case CMD_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LGUI);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case EMAIL:
      if (record->event.pressed) {
        SEND_STRING("medwards@liveareacx.com");
      } else {
      }
      break;
    case PASSWORD:
      if (record->event.pressed) {
        SEND_STRING("RVUEo6oU8hj2");
      }
  }
  return true;
}

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 600) {
      unregister_code(KC_LGUI);
      is_alt_tab_active = false;
    }
  }
}

void matrix_init_user(void) {

}
