#/usr/bin/bash

if test -d build
then
    rm -rf ./build;
fi

mkdir build && cd build && conan install .. --build=missing \
-c tools.system.package_manager:mode=install \
-c tools.system.package_manager:sudo=True && \
cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build  . -j 3