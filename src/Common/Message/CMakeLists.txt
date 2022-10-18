set(INCROOT ${PROJECT_SOURCE_DIR}/src/Common/Message)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Common/Message)

list(
  APPEND
  SRC
  ${INCROOT}/Message.hpp
  ${INCROOT}/MessageHeader.hpp
  ${INCROOT}/MessageType.hpp
)

set(SRC
  "${SRC}"
  PARENT_SCOPE)

set(INCDIRS
  ${INCDIRS} ${INCROOT}
  PARENT_SCOPE)
