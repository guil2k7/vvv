cmake_minimum_required(VERSION 3.22)
project("VVV" LANGUAGES C CXX VERSION 0.1.0)

include(Arduino-AVR-CMake/cmake/lto.cmake)
include(Arduino-AVR-CMake/cmake/arduino_core.cmake)
include(Arduino-AVR-CMake/cmake/arduino_hex.cmake)
include(Arduino-AVR-CMake/cmake/arduino_upload.cmake)

add_subdirectory(src)
