cmake_minimum_required(VERSION 2.8.7)
project (pwmi2c)

set (CMAKE_C_FLAGS "-g")
set (CMAKE_CXX_FLAGS "-g --std=c++11")

if(DEFINED ENV{CPPUTEST_HOME})
  message("Using CppUTest found in $ENV{CPPUTEST_HOME}")
else()
  message("CPPUTEST_HOME is not set; You must tell CMake where to find CppUTest")
  return()
endif()

add_library(imp_cpputest STATIC IMPORTED)
set_property(TARGET imp_cpputest PROPERTY
             IMPORTED_LOCATION $ENV{CPPUTEST_HOME}/libCppUTest.a)

add_library(pwmi2c ./pwmi2c_main.c)
add_library(pwmi2ctest ./pwmi2c_test.cpp)

add_executable(RunAllTests RunAllTests.cpp)
target_link_libraries(RunAllTests imp_cpputest pwmi2ctest pwmi2c)
