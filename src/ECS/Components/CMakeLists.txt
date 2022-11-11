set(INCROOT ${PROJECT_SOURCE_DIR}/src/ECS/Components)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ECS/Components)

list(
  APPEND
  SRC
  ${INCROOT}/AllComponents.hpp
  ${INCROOT}/CollideComponent.hpp
  ${INCROOT}/ClientIDComponent.hpp
  ${INCROOT}/ControllableComponent.hpp
  ${INCROOT}/DestroyableComponent.hpp
  ${INCROOT}/EntityIDComponent.hpp
  ${INCROOT}/GameTeamComponent.hpp
  ${INCROOT}/DrawableComponent.hpp
  ${INCROOT}/HealthComponent.hpp
  ${INCROOT}/ImmobileComponent.hpp
  ${INCROOT}/PositionComponent.hpp
  ${INCROOT}/VelocityComponent.hpp
  ${INCROOT}/WeaponComponent.hpp
  ${INCROOT}/LevelComponent.hpp
  ${INCROOT}/TextComponent.hpp
  ${INCROOT}/ClickableComponent.hpp)

set(SRC
  "${SRC}"
  PARENT_SCOPE)

set(INCDIRS
  ${INCDIRS} ${INCROOT}
  PARENT_SCOPE)
