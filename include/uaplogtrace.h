#ifndef _UAP_LOGTRACE_H_
#define _UAP_LOGTRACE_H_


#ifndef _UAP_APP_H_
#error uaplogtrace.h requires uapapp.h to be included first
#endif

namespace uap
{

    class ILogTrace : public IUnknown
    {
    public:
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const uap::Uuid &,void **) = 0;

        // ILogTrace
        virtual Result initialize(IApplication* piApp, Char* name, IAttributes* piAttributes) = 0;

        virtual Result output(Ulong level, Char* format, ...) = 0;
    }; // @class ILogTrace


    class IFileLogger : public IUnknown
    {
    public:
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const uap::Uuid &,void **) = 0;

        // ILogTrace
        virtual Result initialize(Char* filename) = 0;
        virtual Result saveMessage(Char* message) = 0;
    }; // @class IFileLogger


    // {edae39f6-8b9f-4874-bc49-c7a04f7c6e45}
    DEFINE_UUID(UUID_LOGTRACE_ATTRIBUTES,
            0xedae39f6, 0x8b9f, 0x4874, 0xbc, 0x49, 0xc7, 0xa0, 0x4f, 0x7c, 0x6e, 0x45);


    // log trace attributes
    union LogAttributes
    {
        Ulong ul;
        struct
        {
            Uchar defaultLevel;
            Uchar enableAppLogTrace:1;
            Uchar enableDebugTrace:1;
            Uchar enable:1;
            Uchar enableLevelTag:1;
        }s;
    };

    enum LogTraceLevel
    {
        LT_FATAL=0,
        LT_ERROR,
        LT_WARN,
        LT_INFO,
        LT_VERBOSE,
        LT_OK = LT_VERBOSE,
        LT_ALL = LT_VERBOSE,
        LT_MAX = LT_ALL+1,
    };

}; // @namespace uap


#endif // _UAP_LOGTRACE_H_