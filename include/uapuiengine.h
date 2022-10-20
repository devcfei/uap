#ifndef _UAP_UIENGINE_H_
#define _UAP_UIENGINE_H_

#ifndef _UAP_H_
#error uapuiengine.h requires uap.h to be included first
#endif

namespace uap
{

    // {e28c7ea9-40ec-4dd9-92b1-c9fb9db0258f}
    DEFINE_UUID(IID_IDRAW,
                0xe28c7ea9, 0x40ec, 0x4dd9, 0x92, 0xb1, 0xc9, 0xfb, 0x9d, 0xb0, 0x25, 0x8f);

    class IDraw : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IDraw
        virtual Result draw() = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IDRAW;
    }; // @class IDraw



    // {1241d45a-45d6-4031-9c4e-3573e20b33dc}
    DEFINE_UUID(IID_IMENU,
                0x1241d45a, 0x45d6, 0x4031, 0x9c, 0x4e, 0x35, 0x73, 0xe2, 0x0b, 0x33, 0xdc);

    class IMenu : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IMenu
        virtual Result initialize(IAttributes *piAttributes, IEvent* piEvent) = 0;
        virtual Result addItem(const Char *name, Boolean check, IMenu* submenu, EventId evtId) = 0;
        virtual Result addSeparator() = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IMENU;
    }; // @class IMenu



    // {9b78c15e-f09c-4969-ab82-75582742306e}
    DEFINE_UUID(IID_IMENUBAR,
                0x9b78c15e, 0xf09c, 0x4969, 0xab, 0x82, 0x75, 0x58, 0x27, 0x42, 0x30, 0x6e);

    class IMenuBar : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IMenuBar
        virtual Result initialize(IAttributes *piAttributes) = 0;
        virtual Result setMenu(IMenu* piMenu) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IMENUBAR;
    }; // @class IMenuBar


    // {9de0d6ec-59f6-4901-9d5c-5c8ef58c22a3}
    DEFINE_UUID(IID_ITOOLBAR,
                0x9de0d6ec, 0x59f6, 0x4901, 0x9d, 0x5c, 0x5c, 0x8e, 0xf5, 0x8c, 0x22, 0xa3);

    class IToolBar : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IToolBar
        virtual Result initialize(IAttributes *piAttributes) = 0;

        virtual Result buildToolBarFromTTF(const Char* filename, Ushort min, Ushort max) = 0;
        virtual Result addButton(const Char* label) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_ITOOLBAR;
    }; // @class IToolBar


    // {f9bbb1ab-a011-4c52-b403-d541bbc87505}
    DEFINE_UUID(IID_ISTATUSBAR,
                0xf9bbb1ab, 0xa011, 0x4c52, 0xb4, 0x03, 0xd5, 0x41, 0xbb, 0xc8, 0x75, 0x05);

    class IStatusBar : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IStatusBar
        virtual Result initialize(IAttributes *piAttributes) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_ISTATUSBAR;
    }; // @class IStatusBar

    // {ec59c3b2-9342-4007-b628-f0a24c4bcb97}
    DEFINE_UUID(IID_IWINDOW,
                0xec59c3b2, 0x9342, 0x4007, 0xb6, 0x28, 0xf0, 0xa2, 0x4c, 0x4b, 0xcb, 0x97);

    // {0625a03e-bd52-4dec-ab3b-72c6acd2e51d}
    DEFINE_UUID(WINDOW_ATTRIBUTE_TITLE,
                0x0625a03e, 0xbd52, 0x4dec, 0xab, 0x3b, 0x72, 0xc6, 0xac, 0xd2, 0xe5, 0x1d);

    // {ff6031d6-db9b-4622-acd1-609812dd8a95}
    DEFINE_UUID(WINDOW_CLOSE_EVENTID,
                0xff6031d6, 0xdb9b, 0x4622, 0xac, 0xd1, 0x60, 0x98, 0x12, 0xdd, 0x8a, 0x95);

    class IWindow: public IDraw
    {
    public:
        // IUniversal
        // virtual Ulong addRef() = 0;
        // virtual Ulong release() = 0;
        // virtual Result queryInterface(const Uuid &, void **) = 0;

        // IWindow
        virtual Result initialize(IAttributes *pAttributes, IEvent* piEvent) = 0;
        virtual Result drawPrimitives() = 0;
        virtual Boolean isOpen() const = 0;
        virtual Boolean setOpen(Boolean open) = 0;
        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IWINDOW;
    }; // @class IWindow


    // {d236619b-80eb-4ecd-ae82-83d70a762ba8}
    DEFINE_UUID(IID_ILOGWINDOW,
                0xd236619b, 0x80eb, 0x4ecd, 0xae, 0x82, 0x83, 0xd7, 0x0a, 0x76, 0x2b, 0xa8);

    class ILogWindow : public IUniversal
    {
    public:
        // IUniversal
        // virtual Ulong addRef() = 0;
        // virtual Ulong release() = 0;
        // virtual Result queryInterface(const Uuid &, void **) = 0;

        // ILogWindow
        virtual Result addMessage(Char *name) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_ILOGWINDOW;
    }; // @class ILogWindow

    // {426c6e1a-ee9d-4381-b0c3-bed169e23bd0}
    DEFINE_UUID(IID_IFILEBROWSERWINDOW,
                0x426c6e1a, 0xee9d, 0x4381, 0xb0, 0xc3, 0xbe, 0xd1, 0x69, 0xe2, 0x3b, 0xd0);

    class IFileBrowserWindow : public IUniversal
    {
    public:
        // IUniversal
        // virtual Ulong addRef() = 0;
        // virtual Ulong release() = 0;
        // virtual Result queryInterface(const Uuid &, void **) = 0;

        // IFileBrowserWindow
        virtual Result addPath(Char *name) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IFILEBROWSERWINDOW;
    }; // @class IFileBrowserWindow

    // {61ad8510-1006-46df-894b-d44d642676a3}
    DEFINE_UUID(IID_IIMAGEWINDOW,
                0x61ad8510, 0x1006, 0x46df, 0x89, 0x4b, 0xd4, 0x4d, 0x64, 0x26, 0x76, 0xa3);

    class IImageWindow : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IImageWindow
        virtual Result loadImage(const Char *name) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IIMAGEWINDOW;
    }; // @class IImageWindow

    // {fc1c4f48-ea3d-4bfe-902d-d9fdf18add7b}
    DEFINE_UUID(IID_ITEXTURE_INSPECTOR,
                0xfc1c4f48, 0xea3d, 0x4bfe, 0x90, 0x2d, 0xd9, 0xfd, 0xf1, 0x8a, 0xdd, 0x7b);

    class ITextureInspector : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // ITextureInspector
        virtual Result loadImage(const Char *name) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_ITEXTURE_INSPECTOR;
    }; // @class ITextureInspector



    // {2e55c329-30cc-4b52-9af9-b2d0a5eeebcf}
    DEFINE_UUID(IID_IUILAYOUT,
                0x2e55c329, 0x30cc, 0x4b52, 0x9a, 0xf9, 0xb2, 0xd0, 0xa5, 0xee, 0xeb, 0xcf);

    class IUiLayout : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IUiLayout
        virtual Result initializeLayout(IAttributes *piAttributes) = 0;
        virtual Result draw() = 0;

        virtual Result addDraw(IUniversal *piDraw) = 0;
        virtual Result deleteDraw(IUniversal *piDraw) = 0;

#ifdef _DEBUG
        virtual void openImGuiDemo(Boolean open) = 0;
        virtual void openImPlotDemo(Boolean open) = 0;
#endif

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IUILAYOUT;
    }; // @class IUiLayout

    // {bf4ad520-db64-401a-af3c-b0d7b19ddc94}
    DEFINE_UUID(IID_IFRAMEWINDOWELEMENTS,
                0xbf4ad520, 0xdb64, 0x401a, 0xaf, 0x3c, 0xb0, 0xd7, 0xb1, 0x9d, 0xdc, 0x94);

    class IFrameWindowElements : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IFrameWindowElements
        virtual Result addMenuBar(IMenuBar *piMenuBar) = 0;
        virtual Result getMenuBar(IMenuBar **ppiMenuBar) = 0;
        virtual Result addToolBar(IToolBar *piToolBar) = 0;
        virtual Result getToolBar(IToolBar **ppiToolBar) = 0;
        virtual Result addStatusBar(IStatusBar *piStatusBar) = 0;
        virtual Result getStatusBar(IStatusBar **ppiStatusBar) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IFRAMEWINDOWELEMENTS;
    }; // @class IFrameWindowElements


    // {7f8d5daf-f386-430d-ac32-5578ec6078a0}
    DEFINE_UUID(IID_UIENGINE,
                0x7f8d5daf, 0xf386, 0x430d, 0xac, 0x32, 0x55, 0x78, 0xec, 0x60, 0x78, 0xa0);

    // {181e8813-adad-4e43-826d-6553d11ed520}
    DEFINE_UUID(UUID_UILAYOUT_STYLE,
                0x181e8813, 0xadad, 0x4e43, 0x82, 0x6d, 0x65, 0x53, 0xd1, 0x1e, 0xd5, 0x20);

    enum LayoutStyle
    {
        LAYOUT_STYLE_SIMPLE,
        LAYOUT_STYLE_DOCKING,
        LAYOUT_STYLE_DEMO, // keep at the end

    };

    enum BackendType
    {
        BT_D3D9,
        BT_D3D11,
    };

    class IUiEngine : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        virtual Result createInstance(const Uuid &, void **) = 0;

        // IUiEngine
        virtual Result initialize(IApplication *piApp, IAttributes *piAttributes) = 0;
        virtual Result startup() = 0;
        virtual Result run() = 0;
        virtual Result getLayout(IUiLayout** ppiLayout) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_UIENGINE;

    }; // @class IUiEngine



    // {88fc8602-d006-443b-8562-6f337843b402}
    DEFINE_UUID(IID_ITEXTURE,
                0x88fc8602, 0xd006, 0x443b, 0x85, 0x62, 0x6f, 0x33, 0x78, 0x43, 0xb4, 0x02);

    class IUiTexture : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IUiTexture
        virtual Result loadTexture(const Char *path) = 0;
        virtual int width() = 0;
        virtual int height() = 0;
        virtual void *texture() = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_ITEXTURE;
    }; // @class IUiTexture



    // {cbba6aeb-a57c-45b7-81e1-0f0882ae4547}
    DEFINE_UUID(IID_IUIENGINE_BACKEND,
                0xcbba6aeb, 0xa57c, 0x45b7, 0x81, 0xe1, 0x0f, 0x08, 0x82, 0xae, 0x45, 0x47);

    // {937cb490-66f9-4d24-82ca-058a8c166712}
    DEFINE_UUID(UUID_IUIENGINE_BACKEND_HWND,
                0x937cb490, 0x66f9, 0x4d24, 0x82, 0xca, 0x05, 0x8a, 0x8c, 0x16, 0x67, 0x12);

    class IUiEngineBackend : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // UiEngineBackend
        virtual Result initializeBackend(IUiEngine *piUiEngine, IAttributes *piAttributes) = 0;
        virtual Result createDevice(IAttributes *piAttributes) = 0;
        virtual Result destoryDevice() = 0;
        virtual Result setup() = 0;
        virtual Result newFrame() = 0;
        virtual Result render() = 0;
        virtual Result reset() = 0;
        virtual Result shutdown() = 0;
        virtual Result resize(Uint width, Uint height) = 0;

        virtual Result createTexture(const Char *filename, IUiTexture **ppiTexture) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IUIENGINE_BACKEND;
    }; // @class IUiEngineBackend

} // @namespace uap

#endif // _UAP_UIENGINE_H_