cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

if(NOT DEFINED CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
  set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS
    1
    CACHE INTERNAL "No dev warnings")
endif()

project(R-Type LANGUAGES CXX)

if(APPLE)
  execute_process(COMMAND mkdir build/
    COMMAND cd build/
    COMMAND conan install .. --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True)
elseif(WIN32)
  execute_process(COMMAND mkdir build
    COMMAND Set-Location build
    COMMAND conan install .. --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True)
else()
  execute_process(COMMAND mkdir build/
    COMMAND cd build/
    COMMAND conan install .. --build=missing -s compiler.libcxx=libstdc++11 -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True)
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
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_BUNDLE_NAME "R-Type")
include(CPack)
install(DIRECTORY ./assets/ DESTINATION bin/assets/)