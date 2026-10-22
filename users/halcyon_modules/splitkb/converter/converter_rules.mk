CONVERT_TO = halcyon

LTO_ENABLE := no
# ifndef HLC_NONE
# 	OLED_ENABLE := no
# endif

CONFIG_H += $(USER_PATH)/splitkb/converter/config.h

include $(USER_PATH)/splitkb/rules.mk
