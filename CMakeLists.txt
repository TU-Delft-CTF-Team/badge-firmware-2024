# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.25)

include(pico_sdk_import.cmake)

project(firmware)

add_compile_definitions(PICO_STDIO_USB_ENABLE_RESET_VIA_BAUD_RATE=0)
add_compile_definitions(PICO_STDIO_USB_RESET_MAGIC_BAUD_RATE=47633) # the above definition should be enough, but just in case let's set magic baud rate to some random value

# add_compile_definitions(PICO_STDIO_USB_ENABLE_RESET_VIA_VENDOR_INTERFACE=0) # Windows doesn't like this option being on
add_compile_definitions(PICO_STDIO_USB_RESET_INTERFACE_SUPPORT_RESET_TO_BOOTSEL=0) # as earlier, just in case...

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

pico_sdk_init()

add_custom_command(
    OUTPUT morse_flag.hpp
    COMMAND ${CMAKE_CURRENT_LIST_DIR}/src/generate_morse_flag.sh
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/src/generate_morse_flag.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(firmware
    src/main.cpp
    src/hello_hardware/hello_hardware.cpp
    src/black_box/black_box.cpp
    src/entropy_encrypter/entropy_encrypter.cpp
    src/weary_watchdog/weary_watchdog.cpp
    src/flagstore/flagstore.cpp
)

pico_generate_pio_header(firmware ${CMAKE_CURRENT_LIST_DIR}/src/black_box/morse.pio)

target_link_libraries(firmware pico_stdlib hardware_adc hardware_pio hardware_dma pico_multicore)

pico_add_extra_outputs(firmware)

# Disable UART via pins, only enable for USB
pico_enable_stdio_uart(firmware 0)
pico_enable_stdio_usb(firmware 1)