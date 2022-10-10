set(INCROOT ${PROJECT_SOURCE_DIR}/src/server/Package)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/server/Package)

set(SRC
    ${SRC}
    ${INCROOT}/Package.hpp
    PARENT_SCOPE
)

set(INCDIRS ${INCROOT})

add_subdirectory(Packets)

source_group("server" FILES ${SRC})

set(TARGET_NAME r-type_server)

add_executable(${TARGET_NAME} ${SRC})
target_link_libraries(${TARGET_NAME} PRIVATE ${LIB_NAME})

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if(APPLE)
    target_link_libraries(${TARGET_NAME} PRIVATE "-framework IOKit")
    target_link_libraries(${TARGET_NAME} PRIVATE "-framework Cocoa")
    target_link_libraries(${TARGET_NAME} PRIVATE "-framework OpenGL")
endif()

add_custom_command(TARGET ${TARGET_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}> ${PROJECT_SOURCE_DIR})
