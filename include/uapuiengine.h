#ifndef _UAP_UIENGINE_H_
#define _UAP_UIENGINE_H_

#ifndef _UAP_H_
#error uapuiengine.h requires uap.h to be included first
#endif

namespace uap
{

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

    class IUiEngine : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IUiEngine
        virtual Result initialize(IApplication *piApp, IAttributes *piAttributes) = 0;
        virtual Result startup() = 0;
        virtual Result run() = 0;

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
        virtual Result initializeMenuBar(IAttributes *piAttributes) = 0;
        virtual Result insertMenuItem(const Char *name, Uint id, Uint flags) = 0;
        virtual Result drawMenuBar() = 0;

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
} // @namespace uap

#endif // _UAP_UIENGINE_H_