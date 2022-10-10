set(INCROOT ${PROJECT_SOURCE_DIR}/src/server)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/server)

set(SRC
    ${SRCROOT}/main.cpp
    ${SRCROOT}/server.cpp
    ${SRCROOT}/bytes.cpp
    ${INCROOT}/utils.hpp
)

set(INCDIRS ${INCROOT})

source_group("server" FILES ${SRC})

set(TARGET_NAME r-type_server)

add_executable(${TARGET_NAME} ${SRC})

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if(APPLE)
    target_include_directories(${TARGET_NAME} PUBLIC ${INCROOT} /opt/homebrew/include/)
    target_link_libraries(${TARGET_NAME}
        /opt/homebrew/Cellar/boost/1.80.0/lib/libboost_system.dylib
    )
endif()

target_link_libraries(${TARGET_NAME} PRIVATE ${LIB_NAME})

add_custom_command(TARGET ${TARGET_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}> ${PROJECT_SOURCE_DIR})
