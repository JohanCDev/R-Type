Write-Host "\t\t\tINSTALLER FOR R-TYPE ON LINUX UBUNTU AND FEDORA" -ForegroundColor Blue
Write-Host "Made by Johan CHRILLESEN, Adam DJEBAR, Louis MAESTRE, Tanguy BELLICHA and Cédric CORGE"
Write-Host ""
Write-Host "To run the game we need many dependencies, this installer will install them for you."

if (Test-Path -Path ./build/) {
    Remove-Item ./build -Recurse
}

mkdir build
Set-Location build

Write-Host "BUILDING PROJECT" -ForegroundColor Green
conan install .. --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True
cmake .. -DCMAKE_BUILD_TYPE=Release -G 'Visual Studio 17 2022'
Set-Location ../
cmake --build build
