set(INCROOT ${PROJECT_SOURCE_DIR}/src/client)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/client)

list(APPEND SRC_CLIENT 
  ${SRCROOT}/main.cpp
  ${SRCROOT}/client.cpp ${INCROOT}/client.hpp
  ${SRCROOT}/scene/game/Game.cpp ${INCROOT}/scene/game/Game.hpp
  ${SRCROOT}/scene/menu/Menu.cpp ${INCROOT}/scene/menu/Menu.hpp
  ${SRCROOT}/scene/lobby/Lobby.cpp ${INCROOT}/scene/lobby/Lobby.hpp
  ${SRCROOT}/scene/option/Option.cpp ${INCROOT}/scene/option/Option.hpp
  ${INCROOT}/scene/Scene.hpp
  ${SRCROOT}/scene/callback/callback.cpp
  ${SRCROOT}/handle_movement.cpp
  ${INCROOT}/proto.hpp ${SRCROOT}/new_entity.cpp)
  

set(SRC_CLIENT
  "${SRC_CLIENT}" "${SRC}")

set(INCDIRS ${INCROOT})
set(CONAN_DISABLE_CHECK_COMPILER
  True
  CACHE BOOL "" FORCE)

source_group("client" FILES ${SRC_CLIENT})

set(TARGET_NAME r-type_client)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(
    STATUS
    "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(
    DOWNLOAD
    "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
    "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

add_executable(${TARGET_NAME} ${SRC_CLIENT})

include(${CMAKE_BINARY_DIR}/conan.cmake)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

if(APPLE)
  target_include_directories(
    ${TARGET_NAME} PUBLIC ${INCROOT} /opt/homebrew/include/
    ${PROJECT_BINARY_DIR}/)
  target_link_libraries(
    ${TARGET_NAME}
    /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-audio.dylib
    /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-graphics.dylib
    /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-network.dylib
    /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-system.dylib
    /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-window.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_chrono.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_container.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_contract.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_coroutine.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_date_time.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_filesystem.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_graph.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_iostreams.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_json.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_log.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_log_setup.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_math_c99.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_math_c99f.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_math_c99l.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_math_tr1.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_math_tr1f.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_math_tr1l.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_nowide.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_prg_exec_monitor.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_program_options.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_random.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_regex.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_serialization.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_stacktrace_addr2line.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_stacktrace_basic.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_stacktrace_noop.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_system.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_thread-mt.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_timer.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_type_erasure.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_unit_test_framework.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_wave.dylib
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_wserialization.dylib)
else()
  target_include_directories(
    ${TARGET_NAME} PUBLIC ${INCROOT} ${CONAN_INCLUDE_DIRS_SFML}
    ${CONAN_INCLUDE_DIRS_BOOST})
  target_link_libraries(${TARGET_NAME} PUBLIC CONAN_PKG::sfml CONAN_PKG::boost)
endif()

set_property(TARGET ${TARGET_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "")
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
  ${PROJECT_SOURCE_DIR}/)

install(TARGETS ${TARGET_NAME} DESTINATION bin)