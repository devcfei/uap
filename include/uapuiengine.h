#ifndef _UAP_UIENGINE_H_
#define _UAP_UIENGINE_H_


#ifndef _UAP_H_
#error uapuiengine.h requires uap.h to be included first
#endif

namespace uap
{




    class IUiEngine : public IUnknown
    {
    public:
        // IUnknown
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const uap::Uuid &,void **) = 0;

        // IUiEngine
        virtual Result initialize(IApplication* piApp, IAttributes* piAttributes)=0;
        virtual Result startup()=0;
        virtual Result run()=0;


    }; // @class IUiEngine



    class IUiLayout: public IUnknown
    {
    public:
        // IUnknown
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const uap::Uuid &,void **) = 0;

        // IUiLayout
        virtual Result initializeLayout(IAttributes* piAttributes) = 0;
    }; // @class IUiLayout



    

    class IUiMenuBar: public IUnknown
    {
    public:
        // IUnknown
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const uap::Uuid &,void **) = 0;

        // IUiMenuBar
        virtual Result initializeMenuBar(IAttributes* piAttributes) = 0;
    }; // @class IUiMenuBar


}; // @namespace uap


#endif // _UAP_UIENGINE_H_