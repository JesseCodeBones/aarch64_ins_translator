cmake_minimum_required(VERSION 3.5.0)
project(aarch64_armv8_cpp VERSION 0.1.0 LANGUAGES C CXX)
file(GLOB sources CONFIGURE_DEPENDS ./*.cpp)
include(CTest)
enable_testing()

add_library(aarch64_armv8_cpp ${sources})
add_subdirectory(test)
