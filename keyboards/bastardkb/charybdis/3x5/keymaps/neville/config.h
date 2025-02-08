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
    // Basic pointing device settings
    #define POINTING_DEVICE_COMBINED
    #define POINTING_DEVICE_LEFT_DRIVER cirque_pinnacle
    #define POINTING_DEVICE_RIGHT_DRIVER pmw33xx
    #define POINTING_DEVICE_TASK_THROTTLE_MS 1
    #define POINTING_DEVICE_ROTATION_90
    #define POINTING_DEVICE_ROTATION_90_RIGHT
    #define POINTING_DEVICE_INVERT_Y

    // Cirque trackpad config (left side)
    #define I2C1_SCL_PIN GP15
    #define I2C1_SDA_PIN GP14
    #define I2C_DRIVER I2CD1
    #define CIRQUE_PINNACLE_ADDR 0x2A
    #define CIRQUE_PINNACLE_TAP_ENABLE
    #define CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE
    #define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
    #define CIRQUE_PINNACLE_DIAMETER_MM 40
    #define CIRQUE_PINNACLE_CURVED_OVERLAY

    // PMW3360 config (right side)
    // Use the default SPI pins from the base config
    #define PMW33XX_CS_PIN GP17  // Only define CS pin, use default SPI pins
    #define PMW33XX_CPI 2000
    #define PMW33XX_CPI_STEP 100
    #define PMW33XX_CPI_MIN 100
    #define PMW33XX_CPI_MAX 12000

    // Scrolling settings
    #define SCROLL_DIVISOR_H 4
    #define SCROLL_DIVISOR_V 4
#endif

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

// PMW3360 specific settings (if not already defined)
#ifndef PMW33XX_CS_PIN
    #define PMW33XX_CS_PIN GP21  // Adjust pin as needed
#endif
