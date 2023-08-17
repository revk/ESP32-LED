set (COMPONENT_SRCS "LED.c" "idle.c" "stargate.c" "spin.c" "pulse.c" "cylon.c" "clock.c" "text.c" "countdown.c" "random.c" "twinkle.c" "lava.c" "matter_main.cpp")
set (COMPONENT_REQUIRES "ESP32-RevK" "led_strip" "esp_netif" "esp_matter")

if(CONFIG_REVK_MATTER)

set(PRIV_REQUIRES_LIST esp_matter esp_matter_console app_reset)

idf_component_register(
	SRCS ${COMPONENT_SRCS}
	REQUIRES ${COMPONENT_REQUIRES}
	SRC_DIRS          "."
	PRIV_INCLUDE_DIRS  "."
	PRIV_REQUIRES      ${PRIV_REQUIRES_LIST})

set_property(TARGET ${COMPONENT_LIB} PROPERTY CXX_STANDARD 14)
target_compile_options(${COMPONENT_LIB} PRIVATE "-DCHIP_HAVE_CONFIG_H")

else()

register_component ()

endif()

