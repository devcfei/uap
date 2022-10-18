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

    // {9b78c15e-f09c-4969-ab82-75582742306e}
    DEFINE_UUID(IID_IUIMENUBAR,
                0x9b78c15e, 0xf09c, 0x4969, 0xab, 0x82, 0x75, 0x58, 0x27, 0x42, 0x30, 0x6e);

    class IUiMenuBar : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IUiMenuBar
        virtual Result initialize(IAttributes *piAttributes) = 0;
        virtual Result insertMenuItem(const Char *name, Uint id, Uint flags) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IUIMENUBAR;
    }; // @class IUiMenuBar

    union UiMenuFlags
    {
        Uint ui;
        struct
        {
            Uchar start : 1;
            Uchar end : 1;
            Uchar enable : 1;
            Uchar checked : 1;
        } s;
    };

    // {9de0d6ec-59f6-4901-9d5c-5c8ef58c22a3}
    DEFINE_UUID(IID_IUITOOLBAR,
                0x9de0d6ec, 0x59f6, 0x4901, 0x9d, 0x5c, 0x5c, 0x8e, 0xf5, 0x8c, 0x22, 0xa3);

    class IUiToolBar : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IUiToolBar
        virtual Result initialize(IAttributes *piAttributes) = 0;

        virtual Result buildToolBarFromTTF(const Char* filename, Ushort min, Ushort max) = 0;
        virtual Result addButton(const Char* label) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IUITOOLBAR;
    }; // @class IUiToolBar


    // {f9bbb1ab-a011-4c52-b403-d541bbc87505}
    DEFINE_UUID(IID_IUISTATUSBAR,
                0xf9bbb1ab, 0xa011, 0x4c52, 0xb4, 0x03, 0xd5, 0x41, 0xbb, 0xc8, 0x75, 0x05);

    class IUiStatusBar : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IUiStatusBar
        virtual Result initialize(IAttributes *piAttributes) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IUISTATUSBAR;
    }; // @class IUiStatusBar

    // {ec59c3b2-9342-4007-b628-f0a24c4bcb97}
    DEFINE_UUID(IID_IUIPANELWINDOW,
                0xec59c3b2, 0x9342, 0x4007, 0xb6, 0x28, 0xf0, 0xa2, 0x4c, 0x4b, 0xcb, 0x97);

    // {0625a03e-bd52-4dec-ab3b-72c6acd2e51d}
    DEFINE_UUID(PANELWINDOW_ATTRIBUTE_TITLE,
                0x0625a03e, 0xbd52, 0x4dec, 0xab, 0x3b, 0x72, 0xc6, 0xac, 0xd2, 0xe5, 0x1d);

    class IPanelWindow: public IDraw
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IPanelWindow
        virtual Result initialize(IAttributes *pAttributes) = 0;
        virtual Result drawPrimitives() = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IUIPANELWINDOW;
    }; // @class IPanelWindow


    // {d236619b-80eb-4ecd-ae82-83d70a762ba8}
    DEFINE_UUID(IID_IUILOGWINDOW,
                0xd236619b, 0x80eb, 0x4ecd, 0xae, 0x82, 0x83, 0xd7, 0x0a, 0x76, 0x2b, 0xa8);

    class IUiLogWindow : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IUiLogWindow
        virtual Result initialize(IAttributes *piAttributes) = 0;
        virtual Result addMessage(Char *name) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IUILOGWINDOW;
    }; // @class IUiLogWindow

    // {61ad8510-1006-46df-894b-d44d642676a3}
    DEFINE_UUID(IID_IUIIMAGEWINDOW,
                0x61ad8510, 0x1006, 0x46df, 0x89, 0x4b, 0xd4, 0x4d, 0x64, 0x26, 0x76, 0xa3);

    class IUiImageWindow : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IUiImageWindow
        virtual Result initialize(IAttributes *piAttributes) = 0;
        virtual Result loadImage(Char *name) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IUIIMAGEWINDOW;
    }; // @class IUiImageWindow

    // {fc1c4f48-ea3d-4bfe-902d-d9fdf18add7b}
    DEFINE_UUID(IID_IUITEXTURE_INSPECTOR,
                0xfc1c4f48, 0xea3d, 0x4bfe, 0x90, 0x2d, 0xd9, 0xfd, 0xf1, 0x8a, 0xdd, 0x7b);

    class IUiTextureInspector : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IUiTextureInspector
        virtual Result initialize(IAttributes *piAttributes) = 0;
        virtual Result loadImage(Char *name) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IUITEXTURE_INSPECTOR;
    }; // @class IUiTextureInspector




    
    // {a80fca28-e467-48a8-a986-1f0d45367ccb}
    DEFINE_UUID(IID_IFILEBROSWER, 
        0xa80fca28, 0xe467, 0x48a8, 0xa9, 0x86, 0x1f, 0x0d, 0x45, 0x36, 0x7c, 0xcb);


    class IUiFileBrowser : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IUiFileBrowser

        virtual Result initialize(char* path)=0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IFILEBROSWER;
    }; // @class IUiFileBrowser





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

        virtual Result addMenuBar(IUiMenuBar *piMenuBar) = 0;
        virtual Result getMenuBar(IUiMenuBar **ppiMenuBar) = 0;
        virtual Result addToolBar(IUiToolBar *piToolBar) = 0;
        virtual Result getToolBar(IUiToolBar **ppiToolBar) = 0;
        virtual Result addStatusBar(IUiStatusBar *piStatusBar) = 0;
        virtual Result getStatusBar(IUiStatusBar **ppiStatusBar) = 0;
        virtual Result addLogWindow(IUiLogWindow *piLogWindow) = 0;
        virtual Result getLogWindow(IUiLogWindow **ppiLogWindow) = 0;
        virtual Result addFileBroserWindow(IUiFileBrowser *piFileBrowserWindow) = 0;
        virtual Result getFileBroserWindow(IUiFileBrowser **ppiFileBrowserWindow) = 0;
        virtual Result addImageWindow(IUiImageWindow *piImageWindow) = 0;
        virtual Result getImageWindow(IUiImageWindow **ppiImageWindow) = 0;
        virtual Result addTextureInspector(IUiTextureInspector *piTextureInspector) = 0;
        virtual Result getTextureInspector(IUiTextureInspector **ppiTextureInspector) = 0;

        virtual Result addPanelWindow(IPanelWindow* piPanelWindow) = 0;
        virtual Result getPanelWindow(IPanelWindow** ppiPanelWindow) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_UIENGINE;

    }; // @class IUiEngine

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
        virtual Result initializeLayout(IUiEngine *piUiEngine, IAttributes *piAttributes) = 0;
        virtual Result draw() = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IUILAYOUT;
    }; // @class IUiLayout

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
        virtual Result loadTexture(Char *path) = 0;
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

        virtual Result createTexture(Char *filename, IUiTexture **ppiTexture) = 0;

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