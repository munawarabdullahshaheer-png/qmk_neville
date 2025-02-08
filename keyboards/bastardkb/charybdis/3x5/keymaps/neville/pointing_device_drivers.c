#include QMK_KEYBOARD_H
#include "drivers/sensors/cirque_pinnacle.h"
#include "drivers/sensors/pmw3360.h"

void pointing_device_init_kb(void) {
    // Initialize both sensors
    pmw3360_init();
    cirque_pinnacle_init();
    pointing_device_init_user();
}

// Combine reports from both sensors
report_mouse_t pointing_device_task_combined_kb(report_mouse_t left_report, report_mouse_t right_report) {
    report_mouse_t report = {0};

    // Combine X movements (assuming PMW3360 is on left, Cirque on right)
    report.x = left_report.x + right_report.x;
    report.y = left_report.y + right_report.y;
    
    // Combine buttons (using bitwise OR to merge button states)
    report.buttons = left_report.buttons | right_report.buttons;
    
    // Combine scroll
    report.h = left_report.h + right_report.h;
    report.v = left_report.v + right_report.v;

    return pointing_device_task_combined_user(report, right_report);
}

// Optional: Implement this if you need custom handling
report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    return left_report;
}
