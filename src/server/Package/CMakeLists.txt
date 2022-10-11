set(INCROOT ${PROJECT_SOURCE_DIR}/src/server/Package)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/server/Package)

set(SRC
    ${SRC}
    # ${INCROOT}/Package.hpp
    # ${INCROOT}/InterfacePackage.hpp
    PARENT_SCOPE
)

set(INCDIRS ${INCROOT})

add_subdirectory(Packets)
