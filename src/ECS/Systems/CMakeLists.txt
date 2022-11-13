set(INCROOT ${PROJECT_SOURCE_DIR}/src/ECS/Systems)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ECS/Systems)

list(APPEND SRC ${SRCROOT}/ControllableSystem.cpp ${SRCROOT}/DrawableSystem.cpp ${SRCROOT}/ClickableSystem.cpp ${SRCROOT}/MusicSystem.cpp
    ${SRCROOT}/VelocitySystem.cpp ${SRCROOT}/AllSystem.hpp)

set(SRC
    "${SRC}"
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS} ${INCROOT}
    PARENT_SCOPE)
