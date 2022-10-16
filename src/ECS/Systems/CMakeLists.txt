set(INCROOT ${PROJECT_SOURCE_DIR}/src/ECS/Systems)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ECS/Systems)

list(APPEND SRC ${SRCROOT}/ControllableSystem.cpp ${SRCROOT}/DrawableSystem.cpp
     ${SRCROOT}/ShootingSystem.cpp ${SRCROOT}/VelocitySystem.cpp)

set(SRC
    "${SRC}"
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS} ${INCROOT}
    PARENT_SCOPE)
