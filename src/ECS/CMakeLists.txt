set(INCROOT ${PROJECT_SOURCE_DIR}/src/ECS)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ECS)

add_subdirectory(Systems)
add_subdirectory(Components)

list(
  APPEND
  SRC
  ${INCROOT}/Entity.hpp
  ${INCROOT}/Input.hpp
  ${INCROOT}/Registry.hpp
  ${INCROOT}/ResourcesManager.hpp
  ${SRCROOT}/ResourcesManager.cpp
  ${INCROOT}/SparseArray.hpp)

set(SRC
    "${SRC}"
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS} ${INCROOT}
    PARENT_SCOPE)
