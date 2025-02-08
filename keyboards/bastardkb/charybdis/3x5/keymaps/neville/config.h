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
#pragma once

#ifdef VIA_ENABLE
/* VIA configuration. */
#undef DYNAMIC_KEYMAP_LAYER_COUNT
#define DYNAMIC_KEYMAP_LAYER_COUNT 4
#endif // VIA_ENABLE

#ifndef TAPPING_TERM
/**
 * \brief Configure the global tapping term (default: 200ms).
 * If you have a lot of accidental mod activations, crank up the tapping term.
 * See docs.qmk.fm/using-qmk/software-features/tap_hold#tapping-term
 */
#define TAPPING_TERM 200
#endif  // TAPPING_TERM

#ifndef __arm__
/* Disable unused features. */
#define NO_ACTION_ONESHOT
#endif // __arm__

/* Charybdis-specific features. */

#ifdef POINTING_DEVICE_ENABLE
#define POINTING_DEVICE_SCROLL_ENABLE
#define POINTING_DEVICE_INVERT_V
// Automatically enable the pointer layer when moving the trackball.  See also:
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS`
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD`
// #define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#endif // POINTING_DEVICE_ENABLE

#define COMBO_COUNT 3 // Change this number.
#define COMBO_TERM 120

//#define RETRO_SHIFT 500
#define LAYER_STATE_8BIT

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_ACTION_ONESHOT

//#define IGNORE_MOD_TAP_INTERRUPT
#define HOLD_ON_OTHER_KEY_PRESS
//#define PERMISSIVE_HOLD

#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR

//#define CHARYBDIS_DRAGSCROLL_REVERSE_X
#define CHARYBDIS_DRAGSCROLL_REVERSE_Y

// I2C Configuration for RP2040
#undef I2C_DRIVER
#define I2C_DRIVER I2C0
#define I2C0_SDA_PIN GP2
#define I2C0_SCL_PIN GP3
#define I2C0_SDA_PAL_MODE 4
#define I2C0_SCL_PAL_MODE 4

// I2C timing configuration
#define I2C0_CLOCK_SPEED 400000
#define I2C0_DUTY_CYCLE FAST_DUTY_CYCLE_2

// Cirque Trackpad Configuration
#define CIRQUE_PINNACLE_ADDR 0x2A
#define CIRQUE_PINNACLE_TAP_ENABLE
#define CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE
#define POINTING_DEVICE_ROTATION_90
#define POINTING_DEVICE_ROTATION_90_SECONDARY

// Add this with your other Cirque configurations
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
