set(INCROOT ${PROJECT_SOURCE_DIR}/src/client)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/client)

set(SRC
    "RTypeBootstrap/RessourcesManager.hpp"
    "RTypeBootstrap/Input.hpp"
    "RTypeBootstrap/Entity.h"
    "RTypeBootstrap/registry.h"
    "RTypeBootstrap/RTypeBootstrap.cpp"
    "RTypeBootstrap/RTypeBootstrap.h"
    "RTypeBootstrap/sparse_array.h"
    "RTypeBootstrap/Components/AccelerationComponent.h"
    "RTypeBootstrap/Components/ControllableComponent.h"
    "RTypeBootstrap/Components/DrawableComponent.h"
    "RTypeBootstrap/Components/HealthComponent.h"
    "RTypeBootstrap/Components/CollideComponent.h"
    "RTypeBootstrap/Components/MaximumVelocityComponent.h"
    "RTypeBootstrap/Components/PositionComponent.h"
    "RTypeBootstrap/Components/VelocityComponent.h"
    "RTypeBootstrap/Components/WeaponComponent.h"
    "RTypeBootstrap/Components/ImmobileComponent.h"
    "RTypeBootstrap/Components/DestroyableComponent.hpp"
    "RTypeBootstrap/Systems/ControllableSystem.cpp"
    "RTypeBootstrap/Systems/CollideSystem.cpp"
    "RTypeBootstrap/Systems/ShootingSystem.cpp"
    "RTypeBootstrap/Systems/DrawableSystem.cpp"
    "RTypeBootstrap/Systems/VelocitySystem.cpp"
    "RTypeBootstrap/Components/ShapeComponent.hpp")

set(INCDIRS ${INCROOT})
set(CONAN_DISABLE_CHECK_COMPILER True CACHE BOOL "" FORCE)

source_group("client" FILES ${SRC})

set(TARGET_NAME r-type_client)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
        "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(${TARGET_NAME} ${SRC})

if(APPLE)
    target_include_directories(${TARGET_NAME} PUBLIC ${INCROOT} /opt/homebrew/include/ ${PROJECT_BINARY_DIR}/)
    target_link_libraries(${TARGET_NAME}
        /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-audio.dylib
        /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-graphics.dylib
        /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-network.dylib
        /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-system.dylib
        /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-window.dylib
    )
else()
    target_include_directories(${TARGET_NAME} PUBLIC ${INCROOT} ${CONAN_INCLUDE_DIRS_SFML})
    target_link_libraries(${TARGET_NAME} PUBLIC -lsfml-graphics -lsfml-window -lsfml-system CONAN_PKG::sfml)

    if(WIN32 AND BUILD_SHARED_LIBS)
        add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${TARGET_NAME}> $<TARGET_FILE_DIR:${TARGET_NAME}> COMMAND_EXPAND_LISTS)
    endif()
endif()

set_property(TARGET ${TARGET_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "")
set_target_properties(${TARGET_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/
)
