# uap

## Universal Application Platform
![example workflow](https://github.com/devcfei/uap/actions/workflows/Windows.yml/badge.svg)


📖 [API](doc/api.md)

## ✨ Features
🕹 Simple and clear user interface



## ⌨️ Development


### Clone Code
UAP leverages several open source projects as submodules. Clone the code with **--recursive** option
```
git clone --recursive https://github.com/devcfei/uap.git
```

Submodules | Description
---|---
[ImGui](https://github.com/ocornut/imgui) | Dear ImGui                         
[imgui_tex_inspect](https://github.com/andyborrell/imgui_tex_inspect) | Texture inspector
[toml11](https://github.com/ToruNiina/toml11) | toml parser/encoder


### Build
Supported platform and build

Platform | Build Type
----|----
Windows| Debug,Release 
Linux| N/A


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





## 📜 License
uap is licensed under the MIT License, see LICENSE.txt for more information.


[MIT](https://opensource.org/licenses/MIT) Copyright (c) 2018-present Chao Fei