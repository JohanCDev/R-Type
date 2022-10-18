set(INCROOT ${PROJECT_SOURCE_DIR}/src/Common)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Common)

list(
  APPEND
  SRC
  ${INCROOT}/locked_queue.hpp
)

add_subdirectory(Message)

set(SRC
  "${SRC}"
  PARENT_SCOPE)

set(INCDIRS
  ${INCDIRS} ${INCROOT}
  PARENT_SCOPE)
