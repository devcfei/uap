#ifndef _UAP_APP_H_
#define _UAP_APP_H_

#ifndef _UAP_RESULT_H_
#error uapapp.h requires uapresult.h to be included first
#endif

namespace uap
{

    class IApp : public IUnknown
    {
    public:
        virtual const Uuid &uuidof() = 0;
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const uap::Uuid &, void **) = 0;

        // IApp
        virtual Result initialize() = 0;
        virtual Result createInterface(const uap::Uuid & rUuid, void **ppv) = 0;

    }; // @class IApp

}; // @namespace uap

#endif // _UAP_APP_H_