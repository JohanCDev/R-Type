include(FetchContent)

set(SFML_HASH "863fef024619da7f59b6404087b454337a172ac1")

if(NOT(SFML_OS_IOS OR SFML_OS_WINDOWS))
    set(BUILD_SHARED_LIBS TRUE "Building SFML shared libraries")
endif()

if(NOT APPLE)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG "${SFML_HASH}")
    FetchContent_MakeAvailable(SFML)
endif()