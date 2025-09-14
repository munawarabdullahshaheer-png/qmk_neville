#include "quantum/pointing_device.h"
#include "quantum.h"

// If you have these headers available from QMK core drivers:
#include "pmw33xx.h"            // QMK pmw33xx driver
#include "cirque_pinnacle.h"    // QMK cirque driver

// Helper clamp macro from QMK docs
#define constrain_hid(amt) ((amt) < -127 ? -127 : ((amt) > 127 ? 127 : (amt)))

/* Called by QMK at startup to init pointing device on this side.
   We'll init the sensor that belongs to this controller side. */
bool pointing_device_driver_init(void) {
#ifdef POINTING_DEVICE_COMBINED
    if (is_keyboard_left()) {
        // Left side -> Cirque trackpad
        // Use whatever init function the cirque driver exposes:
        cirque_pinnacle_init();
    } else {
        // Right side -> PMW33xx trackball
        // index 0 for single-device on this MCU
        pmw33xx_init(0);
    }
#endif
    return true;
}

/* Return the local (per-side) mouse report. QMK will pass left+right to the combined callback. */
report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
    // zero-init
    mouse_report.x = 0;
    mouse_report.y = 0;
    mouse_report.v = 0;
    mouse_report.h = 0;
    mouse_report.buttons = 0;

    if (is_keyboard_left()) {
        // Read Cirque trackpad data (replace with real API call from your QMK build)
        pinnacle_data_t p = cirque_pinnacle_read_data(); // example API; adapt if needed
        // If the driver gives absolute positions you must convert to delta
        // Example: driver already provides delta (relative mode). If not, implement delta tracking.
        mouse_report.x = constrain_hid((int8_t)p.xValue); // adapt field names
        mouse_report.y = constrain_hid((int8_t)p.yValue);
        // handle tap/buttons if driver exposes them
        // mouse_report.buttons |= (p.buttonFlags & ... );
    } else {
        // Read PMW33xx sensor
        pmw33xx_report_t r = pmw33xx_read_burst(0);
        if (!r.motion.b.is_lifted && r.motion.b.is_motion) {
            int dx = (int)r.delta_x;
            int dy = (int)r.delta_y;
            mouse_report.x = constrain_hid(dx);
            mouse_report.y = constrain_hid(dy);
        }
        // if your breakout exposes buttons/push, read them here and set mouse_report.buttons
    }
    return mouse_report;
}

/* CPI helpers for QMK (simple passthrough using PMW / Cirque defaults) */
uint16_t pointing_device_driver_get_cpi(void) {
    if (is_keyboard_left()) {
        return cirque_pinnacle_get_cpi(); // adapt or return configured value
    } else {
        return pmw33xx_get_cpi(0);         // adapt as needed
    }
}
void pointing_device_driver_set_cpi(uint16_t cpi) {
    if (is_keyboard_left()) {
        cirque_pinnacle_set_cpi(cpi);
    } else {
        pmw33xx_set_cpi(0, cpi);
    }
}

/* Combine left and right reports into the shared report.
   Strategy: use right side (trackball) as coarse movement, left (trackpad) as fine,
   by scaling the trackpad deltas down and adding them. */
report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    report_mouse_t out = {.x = 0, .y = 0, .v = 0, .h = 0, .buttons = 0};

    const float fine_scale = 0.25f; // tweak: lower -> trackpad gives finer adjustments

    int combined_x = (int)right_report.x + (int)(left_report.x * fine_scale);
    int combined_y = (int)right_report.y + (int)(left_report.y * fine_scale);

    out.x = constrain_hid(combined_x);
    out.y = constrain_hid(combined_y);

    // Merge buttons (OR them). Adjust priority/behavior if needed.
    out.buttons = left_report.buttons | right_report.buttons;

    // Optionally treat left_report as scroll-only (set out.v/out.h based on left_report)
    // out.v = left_report.v; out.h = left_report.h;

    return out;
}

