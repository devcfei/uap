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
            Uchar start:1;
            Uchar end:1;
            Uchar enable:1;
            Uchar checked:1;
        }s;
    };


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

        virtual Result createInstance(const Uuid&, void **) = 0;
        
        // IUiEngine
        virtual Result initialize(IApplication *piApp, IAttributes *piAttributes) = 0;
        virtual Result startup() = 0;
        virtual Result run() = 0;

        virtual Result addMenuBar(IUiMenuBar* piMenuBar)=0;
        virtual Result getMenuBar(IUiMenuBar** ppiMenuBar)=0;

        

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
        virtual Result loadTexture(Char* path) = 0;
        virtual int width() = 0;
        virtual int height() = 0;
        virtual void* texture() = 0;

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
        virtual Result shutdown()= 0;
        virtual Result resize(Uint width, Uint height) = 0;

        virtual Result createTexture(Char* filename, IUiTexture** ppiTexture) =0;

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