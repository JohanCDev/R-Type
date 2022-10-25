set(INCROOT ${PROJECT_SOURCE_DIR}/src/ECS/Components)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ECS/Components)

list(
  APPEND
  SRC
  ${INCROOT}/AllComponents.hpp
  ${INCROOT}/AccelerationComponent.hpp
  ${INCROOT}/AnimationComponent.hpp
  ${INCROOT}/CollideComponent.hpp
  ${INCROOT}/ControllableComponent.hpp
  ${INCROOT}/DestroyableComponent.hpp
  ${INCROOT}/DrawableComponent.hpp
  ${INCROOT}/HealthComponent.hpp
  ${INCROOT}/ImmobileComponent.hpp
  ${INCROOT}/MaximumVelocityComponent.hpp
  ${INCROOT}/PositionComponent.hpp
  ${INCROOT}/VelocityComponent.hpp
  ${INCROOT}/WeaponComponent.hpp
  ${INCROOT}/ClientIDComponent.hpp)

set(SRC
    "${SRC}"
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS} ${INCROOT}
    PARENT_SCOPE)
