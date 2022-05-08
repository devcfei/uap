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
        virtual const Uuid& uuidof()=0;
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const uap::Uuid &,void **) = 0;

        // IUiEngine
        virtual Result initialize()=0;
        virtual Result run()=0;

    }; // @class IAttributes

}; // @namespace uap


#endif // _UAP_UIENGINE_H_