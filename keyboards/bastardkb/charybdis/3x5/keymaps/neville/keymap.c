/**
* Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#ifdef POINTING_DEVICE_ENABLE
#    include "pointing_device.h"
#    include "drivers/sensors/cirque_pinnacle.h"
#    include "drivers/sensors/pmw33xx_common.h"
#endif

enum charybdis_keymap_layers {
LAYER_BASE = 0,
LAYER_LOWER,
LAYER_RAISE,
LAYER_DUAL,
};

/**
// Automatically enable sniping-mode on the pointer layer.
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
*/

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define PT_SPC LT(LAYER_DUAL, KC_SPC)
#define PT_DOT LT(LAYER_DUAL, KC_DOT)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
/** \brief QWERTY layout (3 rows, 10 columns). */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[LAYER_BASE] = LAYOUT(
KC_Q,      KC_W,       KC_E,        KC_R,              KC_T,              KC_Y,      KC_U,        KC_I,        KC_O,              KC_P, \
SFT_T(KC_A),      KC_S,       KC_D,        KC_F,       ALT_T(KC_G),      RALT_T(KC_H),      KC_J,        KC_K,        KC_L,   RSFT_T(KC_QUOT), \
CTL_T(KC_Z),      KC_X,       KC_C,        KC_V,      LGUI_T(KC_B),      RCMD_T(KC_N),      KC_M,     KC_COMM,      KC_DOT,            KC_ENT, \
RAISE,    RAISE,   LOWER,           KC_BTN1,   KC_BTN2
),

[LAYER_RAISE] = LAYOUT(
KC_ESC,      KC_7,       KC_8,         KC_9,           KC_GRV,           KC_LPRN,    KC_RPRN,     KC_MINS,     KC_EQL,           KC_BSPC, \
SFT_T(KC_TAB),      KC_4,       KC_5,         KC_6,          KC_LALT,            KC_DLR,    KC_AMPR,       KC_AT,    KC_SCLN,   RSFT_T(KC_QUOT), \
CTL_T(KC_0),      KC_1,       KC_2,         KC_3,           KC_SPC,           KC_ASTR,    KC_EXLM,     KC_BSLS,    KC_SLSH,            KC_ENT, \
XXXXXXX,   XXXXXXX,    _______,           KC_BTN1,   KC_BTN2
),

[LAYER_LOWER] = LAYOUT(
KC_F9,    KC_F10,     KC_F11,       KC_F12,         KC_TILD,           KC_LBRC,    KC_RBRC,    KC_UNDS,     KC_PLUS,           KC_DEL, \
SFT_T(KC_F5),     KC_F6,      KC_F7,        KC_F8,         KC_LCMD,           KC_LCBR,    KC_RCBR,    KC_HASH,     KC_COLN,          KC_RSFT, \
CTL_T(KC_F1),     KC_F2,      KC_F3,        KC_F4,          KC_SPC,           KC_PERC,    KC_CIRC,    KC_PIPE,     KC_QUES,           KC_ENT, \
_______,        _______,   XXXXXXX,           KC_BTN1,    KC_BTN2
),

[LAYER_DUAL] = LAYOUT(
KC_BRID,   KC_BRIU,   C(KC_UP),    LAG(KC_D),        RGB_VAI,            KC_MRWD,     KC_MPLY,   KC_MFFD,      KC_VOLD,         KC_VOLU, \
SFT_T(KC_CAPS),   RGB_SAD,    RGB_SAI,      RGB_HUD,        RGB_HUI,            DPI_MOD,    DPI_RMOD,     KC_UP,      KC_PGUP,         KC_PGDN, \
SNIPING,   S_D_MOD,   S_D_RMOD,        DT_UP,        DT_DOWN,            DT_PRNT,     KC_LEFT,   KC_DOWN,     KC_RIGHT,         DRG_TOG, \
_______,    _______,    _______,            KC_BTN1,     KC_BTN2
),
};

// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
if (auto_pointer_layer_timer == 0) {
layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
}
auto_pointer_layer_timer = timer_read();
}
return mouse_report;
}

void matrix_scan_user(void) {
if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
auto_pointer_layer_timer = 0;
layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
}
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER

void pointing_device_init_kb(void) {
    if (is_keyboard_left()) {
        cirque_pinnacle_init();
    }
    pointing_device_init_user();
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    if (is_keyboard_left()) {
        // Left side - Cirque trackpad
        mouse_report = cirque_pinnacle_get_report(mouse_report);
        // Apply rotation and inversion
        int8_t x = mouse_report.y;
        int8_t y = -mouse_report.x;
        mouse_report.x = x;
        mouse_report.y = y;
    } else {
        // Right side - PMW3360
        mouse_report = pmw33xx_get_report(mouse_report);
        // Invert X axis for right side
        mouse_report.x = -mouse_report.x;
    }

    pointing_device_handle_shared_button(&mouse_report);
    pointing_device_handle_buttons(&mouse_report);
    pointing_device_handle_scrolling(&mouse_report);

    return pointing_device_task_user(mouse_report);
}

static void pointing_device_handle_shared_button(report_mouse_t* report) {
    static uint16_t shared_button_timer = 0;
    static bool shared_button_active = false;

    if (timer_elapsed(shared_button_timer) > 100) {  // Adjust debounce time as needed
        shared_button_active = false;
    }

    // Example of shared button handling - adjust as needed
    if (!shared_button_active && (report->buttons & MOUSE_BTN1)) {
        shared_button_timer = timer_read();
        shared_button_active = true;
    }
}

static void pointing_device_handle_buttons(report_mouse_t* report) {
    // Add any button processing logic here
    // For example, implementing drag-scroll toggle
    static bool drag_scroll = false;
    if (IS_LAYER_ON(LAYER_DUAL) && (report->buttons & MOUSE_BTN1)) {
        drag_scroll = !drag_scroll;
        report->buttons &= ~MOUSE_BTN1;  // Clear the button press
    }
}

static void pointing_device_handle_scrolling(report_mouse_t* report) {
    // Add scrolling behavior here
    static bool scrolling = false;
    if (IS_LAYER_ON(LAYER_DUAL)) {
        scrolling = true;
        report->h = report->x / 4;  // Adjust divisor to control scroll speed
        report->v = report->y / 4;
        report->x = 0;
        report->y = 0;
    } else {
        scrolling = false;
    }
}

// Optional: Implement this if you need custom user handling
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    return mouse_report;
}
#endif

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in
// rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

enum combos {
RAISE_LOWER_LAYER_DUAL,
BTN1_BTN2_BTN3,
DOT_ENT_DRGSCRL,

};

const uint16_t PROGMEM raise_lower_layer_dual[] = { RAISE, LOWER, COMBO_END};
const uint16_t PROGMEM btn1_btn2_btn3[] = { KC_BTN1, KC_BTN2, COMBO_END};
const uint16_t PROGMEM dot_ent_drgscrl[] = { KC_DOT, KC_ENT, COMBO_END};

combo_t key_combos[] = {
COMBO(raise_lower_layer_dual, MO(LAYER_DUAL)),
COMBO(btn1_btn2_btn3, KC_BTN3),
COMBO(dot_ent_drgscrl, DRGSCRL),

};
