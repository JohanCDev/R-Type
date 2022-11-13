cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(NOT WIN32)
  set(CMAKE_THREAD_LIBS_INIT "-lpthread")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
  set(CMAKE_HAVE_THREADS_LIBRARY 1)
  set(CMAKE_USE_WIN32_THREADS_INIT 0)
  set(CMAKE_USE_PTHREADS_INIT 1)
  set(THREADS_PREFER_PTHREAD_FLAG ON)
endif()

if(NOT DEFINED CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
  set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS
    1
    CACHE INTERNAL "No dev warnings")
endif()

project(R-Type LANGUAGES CXX)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(
    STATUS
    "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(
    DOWNLOAD
    "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
    "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

# Add ./cmake to the module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(MSVC)
  add_compile_options(/W2 /EHsc)
else()
  add_compile_options("-Wall" "-Wextra" "-Wshadow" "-pedantic"
    "-Wpointer-arith" "-fpermissive")
endif()

add_subdirectory(src)

# Unit testing
if(BUILD_TEST_SUITE)
  # Check for criterion
  find_package(Criterion REQUIRED)
  enable_testing()
  add_subdirectory(tests)
endif()

include(InstallRequiredSystemLibraries)
set(CPACK_WIX_LICENSE_RTF ${PROJECT_SOURCE_DIR}/misc/windows/wix_licence.txt)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_BUNDLE_NAME "R-Type")
include(CPack)
install(DIRECTORY ./assets/ DESTINATION bin/assets/)

if(WIN32 OR APPLE)
  install(DIRECTORY ./build/bin/ DESTINATION bin/)
endif()