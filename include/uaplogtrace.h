#ifndef _UAP_LOGTRACE_H_
#define _UAP_LOGTRACE_H_


#ifndef _UAP_APP_H_
#error uaplogtrace.h requires uapapp.h to be included first
#endif

namespace uap
{

    // {4a84f317-1dec-4257-9b3d-980302860820}
    DEFINE_UUID(IID_LOGTRACE, 
        0x4a84f317, 0x1dec, 0x4257, 0x9b, 0x3d, 0x98, 0x03, 0x02, 0x86, 0x08, 0x20);


    class ILogTrace : public IUniversal
    {
    public:
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &,void **) = 0;

        // ILogTrace
        virtual Result initialize(IApplication* piApp, Char* name, IAttributes* piAttributes) = 0;

        virtual Result output(Ulong level, Char* format, ...) = 0;

            // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_LOGTRACE;
    }; // @class ILogTrace




    // {7ad7241f-628d-4a3d-8379-dbaeb69deae8}
    DEFINE_UUID(IID_FILELOGGER,
        0x7ad7241f, 0x628d, 0x4a3d, 0x83, 0x79, 0xdb, 0xae, 0xb6, 0x9d, 0xea, 0xe8);

    class IFileLogger : public IUniversal
    {
    public:
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &,void **) = 0;

        // ILogTrace
        virtual Result initialize(Char* filename) = 0;
        virtual Result saveMessage(Char* message) = 0;

            // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_FILELOGGER;
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

} // @namespace uap


#endif // _UAP_LOGTRACE_H_