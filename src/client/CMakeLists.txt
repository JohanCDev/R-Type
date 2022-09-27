set(INCROOT ${PROJECT_SOURCE_DIR}/src/client)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/client)

set(SRC
 "RTypeBootstrap/Entity.h"
 "RTypeBootstrap/registry.h"
 "RTypeBootstrap/RTypeBootstrap.cpp"
 "RTypeBootstrap/RTypeBootstrap.h"
 "RTypeBootstrap/sparse_array.h"
 "RTypeBootstrap/Components/AccelerationComponent.h"
 "RTypeBootstrap/Components/ControllableComponent.h"
 "RTypeBootstrap/Components/DrawableComponent.h"
 "RTypeBootstrap/Components/HealthComponent.h"
 "RTypeBootstrap/Components/HitBoxComponent.h"
 "RTypeBootstrap/Components/MaximumVelocityComponent.h"
 "RTypeBootstrap/Components/PositionComponent.h"
 "RTypeBootstrap/Components/VelocityComponent.h"
 "RTypeBootstrap/Components/WeaponComponent.h"
 "RTypeBootstrap/Systems/ControllableSystem.cpp"
 "RTypeBootstrap/Systems/ShootingSystem.cpp"
 "RTypeBootstrap/Systems/DrawableSystem.cpp"
 "RTypeBootstrap/Systems/VelocitySystem.cpp")

set(INCDIRS ${INCROOT})

source_group("client" FILES ${SRC})

set(TARGET_NAME r-type_client)

add_executable(${TARGET_NAME} ${SRC})

if(APPLE)
    target_include_directories(${TARGET_NAME} PUBLIC ${INCROOT} /opt/homebrew/include/)
    target_link_libraries(${TARGET_NAME}
        /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-audio.dylib
        /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-graphics.dylib
        /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-network.dylib
        /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-system.dylib
        /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-window.dylib
    )
else()
    target_include_directories(${TARGET_NAME} PUBLIC ${INCROOT})
    target_link_libraries(${TARGET_NAME} PRIVATE sfml-graphics sfml-window sfml-audio sfml-system)
    if (WIN32 AND BUILD_SHARED_LIBS)
        add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${TARGET_NAME}> $<TARGET_FILE_DIR:${TARGET_NAME}> COMMAND_EXPAND_LISTS)
    endif()
endif()

add_custom_command(TARGET ${TARGET_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}> ${PROJECT_SOURCE_DIR})
