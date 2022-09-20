set(INCROOT ${PROJECT_SOURCE_DIR}/src/client)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/client)

find_package(SFML 2.5.1 COMPONENTS graphics window audio system REQUIRED)

set(SRC
    ${SRCROOT}/main.cpp
)

set(INCDIRS ${INCROOT})

source_group("client" FILES ${SRC})

set(TARGET_NAME r-type_client)

add_executable(${TARGET_NAME} ${SRC})

# target_include_directories()
target_include_directories(${TARGET_NAME} PUBLIC ${INCROOT})
target_link_libraries(${TARGET_NAME} PUBLIC sfml-graphics sfml-window sfml-audio sfml-system)

add_custom_command(TARGET ${TARGET_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}> ${PROJECT_SOURCE_DIR})
