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
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="install/Debug"
cmake --build build --config Debug --target install

goto end



:rebuildAndTest
cmake --build build --target clean
:buildAllTest
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="install/Debug"
cmake --build build --config Debug --target install
:runTest
.\install\Debug\bin\test.exe
goto end

:runDemo
.\install\Debug\bin\demo.exe
goto end


:buildPrecheckin
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="install/Debug"
cmake --build build --config Debug --target install

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="install/Release"
cmake --build build --config Release --target install

:end