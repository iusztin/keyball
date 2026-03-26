#include QMK_KEYBOARD_H

#include "quantum.h"

// IDEA: LT to toggle layer & other key?

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_ESC,
    KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,            KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  RSFT_T(KC_ENT) ,
                  KC_LGUI, KC_LALT, KC_MEH, MO(2), KC_SPC,    KC_BSPC, MO(3), _______, _______, KC_HYPR
  ),

  [1] = LAYOUT_universal(
    _______, _______, _______, _______, _______, _______,            _______, SSNP_FRE, SSNP_VRT, SSNP_HOR, _______, _______,
    _______, _______, _______, _______, _______, _______,            KC_PGUP, KC_BTN1, KC_BTN2, KC_BTN3, _______, _______,
    _______, _______, _______, _______, _______, _______,            KC_PGDN, KC_BTN4, KC_BTN5, _______, _______, _______,
                  _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______
  ),

  [2] = LAYOUT_universal(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,              KC_6,    KC_7,    KC_8,  KC_9,    KC_0,    _______,
    _______, _______, _______, _______, _______, _______,           KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
                _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______
  ),

  [3] = LAYOUT_universal(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_GRV,
    _______, _______, _______, _______, _______, _______,            _______, KC_EQL,  KC_PLUS, KC_LBRC, KC_RBRC, KC_PIPE,
    _______, _______, _______, _______, _______, _______,            _______, KC_UNDS, KC_MINS, KC_LCBR, KC_RCBR, KC_BSLS,
                 _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______
  ),

  [4] = LAYOUT_universal(
    _______, KC_F1,  KC_F2,  KC_F3,   KC_F4,   KC_F5,                 KC_F6,   KC_F7,    KC_F8,    KC_F9,   KC_F10,  _______,
    _______, KC_F11, KC_F12, _______, _______, SCRL_DVI,              _______, KC_VOLD,  KC_VOLU,  _______, _______, _______,
    _______, AML_TO, AML_I50, AML_D50, _______, SCRL_DVD,             CPI_D1K, CPI_D100, CPI_I100, CPI_I1K, _______, KBC_SAVE,
                  _______, _______, _______, _______, _______,    KBC_RST, _______, _______, _______, _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when layer 2 is on
    keyball_set_scroll_mode(layer_state_cmp(state, 2));

    // Enable layer 4 when layers 2 & 3 are active
    state = update_tri_layer_state(state, 2, 3, 4);

    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

// Delete on shift + backspace
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    NULL
};
