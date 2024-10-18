CURRENT_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

SPI_DRIVER_REQUIRED = yes
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = cirque_pinnacle_spi

CONFIG_H += $(CURRENT_DIR)/config.h