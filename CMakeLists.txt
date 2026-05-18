# Generated Cmake Pico project file

cmake_minimum_required(VERSION 4.0)

set(CMAKE_C_STANDARD 17)
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
set(toolchainVersion 15_2_Rel1)
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

# Add executable.

add_executable(${PROJECT_NAME}
	experiments.cxx
)

add_subdirectory(std_plus)
add_subdirectory(pico_plus)
add_subdirectory(gpio_plus)
add_subdirectory(pwm_plus)
add_subdirectory(pico_wire)
add_subdirectory(gfx)

# pico explorer board
add_subdirectory(display_7735)
add_subdirectory(buzzer)
add_subdirectory(ui_leds)
add_subdirectory(working_led)

# cfpt stuff
add_subdirectory(display_1309)
add_subdirectory(rotary_encoder)

# pic i2c board
add_subdirectory(mcp23008)
add_subdirectory(mem24lc02b)
add_subdirectory(mcp41xxx)
add_subdirectory(mcp3221)
#add_subdirectory(tc1321)
add_subdirectory(mcp9800)

# pic spi board
#add_subdirectory(mem25lc02)
#add_subdirectory(tc77)
#add_subdirectory(mcp3201)
#add_subdirectory(mcp4822)
#add_subdirectory(mcp41010)
#add_subdirectory(mcp6s92)
#add_subdirectory(mcp23s08)

# Add the standard library to the build
target_link_libraries(${PROJECT_NAME}
	lib_std_plus
	pico_stdlib
	hardware_i2c
	hardware_spi
	lib_pico_plus
	lib_gpio_plus
	lib_pwm_plus
	lib_pico_wire
	lib_gfx
	lib_display_7735
	lib_buzzer
	lib_ui_leds
	lib_working_led
	lib_display_1309
	lib_rotary_encoder
	lib_mcp23008
	lib_mem24lc02b
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(${PROJECT_NAME})

pico_set_program_name(${PROJECT_NAME} "Playground")
pico_set_program_version(${PROJECT_NAME} "avril 2026")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_enable_stdio_usb(${PROJECT_NAME} 1)

#add_compile_options(-fexec-charset=ISO-8859-1)
target_compile_options(${PROJECT_NAME} PRIVATE -fexec-charset=ISO-8859-1)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${PICO_TOOLCHAIN_PATH}/bin/arm-none-eabi-size $<TARGET_FILE:${PROJECT_NAME}>
#	COMMAND ${PICO_TOOLCHAIN_PATH}/bin/arm-none-eabi-size --format=sysv $<TARGET_FILE:${PROJECT_NAME}>
	COMMENT "Binary sizes:"
)
