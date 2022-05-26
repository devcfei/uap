@echo off
@rem Windows BAT
@rem


if {%1} == {} goto buildAllTest 

if "%1" == "a" goto buildAll
if "%1" == "ca" goto rebuildAll
if "%1" == "at" goto buildAllTest
if "%1" == "t" goto runTest
if "%1" == "cat" goto rebuildAndTest
if "%1" == "p" goto buildPrecheckin
if "%1" == "d" goto runDemo

goto end

:rebuildAll
cmake --build build --target clean
:buildAll
cmake -S . -B build -DCMAKE_INSTALL_PREFIX="install" -DINSTALL_GTEST=OFF
cmake --build build
cmake --install build --config Debug

goto end



:rebuildAndTest
cmake --build build --target clean
:buildAllTest
cmake -S . -B build -DCMAKE_INSTALL_PREFIX="install" -DINSTALL_GTEST=OFF
cmake --build build
cmake --install build --config Debug
:runTest
.\install\Debug\bin\test.exe
goto end

:runDemo
.\install\Debug\bin\demo.exe
goto end


:buildPrecheckin
cmake -S . -B build -DCMAKE_INSTALL_PREFIX="install" -DINSTALL_GTEST=OFF
cmake --build build
cmake --install build --config Debug

cmake --build build --config Release
cmake --install build --config Release

:end