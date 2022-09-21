R-Type
[![Build](https://img.shields.io/github/workflow/status/JohanCDev/R-Type/Build)](https://github.com/JohanCDev/Bomberman/actions/workflows/build.yml)
[![License](https://img.shields.io/github/license/JohanCDev/R-Type)](https://github.com/JohanCDev/R-Type)
====

# R-Type

This project aims to recreate the R-Type game and add a multiplayer mode to it. we had to implement a multi-threaded server and a graphical client in SFML.

## Before continuing...

This project is an EPITECH Project. If you are an EPITECH student, move out the way! Nothing to see here... The groups don't want to be involved to your -42.<br/>If you're not, no worries! You're welcome here!

### Prerequisites

To use this project, you'll need Cmake 3.17.0 Compiler, SFML-devel library and C11.

## Building

### Command Line (via CMake)

Required tools:

- CMake 3.17 (minimum)

on Linux:

```sh

# Configure the project
cmake -B build/ -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Release

# Build the executable and libraries
cmake --build build/ -j
```

on Windows:

Required tools:

- Visual Studio 17 2022 (minimum)

```sh
# Create the build directory
mkdir build && cd build

# Configure the project
cmake .. -G 'Visual Studio 17 2022' -DCMAKE_BUILD_TYPE=Release

# Build the executable and libraries
cmake --build .

# Return to previous directory
cd -
```

### Coding Style

R-Type is developed with C++. EPITECH doesn't impose any Coding Style to this but we tried to be as clean as possible.

## Documentation

### Local

Required tools:

- Doxygen

on Linux:

```sh
# Run at the root of the project
doxygen

# Open the genrated pages
xdg-open doc/generated/html/index.html
```

# Authors

**Johan Chrillesen** - [![JohanCdev]](https://github.com/JohanCDev)
**Cédric Corge** - [![CedricCorge]](https://github.com/CedricCORGE)
**Tanguy Bellicha** - [![tbellicha]](https://github.com/tbellicha)
**Adam Djebar** - [![djadanis]](https://github.com/djadanis)
**Louis Maestre** - [![Louismaestre]](https://github.com/Louismaestre)
