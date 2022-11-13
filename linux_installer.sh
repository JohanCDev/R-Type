echo "\t\t\t\033[0;34mINSTALLER FOR R-TYPE ON LINUX UBUNTU AND FEDORA\033[0m"
echo "Made by Johan CHRILLESEN, Adam DJEBAR, Louis MAESTRE, Tanguy BELLICHA and Cédric CORGE"
echo ""
echo "To run the game we need many dependencies, this installer will install them for you."
echo "\033[0;31mWe may ask you your super user password to install some dependencies such as cmake, g++ and pip\033[0m"

if uname -a | grep "Linux";
then
    echo ""
else
    echo "Unhandled architecture, not able to continue"
    exit -1
fi

if grep 'Fedora' /etc/os-release > /dev/null;
then
    COMMAND="dnf"
elif grep 'Ubuntu' /etc/os-release > /dev/null;
then
    COMMAND="apt-get"
else
    echo -e "\033[0;31mUnhandled system os\033[0m"
fi

echo "Sudo password: "
sudo $COMMAND install -y cmake g++ libudev-dev pip pkg-config libgl-dev

echo -e "\033[0;32mINSTALLING CONAN PACKAGE MANAGER\033[0m"
sudo pip install conan

if [ -d build ]
then
    rm -rf build
fi

echo -e "\033[0;32mBUILDING PROJECT\033[0m"
mkdir -p build; cd build && 
conan install .. --build=missing -s compiler=gcc -s compiler.libcxx=libstdc++11 -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True && \
cmake -DCMAKE_BUILD_TYPE=Release .. && cd ../ && \
cmake --build build/ -j 3
