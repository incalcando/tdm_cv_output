# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "../pico-sdk")

set(PICO_BOARD solderparty_rp2350_stamp_xl) 

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(PROJECT_NAME RP2350_TDM_example)

project(${PROJECT_NAME} C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

set(INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/inc)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)


# file(GLOB SOURCES "src/*.c" "src/*.cpp")

add_executable(${PROJECT_NAME}  
    ${SOURCES}
    # src/main.c
    # src/wrapper.cpp
    # src/blinker.cpp
    )


pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/src/TDM_output.pio)

pico_set_program_name(${PROJECT_NAME}  "template")
pico_set_program_version(${PROJECT_NAME}  "0.1")

pico_enable_stdio_uart(${PROJECT_NAME}  0)
pico_enable_stdio_usb(${PROJECT_NAME}  1)

# Add the standard library to the build
target_link_libraries(${PROJECT_NAME} 
        pico_stdlib
        )

# Add the standard include files to the build
target_include_directories(${PROJECT_NAME}  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/inc
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
  ${INCLUDE_DIRECTORIES}
  )

# Add any user requested libraries
target_link_libraries(${PROJECT_NAME}
        hardware_i2c
        hardware_dma
        hardware_pio
        hardware_clocks
        hardware_adc
        hardware_gpio #needed?
        )

target_compile_definitions(${PROJECT_NAME} PUBLIC
  LOG_LEVEL=DEBUG_LEVEL
  )

pico_add_extra_outputs(${PROJECT_NAME})

