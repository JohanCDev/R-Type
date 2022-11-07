echo "\t\t\t\033[0;34mINSTALLER FOR R-TYPE ON MACOSX\033[0m"
echo "Made by Johan CHRILLESEN, Adam DJEBAR, Louis MAESTRE, Tanguy BELLICHA and Cédric CORGE"
echo ""
echo "To run the game we need many dependencies, this installer will install them for you."

which -s brew
if [[ $? != 0 ]] ; then
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
else
    brew update
fi

brew install cmake pip
xcode-select --install

echo "\033[0;32mINSTALLING CONAN PACKAGE MANAGER\033[0m"
pip install conan

echo "\033[0;32mBUILDING PROJECT\033[0m"

if [ -d build ]
then
    rm -rf build
fi

mkdir build/ && cd build/ && 
conan install .. --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True && \
cmake .. -DCMAKE_BUILD_TYPE=Release -G 'Unix Makefiles' && cd .. && \
cmake --build build/ -j 5
