set(INCROOT ${PROJECT_SOURCE_DIR}/src/server)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/server)

set(SRC ${SRCROOT}/main.cpp)

set(INCDIRS ${INCROOT})

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

set_property(TARGET ${TARGET_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "")
