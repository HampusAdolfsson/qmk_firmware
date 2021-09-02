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
#include "keymap_swedish.h"
#include "raw_hid.h"
#include "print.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    // _LMODS,
    _RMODS,
    _MISC,
    _GAMING,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_bar(
        KC_ESC,        KC_Q,     KC_W,    KC_E,                KC_R,   KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,                 KC_P,    KC_BSPC, KC_MPLY,
        LT(_MISC, KC_TAB), KC_A, KC_S,    KC_D,                KC_F,   KC_G,   KC_H,    KC_J,    KC_K,    KC_L,                 KC_ENT,           KC_MNXT,
        KC_LSFT,       KC_Z,     KC_X,    KC_C,                KC_V,   KC_B,   KC_N,    KC_M,    KC_COMM, MT(MOD_RSFT, KC_DOT), KC_UP,            KC_DEL,
        KC_LCTL,       KC_LGUI,  KC_LALT, KC_SPC,  LT(_RMODS, KC_SCLN),     KC_SLSH, KC_QUOT, KC_LEFT,              KC_DOWN,          KC_RGHT
    ),

    // [_LMODS] = LAYOUT_split_bar(
    //     KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PGUP,
    //     _______, KC_EXLM, KC_AT,    KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,           KC_PGDN,
    //     _______, KC_BSLS, KC_LCBR,  KC_LBRC, KC_LPRN, KC_RPRN, KC_RBRC, KC_RCBR, KC_UNDS, KC_PLUS, _______,          KC_PSCR,
    //     _______, _______, _______,  _______,          _______,          _______, KC_GRV,  _______, _______,          _______
    // ),

    [_RMODS] = LAYOUT_split_bar(
        KC_GRV,  KC_EXLM, KC_AT,    KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,  KC_PLUS, KC_PGUP,
        _______, KC_1,    KC_2,     KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,             KC_PGDN,
        _______, KC_BSLS, KC_LPRN,  KC_RPRN, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_UNDS, KC_PLUS, _______,          KC_PSCR,
        _______, _______, _______,  _______,          _______,          _______, KC_GRV,  _______, _______,          _______
    ),

    [_MISC] = LAYOUT_split_bar(
        // KC_DEL,  KC_HOME, KC_END,  KC_UP,   RGB_M_P, RGB_M_B,     RGB_M_R,  RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_M_X, RGB_M_G, KC_PSCR,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,       KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,
        _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, TG(_GAMING), KC_LEFT,  KC_DOWN, KC_UP,   KC_RGHT, _______,          KC_VOLU,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,       RGB_RMOD, RGB_MOD, RGB_VAD, RGB_VAI, RGB_HUI,          KC_VOLD,
        _______, RGB_TOG, XXXXXXX, XXXXXXX,          RGB_M_P,               XXXXXXX, RGB_TOG, RGB_VAD, RGB_HUD,          RGB_VAI
    ),

    [_GAMING] = LAYOUT_split_bar(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_TAB,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LOCK, _______,          _______,
        _______, _______, _______, _______,          KC_SPC,           _______, TG(_GAMING), _______, _______,      _______
    ),
};

#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_aa[] = {KC_Z, KC_BSPC, COMBO_END};
const uint16_t PROGMEM combo_ae[] = {KC_Z, KC_L, COMBO_END};
const uint16_t PROGMEM combo_oe[] = {KC_Z, KC_ENT, COMBO_END};

// Defines Combos for use in the keymap
enum combo_events {
  COMBO_AA,
  COMBO_AE,
  COMBO_OE,
};

combo_t key_combos[COMBO_COUNT] = {
  [COMBO_AA] = COMBO(combo_aa, SE_ARNG),
  [COMBO_AE] = COMBO(combo_ae, SE_ADIA),
  [COMBO_OE] = COMBO(combo_oe, SE_ODIA),
};
#endif

#ifdef RAW_ENABLE

#define MAX(a,b) ((a) > (b) ? (a) : (b))

void raw_hid_receive(uint8_t *data, uint8_t length) {
  // TODO: check length
  int n_leds = data[0];
  for (int i = 0; i < n_leds; i++) {
    int intensity = MAX(data[3*i + 1], MAX(data[3*i + 2], data[3*i + 3]));
    // setrgb(data[3*i + 1], data[3*i + 2], data[3*i + 3], (LED_TYPE *)&led[i]);
    setrgb(intensity, IS_LAYER_ON(_GAMING) ? intensity * 0.3f: intensity * 0.7f, 0, (LED_TYPE *)&led[i]);
  }
  rgblight_set();
}
#endif

#ifdef MIDI_ENABLE
MidiDevice device;

void keyboard_post_init_user(void) {
  midi_device_init(&device);
  // midi_init();
}

#endif