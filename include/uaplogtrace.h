#ifndef _UAP_LOGTRACE_H_
#define _UAP_LOGTRACE_H_


#ifndef _UAP_RESULT_H_
#error uaplogtrace.h requires uapresult.h to be included first
#endif

namespace uap
{

    class ILogTrace : public IUnknown
    {
    public:
        virtual const Uuid& uuidof()=0;
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const uap::Uuid &,void **) = 0;

        // ILogTrace
        virtual Result initialize(Char* name, Ulong defaultLevel) = 0;

        virtual Result output(Ulong level, Char* format, ...) = 0;
    }; // @class IAttributes

}; // @namespace uap


#endif // _UAP_LOGTRACE_H_