cmake_minimum_required(VERSION 3.17.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(R-Type LANGUAGES CXX)

# Add ./cmake to the module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_compile_options(
    "-Wall" "-Wextra" "-Wshadow" "-pedantic" "-Wpointer-arith"
    "$<$<CONFIG:RELEASE>:-O3;-Werror>"
    "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
)

add_subdirectory(src)

# Unit testing
if(BUILD_TEST_SUITE)
    # Check for criterion
    find_package(Criterion REQUIRED)
    enable_testing()
    add_subdirectory(tests)
endif()