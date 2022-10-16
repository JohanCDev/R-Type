set(INCROOT ${PROJECT_SOURCE_DIR}/src/server/Package/Packets)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/server/Package/Packets)

list(
  APPEND
  SRC_SERVER
  ${INCROOT}/S2C_EntityDead.hpp
  ${INCROOT}/S2C_EntityHit.hpp
  ${INCROOT}/S2C_EntityNew.hpp
  ${INCROOT}/S2C_Error.hpp
  ${INCROOT}/S2C_GameEnd.hpp
  ${INCROOT}/S2C_Movement.hpp
  ${INCROOT}/S2C_Ok.hpp)

set(SRC
    "${SRC}"
    PARENT_SCOPE)

set(INCDIRS ${INCROOT})
