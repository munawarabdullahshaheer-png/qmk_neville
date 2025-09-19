/* --- Charybdis-specific + pointing device features --- */

#ifdef POINTING_DEVICE_ENABLE
    // Keep scroll + invert
    #define POINTING_DEVICE_SCROLL_ENABLE
    #define POINTING_DEVICE_INVERT_V
    // Disable auto pointer layer trigger for now
    // #define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#endif // POINTING_DEVICE_ENABLE


/* >>> Disable combined mode while testing <<< */
// #define SPLIT_POINTING_ENABLE
// #define POINTING_DEVICE_COMBINED
// #define EE_HANDS    // leave off unless you’re doing split-hand config


/* >>> Cirque trackpad (I²C) settings <<< */
#define CIRQUE_PINNACLE_DIAMETER_MM 40
#define CIRQUE_PINNACLE_CURVED_OVERLAY
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
#define CIRQUE_PINNACLE_ATTENUATION EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_4X

// I²C address (default = 0x2A; some boards use 0x2B)
#define CIRQUE_PINNACLE_I2C_ADDRESS 0x2A

// Optional gesture/tap features
// #define CIRQUE_PINNACLE_TAP_ENABLE


/* >>> PMW33xx (trackball) — disabled for now <<< */
// #define PMW33XX_CS_PIN B5
// #define PMW33XX_CPI 1600


/* Debugging */
#define POINTING_DEVICE_DEBUG
