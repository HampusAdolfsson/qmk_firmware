/* Copyright 2020 melonbred
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

#define MIDI_ADVANCED

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _GAMING,
    _LAYER1,
    _LAYER2,
};

// Defines Combos for use in the keymap
enum combo_events {
  COMBO_SLSH,
};

enum tap_dance_events {
  TD_AA,
  TD_AE,
  TD_OE,
};

enum unicode_names {
  AA,
  AA_CAP,
  AE,
  AE_CAP,
  OE,
  OE_CAP,
};

const uint32_t PROGMEM unicode_map[] = {
  [AA]     = 0x00E5,  // å
  [AA_CAP] = 0x00C5,  // Å
  [AE]     = 0x00E4,  // ä
  [AE_CAP] = 0x00C4,  // Ä
  [OE]     = 0x00F6,  // ö
  [OE_CAP] = 0x00D6,  // Ö
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_AA] = ACTION_TAP_DANCE_DOUBLE(KC_Q, XP(AA, AA_CAP)),
  [TD_AE] = ACTION_TAP_DANCE_DOUBLE(KC_A, XP(AA, AA_CAP)),
  [TD_OE] = ACTION_TAP_DANCE_DOUBLE(KC_A, XP(AA, AA_CAP)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_bar(
        KC_GESC,             TD(TD_AA),        TD(TD_AE), KC_E,                KC_R,   KC_T,   KC_Y,    KC_U,    KC_I,        TD(TD_OE),            KC_P,    KC_BSPC, KC_MPLY,
        LT(_LAYER2, KC_TAB), KC_A,             KC_S,      KC_D,                KC_F,   KC_G,   KC_H,    KC_J,    KC_K,        KC_L,                 KC_SCLN,           KC_MFFD,
        KC_LSFT,             KC_Z,             KC_X,      KC_C,                KC_V,   KC_B,   KC_N,    KC_M,    KC_COMM,     MT(MOD_RSFT, KC_DOT), KC_UP,            KC_MRWD,
        KC_LCTL,             KC_LGUI,          KC_LALT,   KC_SPC,              LT(_LAYER1, KC_ENT),     KC_SLSH, KC_QUOT,     KC_LEFT,              KC_DOWN,          KC_RGHT
    ),

    [_GAMING] = LAYOUT_split_bar(
        KC_ESC,  KC_1,    KC_2,    KC_3,      KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, _______,
        KC_TAB,  KC_EXLM, KC_W,    KC_LBRC,   KC_HASH, KC_DLR,  KC_PERC, _______, KC_SCLN, KC_QUOT, _______,         _______,
        _______, KC_A,    KC_S,    KC_D,      _______, _______, _______, _______, _______, _______, _______,         _______,
        _______, KC_LGUI, _______, _______,          _______,          _______, _______, _______, _______,         _______
    ),

    [_LAYER1] = LAYOUT_split_bar(
        KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_MINS, KC_EQL, KC_DEL,
        KC_EXLM, KC_AT,   KC_HASH,  KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC, KC_BSLS,         KC_INS,
        _______, MI_C,    _______,  _______, KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_QUOT, _______, _______,         _______,
        _______, _______, _______,  _______,          _______,          _______, _______, _______, _______,         _______
    ),

    [_LAYER2] = LAYOUT_split_bar(
        KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   _______,  _______,  _______,  _______,
        XXXXXXX, MI_VEL_1,KC_UP,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  RGB_M_K, RGB_M_G, RGB_M_R, RGB_M_SW,         RGB_HUI,
        XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, RESET,   XXXXXXX, XXXXXXX, XXXXXXX, RGB_VAI, RGB_VAD,          RGB_HUD,
        _______, RGB_TOG, XXXXXXX, KC_VOLD,          KC_VOLU,          XXXXXXX, XXXXXXX, KC_DEL,  KC_RALT,          KC_RCTL
    ),
};

#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_slsh[] = {MT(MOD_RSFT, KC_DOT), KC_COMM, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
  [COMBO_SLSH] = COMBO(combo_slsh,KC_SLSH),

};
#endif

#ifdef MIDI_ENABLE
// MidiDevice device;

void keyboard_post_init_user(void) {
  // midi_device_init(&device);
  // midi_init();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // midi_device_process(&device);
  // process_midi(keycode, record);
  return true;
}
#endif

#ifdef RAW_ENABLE
bool hid_is_connected = false;

void raw_hid_receive(uint8_t *data, uint8_t length) {
  hid_is_connected = true;
}
#endif