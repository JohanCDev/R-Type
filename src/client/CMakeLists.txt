set(INCROOT ${PROJECT_SOURCE_DIR}/src/client)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/client)

include(FetchContent)

if(NOT DEFINED CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
    set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
endif()

if(NOT SFML_FOUND)
    set(SFML_VERSION "2.5.1")

    FetchContent_Declare(
        sfml
        GIT_REPOSITORY "https://github.com/SFML/SFML.git"
        GIT_TAG "${SFML_VERSION}"
    )

    FetchContent_GetProperties(sfml)

    if(NOT sfml_POPULATED)
        FetchContent_Populate(sfml)
        add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
    endif()
endif()

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
