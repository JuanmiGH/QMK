/* Copyright 2021 Juan Miguel García (@real_jmgh) and https://www.youtube.com/JuanMiguelGarcia
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

// Custom Keycodes for macros
enum custom_keycodes {
  RECORTE = SAFE_RANGE,
  OMAS,
  OFEM,
  RMT,
  RMS,
  RMIH,
  RMDH,
  RMIS,
  RMDS,
  RMIV,
  RMDV
};

// Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RECORTE:
      if (record->event.pressed){
        SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_LGUI) SS_DOWN(X_S));
      } else {
        clear_keyboard();
      }
      break;

      case OMAS:
      if (record->event.pressed){
        layer_on(2);
        SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_P1) SS_TAP(X_P6) SS_TAP(X_P7));
        layer_off(2);
      } else {
        clear_keyboard();
      }
      break;

      case OFEM:
      if (record->event.pressed){
        layer_on(2);
        SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_P1) SS_TAP(X_P6) SS_TAP(X_P6));
        layer_off(2);
      } else {
        clear_keyboard();
      }
      break;

      case RMT:
      if (record->event.pressed){
        rgb_matrix_toggle();
      }
      break;

      case RMS:
      if (record->event.pressed){
        rgb_matrix_step();
      }
      break;

      case RMIH:
      if (record->event.pressed){
        rgb_matrix_increase_hue();
      }
      break;
      
      case RMDH:
      if (record->event.pressed){
        rgb_matrix_decrease_hue();
      }
      break;

      case RMIS:
      if (record->event.pressed){
        rgb_matrix_increase_sat();
      }
      break;

      case RMDS:
      if (record->event.pressed){
        rgb_matrix_decrease_sat();
      }
      break;

      case RMIV:
      if (record->event.pressed){
        rgb_matrix_increase_val();
      }
      break;
      
      case RMDV:
      if (record->event.pressed){
        rgb_matrix_decrease_val();
      }
      break;
  }
  return true;
};

// Emojis
enum unicode_names {
  GRIN,
  TJOY,
  HEART,
  CRY,
  KISS,
  WINK,
  THMUP,
  THMDN,
  POO,
  ROLF,
};

const uint32_t PROGMEM unicode_map[] = {
  [GRIN] = 0x1F600,
  [TJOY] = 0x1F602,
  [HEART] = 0x2764,
  [CRY] = 0x1f62d,
  [KISS] = 0x1F618,
  [WINK] = 0x1F609,
  [THMUP] = 0x1F44D,
  [THMDN] = 0x1F44E,
  [POO] = 0x1F4A9,
  [ROLF] = 0x1F923,
};

//*************************

// FUNCIONES TAP DANCE
void dance_cln_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_N);
    } else {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_N));
        clear_keyboard();
    }
}

void dance_cln_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_N);
    }
}

//NOMBRES TAP DANCE
enum {
    TD_ENE,
};

// Tap Dance DEFINICIONES
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ENE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
};

//*************************

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_planck_mit(
/*        ESC      Q        W        E        R        T        Y        U        I        O        P       bkspc   */
   LT(5,KC_ESC),  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
/*        TAB       A            S        D        F        G        H        J        K         L       '"      ENTER   */         
     LT(4,KC_TAB), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
/*        SHIFT    Z        X        C        V        B        N        M         ,        .        UP       ;:    */
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    TD(TD_ENE),    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_SCLN,
/*         CTRL     WIN     ALT      FN      LOWER     SPC     RISE   ALTGR      LEFT     DOWN     RIGHT  */
        KC_LCTL, KC_LGUI, KC_LALT, MO(1),    MO(2),  KC_SPC,  MO(3), KC_RALT,   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_planck_mit(
/*        ESC      Q        W        E        R        T        Y        U        I        O        P       bkspc   */
        KC_TRNS,  KC_F1,    KC_F2, KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F11,    KC_F12,
/*        TAB       A        S         D       F        G         H        J        K        L       '"      ENTER   */
        RGB_TOG, RGB_MOD, RGB_RMOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, KC_TRNS,
/*        SHIFT    Z        X        C        V        B        N        M         ,        .        UP       ;:    */
        KC_LSFT,  RMT,     RMS,     RMIH,   RMDH,    RMIS,     RMDS,   RMIV,     RMDV,   NK_TOGG, KC_PGUP, KC_SLSH,
/*         CTRL     WIN     ALT      FN      LOWER     SPC     RISE   ALTGR      LEFT     DOWN     RIGHT  */
          RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SPC, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END
    ),
    [2] = LAYOUT_planck_mit(
/*        ESC         Q        W     E       R       T       Y       U       I       O       P      bkspc   */
    LSFT(KC_SLSH),  KC_1,    KC_2, KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,    KC_DEL,
/*        TAB        A         S         D       F        G         H        J        K        L       '"      ENTER   */         
        KC_CAPS, LT(4,KC_A), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_BSLS, KC_QUOT, KC_SCLN, KC_ENT,
/*        SHIFT    Z        X        C        V        B        N        M         ,        .        UP       ;:    */
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UNDS, KC_EQL, KC_COMM, KC_DOT, KC_VOLU, KC_SCLN,
/*         CTRL     WIN     ALT      FN      LOWER     SPC    RISE   ALTGR      LEFT     DOWN     RIGHT  */
        KC_LCTL, KC_LGUI, KC_LALT, MO(1),    MO(2),  KC_SPC,  MO(3), KC_RALT,   KC_LEFT, KC_VOLD, KC_MUTE
    ),
    [3] = LAYOUT_planck_mit(
/*        ESC         Q        W     E        R        T       Y         U        I        O        P      bkspc   */
    RALT(KC_SLSH), KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, RECORTE,
/*        TAB    A     S      D      F      G       H        J        K        L      '"    ENTER   */         
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LCBR, KC_RCBR, KC_PIPE, KC_DQUO, KC_NO, KC_NO,
/*        SHIFT   Z     X      C      V      B       N        M       ,      .      UP    ;:    */
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MINS, KC_PPLS, KC_NO, KC_NO, KC_NO, KC_NO,
/*        CTRL     WIN      ALT      FN      LOWER     SPC     RISE    ALTGR    LEFT      DOWN    RIGHT  */
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [4] = LAYOUT_planck_mit(
/*        ESC     Q      W      E      R      T      Y      U      I      O      P    bkspc   */
         KC_NO, KC_P1, KC_P2, KC_P3, KC_P4, KC_P5, KC_P6, KC_P7, KC_P8, KC_P9, KC_P0, KC_NO,
/*        TAB    A     S      D      F      G       H      J      K      L     '"    ENTER   */         
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
/*        SHIFT   Z     X      C      V      B      N      M      ,      .      UP    ;:    */
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
/*        CTRL  WIN     ALT      FN   LOWER    SPC   RISE  ALTGR   LEFT   DOWN  RIGHT  */
        KC_NO, KC_NO, KC_LALT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    [5] = LAYOUT_planck_mit(
/*        ESC     Q      W      E      R      T      Y      U      I        O        P    bkspc   */
         KC_NO, OMAS, KC_NO, KC_NO, X(TJOY), KC_NO, KC_NO, KC_NO, KC_NO, X(THMUP), KC_NO, RESET,
/*        TAB    A      S       D      F       G        H      J         K        L     '"    ENTER   */         
        KC_NO, OFEM, X(GRIN), KC_NO, KC_NO, X(WINK), X(HEART), KC_NO, X(THMDN), X(CRY), KC_NO, KC_NO,
/*        SHIFT   Z     X       C       V       B      N       M      ,      .      UP    ;:    */
        KC_NO, KC_NO, KC_NO, X(ROLF), KC_NO, X(KISS), KC_NO, X(POO), KC_NO, KC_NO, KC_NO, KC_NO,
/*        CTRL  WIN     ALT      FN   LOWER   SPC RISE  ALTGR   LEFT   DOWN  RIGHT  */
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    )
};
