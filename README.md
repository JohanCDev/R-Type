R-Type
[![Build](https://github.com/JohanCDev/R-Type/actions/workflows/build.yml/badge.svg)](https://github.com/JohanCDev/R-Type/actions/workflows/mirror.yml)
[![License](https://img.shields.io/github/license/JohanCDev/R-Type)](https://github.com/JohanCDev/R-Type)
====

# R-Type

This project aims to recreate the R-Type game and add a multiplayer mode to it. we had to implement a multi-threaded server and a graphical client in SFML.

## Before continuing...

This project is an EPITECH Project. If you are an EPITECH student, move out the way! Nothing to see here... The groups don't want to be involved to your -42.<br/>If you're not, no worries! You're welcome here!

### Prerequisites

To use this project, you'll need CMake 3.16.3 Compiler minimum and conan package manager.

## Building

### **Command Line**

### on Linux:

Required tools:

- libudev-dev
- pkg-config
- libgl-dev

Commands:

```sh
# Create build directory
mkdir build/ && cd build/

# Install dependencies with conan
conan install .. --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True

# Configure the project
cmake .. -DCMAKE_BUILD_TYPE=Release -G 'Unix Makefiles'

# Build the executable and libraries
cmake --build  . -j 3

# Return to the previous category
cd -
```

on Windows:

Required tools:

- Visual Studio 17 2022 (minimum)

```sh
# Create the build directory
mkdir build && cd build

# Install dependencies with conan
conan install .. --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True

# Configure the project
cmake .. -DCMAKE_BUILD_TYPE=Release -G 'Visual Studio 17 2022'

# Build the executable and libraries
cmake --build . -j 3

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

# Open the generated pages
xdg-open doc/generated/html/index.html
```

# Authors

**Johan Chrillesen** - [JohanCdev](https://github.com/JohanCDev)

**Cédric Corge** - [CedricCorge](https://github.com/CedricCORGE)

**Tanguy Bellicha** - [tbellicha](https://github.com/tbellicha)

**Adam Djebar** - [djadanis](https://github.com/djadanis)

**Louis Maestre** - [Louismaestre](https://github.com/Louismaestre)
