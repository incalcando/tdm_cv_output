# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.22
cmake_policy(SET CMP0009 NEW)

# SOURCES at CMakeLists.txt:33 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/sebastian/Instruo/tdm_output_example/src/*.c")
set(OLD_GLOB
  "/home/sebastian/Instruo/tdm_output_example/src/PCM1681.c"
  "/home/sebastian/Instruo/tdm_output_example/src/TDM_output.c"
  "/home/sebastian/Instruo/tdm_output_example/src/main.c"
  "/home/sebastian/Instruo/tdm_output_example/src/rp2350_adc.c"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/sebastian/Instruo/tdm_output_example/build/CMakeFiles/cmake.verify_globs")
endif()

# SOURCES at CMakeLists.txt:33 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/sebastian/Instruo/tdm_output_example/src/*.cpp")
set(OLD_GLOB
  "/home/sebastian/Instruo/tdm_output_example/src/blinker.cpp"
  "/home/sebastian/Instruo/tdm_output_example/src/wrapper.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/sebastian/Instruo/tdm_output_example/build/CMakeFiles/cmake.verify_globs")
endif()
