CURRENT_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

SRC += halcyon.c

ifndef HLC_CIRQUE_TRACKPAD #add any other pointing devices here
  # Needed otherwise pointing devices will not work
  POINTING_DEVICE_ENABLE = yes
  # cirque defined here as otherwise sensitivity on slave is way too high
  # may need to be changed when we start supporting other pointing devices
  POINTING_DEVICE_DRIVER = cirque_pinnacle_spi 
endif

ifndef HLC_TFT_DISPLAY #add any other displays here
  # Needed otherwise displays will not work
  QUANTUM_PAINTER_ENABLE = yes
  QUANTUM_PAINTER_DRIVERS += st7789_spi
  BACKLIGHT_ENABLE = yes
  BACKLIGHT_DRIVER = pwm
endif

ifdef HLC_ENCODER
  include $(CURRENT_DIR)/hlc_encoder/rules.mk
endif

ifdef HLC_TFT_DISPLAY
  include $(CURRENT_DIR)/hlc_tft_display/rules.mk
endif

ifdef HLC_CIRQUE_TRACKPAD
  include $(CURRENT_DIR)/hlc_cirque_trackpad/rules.mk
endif

HLC_OPTIONS := $(HLC_NONE) $(HLC_CIRQUE_TRACKPAD) $(HLC_ENCODER) $(HLC_TFT_DISPLAY)

ifeq ($(filter 1, $(HLC_OPTIONS)), )
$(error Wrong or no module specified. Please specify one of the following: HLC_NONE, HLC_CIRQUE_TRACKPAD, HLC_ENCODER or HLC_TFT_DISPLAY.)
endif