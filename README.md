# uap

Universal Application Platform


## Build

Supported platform and build

Platform | Build Type
----|----
Windows| Debug,Release 
Linux| N/A

### Windows Build


`Debug Build`
```
cmake -S . -B build -DCMAKE_INSTALL_PREFIX="install" -DINSTALL_GTEST=OFF
cmake --build build
cmake --install build --config Debug
```

`Release Build`
```
cmake -S . -B build -DCMAKE_INSTALL_PREFIX="install" -DINSTALL_GTEST=OFF
cmake --build build --config Release
cmake --install build --config Release
```


## APIs

All the APIs are in **uap** namespace, there are several C APIs and C++ APIs

The C++ APIs are are always interface based. They should be get by uapGetInterface


### C APIs


API | Description
----|----
uapInitialize | Initialize the UAP 
uapCreateApplication | Create the application
logPrint | print log

### C++ APIs(Interfaces)

The C++ APIs are all interfaces, they are exposed from UAP(uapbe) itself or the components


Interface | component|backend
----|----|----
uap::IAttributes| UAP |windows, linux(N/A)
uap::IApplication| UAP |windows, linux(N/A)
uap::ILogTrace| UAP |windows, linux(N/A)
uap::IUiEngine| uiengine| ImGui(win32-d3d9)
uap::IImageEngine| imageengine| WIC, libpng(N/A)