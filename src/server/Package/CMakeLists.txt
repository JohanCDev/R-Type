set(INCROOT ${PROJECT_SOURCE_DIR}/src/server/Package)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/server/Package)

list(APPEND SRC_SERVER ${INCROOT}/Package.hpp ${INCROOT}/InterfacePackage.hpp)

set(SRC
    "${SRC}"
    PARENT_SCOPE)

set(INCDIRS
    ${INCROOT}
    PARENT_SCOPE)

add_subdirectory(Packets)
