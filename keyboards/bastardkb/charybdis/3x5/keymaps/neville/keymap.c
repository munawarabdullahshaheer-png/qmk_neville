#include QMK_KEYBOARD_H
#include "print.h"   // for debug logging

// Simple 1-layer keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_Q, KC_W, KC_E, KC_R, KC_T,    KC_Y, KC_U, KC_I, KC_O, KC_P,
        KC_A, KC_S, KC_D, KC_F, KC_G,    KC_H, KC_J, KC_K, KC_L, KC_ENT,
        KC_Z, KC_X, KC_C, KC_V, KC_B,    KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
        KC_ESC, KC_SPC, KC_TAB, KC_BTN1, KC_BTN2
    ),
};

// -------------------- Cirque Test --------------------
#ifdef POINTING_DEVICE_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Print raw values for debugging
    uprintf("Cirque: x=%d y=%d v=%d h=%d\n", mouse_report.x, mouse_report.y, mouse_report.v, mouse_report.h);
    return mouse_report;
}
#endif
