#!/bin/bash



function build_clean()
{
    cmake --build build --target clean
}

function build_all()
{
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="install/Debug"
    cmake --build build
    cmake --install build
}

function runtest()
{
    ./install/Debug/bin/test
}

function rundemo()
{
    ./install/Debug/bin/demo
}

function build_precheckin()
{
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="install/Debug"
    cmake --build build
    cmake --install build

    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="install/Release"
    cmake --build build
    cmake --install build
}



if [ -n "$1" ]; then
    if [ "$1" = "a" ]; then
        build_all
    elif [ "$1" = "ca" ]; then
        build_clean
        build_all
    elif [ "$1" = "at" ]; then
        build_all
        runtest
    elif [ "$1" = "cat" ]; then
        build_clean
        build_all
        runtest
    elif [ "$1" = "t" ]; then
        runtest
    elif [ "$1" = "d" ]; then
        rundemo
    elif [ "$1" = "p" ]; then
        build_precheckin
    else
        echo "unknown arg"
    fi
else
    build_clean
    build_all
fi