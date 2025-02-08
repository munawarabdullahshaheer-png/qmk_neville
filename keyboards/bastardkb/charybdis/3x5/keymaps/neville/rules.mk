VIA_ENABLE = yes
MOUSEKEY_ENABLE = yes
COMBO_ENABLE = yes
TAP_DANCE_ENABLE = no
DYNAMIC_TAPPING_TERM_ENABLE = yes

# Pointing device configuration
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = custom
CIRQUE_ENABLE = yes

# Add required source files
SRC += drivers/sensors/cirque_pinnacle.c
SRC += pointing/cirque_pinnacle_common.c
SRC += pointing/cirque_trackpad_logic.c
