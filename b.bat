@rem
@rem Windows BAT
@rem

@rem Debug Build
cmake --build build --target clean
cmake -S . -B build -DCMAKE_INSTALL_PREFIX="install" -DINSTALL_GTEST=OFF
cmake --build build
cmake --install build --config Debug
install\Debug\bin\uaptest.exe


@rem Release Build
@rem cmake --build build --target clean
@rem cmake -S . -B build -DCMAKE_INSTALL_PREFIX="install" -DINSTALL_GTEST=OFF
@rem cmake --build build --config Release
@rem cmake --install build --config Release