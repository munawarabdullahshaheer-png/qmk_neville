/* --- Charybdis-specific + pointing device features --- */

#ifdef POINTING_DEVICE_ENABLE
    // Keep scroll + invert
    #define POINTING_DEVICE_SCROLL_ENABLE
    #define POINTING_DEVICE_INVERT_V
    // Disable auto pointer for now (to simplify testing)
    // #define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#endif // POINTING_DEVICE_ENABLE


/* >>> REMOVE combined mode while testing <<< */
// #define SPLIT_POINTING_ENABLE
// #define POINTING_DEVICE_COMBINED
// #define EE_HANDS            // comment this too unless you need split-hand testing


/* >>> Cirque trackpad settings <<< */
#define CIRQUE_PINNACLE_DIAMETER_MM 40
#define CIRQUE_PINNACLE_CURVED_OVERLAY
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
#define CIRQUE_PINNACLE_ADDR 0x2A    // try 0x2B if 0x2A doesn’t work
// #define CIRQUE_PINNACLE_TAP_ENABLE   // optional


/* >>> PMW33xx (trackball) — disable for now <<< */
// #define PMW33XX_CS_PIN B5
// #define PMW33XX_CPI 1600


/* Debugging */
#define POINTING_DEVICE_DEBUG
