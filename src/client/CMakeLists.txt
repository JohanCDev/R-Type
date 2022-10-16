set(INCROOT ${PROJECT_SOURCE_DIR}/src/client)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/client)

set(SRC ${SRCROOT}/main.cpp ${SRCROOT}/client.cpp)

set(INCDIRS ${INCROOT})

source_group("client" FILES ${SRC})

set(TARGET_NAME r-type_client)

add_executable(${TARGET_NAME} ${SRC} "client.hpp")

if(APPLE)
  target_include_directories(${TARGET_NAME} PUBLIC ${INCROOT}
                                                   /opt/homebrew/include/)
  target_link_libraries(
    ${TARGET_NAME}
    /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-audio.dylib
    /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-graphics.dylib
    /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-network.dylib
    /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-system.dylib
    /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-window.dylib)
else()
  target_include_directories(${TARGET_NAME} PUBLIC ${INCROOT})
  target_link_libraries(
    ${TARGET_NAME} PRIVATE -lsfml-graphics -lsfml-window -lsfml-audio
                           -lsfml-system -lboost_thread)
endif()

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                ${PROJECT_SOURCE_DIR})
