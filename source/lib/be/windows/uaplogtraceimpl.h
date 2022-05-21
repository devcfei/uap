#ifndef _UAPBE_LOGTRACEIMPL_H_
#define _UAPBE_LOGTRACEIMPL_H_

namespace uap
{

    class LogTraceImpl : public ILogTrace
    {
    public:
        LogTraceImpl()
            : refcount_(1)
        {
            logAttributes_.ul=0;
        }
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &,void **);

        // ILogTrace
        virtual Result initialize(IApplication* piApp, Char* name, IAttributes* piAttributes);
        virtual Result output(Ulong level, Char* format, ...);
    private:
        Ulong refcount_;


        // set in initialization
        sptr<IApplication> spApp_;
        CHAR name_[256];
        LogAttributes logAttributes_;

    };

};

#endif // _UAPBE_LOGTRACEIMPL_H_
