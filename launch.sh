#rm -rf build/
mkdir -p build/
cd build/
cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build  . -- -j 3