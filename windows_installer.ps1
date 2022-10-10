if (Test-Path -Path ./build/) {
    Remove-Item ./build -Recurse
}

mkdir build
Set-Location build

# Install dependencies with conan
conan install .. --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True

# Configure the project
cmake .. -DCMAKE_BUILD_TYPE=Release -G 'Visual Studio 17 2022'

cmake --build . -j 3

Set-Location ..