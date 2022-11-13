set(INCROOT ${PROJECT_SOURCE_DIR}/src/server)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/server)

list(APPEND SRC_SERVER ${SRCROOT}/main.cpp ${SRCROOT}/server.cpp ${SRCROOT}/handle_packets.cpp
  ${INCROOT}/game.hpp ${INCROOT}/server.hpp ${SRCROOT}/AISystem.cpp ${SRCROOT}/WaveSystem.cpp ${SRCROOT}/BonusSystem.cpp ${SRCROOT}/LobbySystem.cpp
  ${SRCROOT}/CollideSystem.cpp ${INCROOT}/GameStates.hpp ${SRCROOT}/stat_up.cpp ${SRCROOT}/send_stats_to_players.cpp ${SRCROOT}/LevelUpSystem.cpp
  ${SRCROOT}/RefreshSystem.cpp ${SRCROOT}/EndGameSystem.cpp ${SRCROOT}/DestroyOutdatedEntities.cpp)

set(SRC_SERVER
  "${SRC_SERVER}" "${SRC}")

set(INCDIRS ${INCROOT})
set(CONAN_DISABLE_CHECK_COMPILER
  True
  CACHE BOOL "" FORCE)

source_group("server" FILES ${SRC})

set(TARGET_NAME r-type_server)

add_executable(${TARGET_NAME} ${SRC_SERVER})

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
    /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_wserialization.dylib
  )
else()
  target_include_directories(
    ${TARGET_NAME} PUBLIC ${INCROOT} ${CONAN_INCLUDE_DIRS_SFML}
    ${CONAN_INCLUDE_DIRS_BOOST})
  target_link_libraries(${TARGET_NAME} PUBLIC CONAN_PKG::sfml CONAN_PKG::boost)

  if(WIN32 AND BUILD_SHARED_LIBS)
    # add_custom_command(
    # TARGET ${TARGET_NAME}
    # POST_BUILD
    # COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${TARGET_NAME}>
    # $<TARGET_FILE_DIR:${TARGET_NAME}>
    # COMMAND_EXPAND_LISTS)
  endif()
endif()

set_property(TARGET ${TARGET_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "")
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
  ${PROJECT_SOURCE_DIR}/)

install(TARGETS ${TARGET_NAME} DESTINATION bin)
