# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Experiments CXX C ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(${PROJECT_NAME}
	experiments.cpp
)

add_subdirectory(std_plus)
add_subdirectory(pico_plus)
add_subdirectory(gpio_plus)
add_subdirectory(pwm_plus)
add_subdirectory(pico_wire)

add_subdirectory(rotary_encoder)
add_subdirectory(display_7735)

add_subdirectory(mcp23008)
add_subdirectory(mcp41xxx)
add_subdirectory(memory_24lc02b)

add_subdirectory(gfx)
add_subdirectory(display_1309)

pico_set_program_name(${PROJECT_NAME} "Buttons")
pico_set_program_version(${PROJECT_NAME} "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_enable_stdio_usb(${PROJECT_NAME} 1)

# Add the standard library to the build
target_link_libraries(${PROJECT_NAME}
	std_plus_lib
	pico_stdlib
	hardware_i2c
	hardware_spi
	pico_plus_lib
	gpio_plus_lib
	pwm_plus_lib
	rotary_encoder_lib
	display_7735_lib
	mcp23008_lib
	memory_24lc02b_lib
	gfx_lib
	display_1309_lib
	pico_wire_lib
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(${PROJECT_NAME})
