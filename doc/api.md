# APIs

All the APIs are in **uap** namespace, there are several C APIs and C++ APIs

The C++ APIs are are always interface based


## C APIs


API | Description
----|----
uapInitialize | Initialize the UAP 
uapCreateApplication | Create the application
uapPrintMessage | print log

## C++ APIs(Interfaces)

The C++ APIs are all interfaces, they are exposed from UAP(uapbe) itself or the components


Interface | component|backend
----|----|----
uap::IAttributes| UAP |windows, linux(N/A)
uap::IApplication| UAP |windows, linux(N/A)
uap::IFileLogger| UAP |windows, linux(N/A)
uap::ILogTrace| UAP |windows, linux(N/A)
uap::IUiEngine| uiengine| ImGui(win32-d3d9,win32-d3d11)
uap::IUiLayout| uiengine| ImGui(win32-d3d9,win32-d3d11)
uap::IMenuBar| uiengine| ImGui(win32-d3d9,win32-d3d11)
uap::IToolBar| uiengine| ImGui(win32-d3d9,win32-d3d11)
uap::IStatusBar| uiengine| ImGui(win32-d3d9,win32-d3d11)
uap::IUiDraw| uiengine| ImGui(win32-d3d9,win32-d3d11)
uap::IImageWindow| uiengine| ImGui(win32-d3d9,win32-d3d11)
uap::ITextureInspector| uiengine| ImGui(win32-d3d9,win32-d3d11)
uap::IUiTexture| uiengine| ImGui(win32-d3d9,win32-d3d11)
uap::IUiEngineBackend| uiengine| ImGui(win32-d3d9,win32-d3d11)
uap::IImageEngine| imageengine| WIC, libpng(N/A)
