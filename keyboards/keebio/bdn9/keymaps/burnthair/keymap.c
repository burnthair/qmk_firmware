/* Copyright 2019 Danny Nguyen <danny@keeb.io>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define _REAPER 0
#define _MEDIA 1

bool left_secondary = false;
bool middle_secondary = false;
bool right_secondary = false;

enum custom_keycodes {
    LEFT_ENC = SAFE_RANGE,
    RIGHT_ENC,
    MIDDLE_ENC,
    SPOT,
};

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | LAYOUT 0: REAPER
        | Knob 1: Zoom X       | Knob 2: Zoom Y       | Knob 3: Horizontal Scroll |
        | Knob 1: Track Volume | Knob 2: Select Track | Knob 3: Vertical Scroll   |
        | Toggle Layer 1       | Home                 | End                       |
        | Arm Track (F13)      | Record (Ctrl + r)    | Play (Spacebar)           |
     */
    [_REAPER] = LAYOUT(
        LEFT_ENC  , MIDDLE_ENC, RIGHT_ENC,
        TO(_MEDIA), KC_HOME   , KC_END   ,
        KC_F13    , LCTL(KC_R), KC_SPACE
    ),
    /*
        TODO Knob 3 Volume
        TODO Copy Song Link
        TODO Open Spotify
        TODO Play button opens iTunes instead of Spotify
        | LAYOUT 1: Media
        | N/A            | N/A                            | Knob 3: Volume |
        | N/A            | N/A                            | Mute Volume    |
        | Toggle Layer 0 | Copy Song Link (Cmd + Alt + C) | Open Spotify   |
        | Media Previous | Media Play                     | Media Next     |
     */
    [_MEDIA] = LAYOUT(
        _______    , _______         , KC_MUTE,
        TO(_REAPER), LGUI(LALT(KC_C)), SPOT   ,
        KC_MPRV    , KC_MPLY         , KC_MNXT
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        case _LEFT:
            if (clockwise) {
                if (left_secondary) {
                    SEND_STRING(SS_LCTL(SS_TAP(X_UP)));
                } else {
                    tap_code(KC_MS_WH_UP);
                }
            } else {
                if (left_secondary) {
                    SEND_STRING(SS_LCTL(SS_TAP(X_DOWN)));
                } else {
                    tap_code(KC_MS_WH_DOWN);
                }
            }
        case _RIGHT:
            if (clockwise) {
                if (right_secondary) {
                    SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_MS_WH_UP))));
                } else {
                    SEND_STRING(SS_LALT(SS_TAP(X_MS_WH_UP)));
                }
            } else {
                if (right_secondary) {
                    SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_MS_WH_DOWN))));
                } else {
                    SEND_STRING(SS_LALT(SS_TAP(X_MS_WH_DOWN)));
                }
            }
        case _MIDDLE:
            if (clockwise) {
                if (middle_secondary) {
                    SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_DOWN))));
                } else {
                    SEND_STRING(SS_LCTL(SS_TAP(X_MS_WH_UP)));
                }
            } else {
                if (middle_secondary) {
                    SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_UP))));
                } else {
                    SEND_STRING(SS_LCTL(SS_TAP(X_MS_WH_DOWN)));
                }
            }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LEFT_ENC:
            if (record->event.pressed) {
                left_secondary = !left_secondary;
            }
            return false;
        case RIGHT_ENC:
            if (record->event.pressed) {
                right_secondary = !right_secondary;
            }
            return false;
        case MIDDLE_ENC:
            if (record->event.pressed) {
                middle_secondary = !middle_secondary;
            }
            return false;
        case SPOT:  // Open Spotify
            SEND_STRING(SS_LGUI(SS_TAP(X_SPACE)));
            _delay_ms(100);
            SEND_STRING("spotify app");
            _delay_ms(100);
            SEND_STRING(SS_TAP(X_ENTER));
            return false;
        default:
            return true;
    }
}
