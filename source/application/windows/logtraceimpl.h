#ifndef _UAPBE_LOGTRACEIMPL_H_
#define _UAPBE_LOGTRACEIMPL_H_

namespace uap
{

    class LogTraceImpl : public ILogTrace
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &,void **);

        // ILogTrace
        virtual Result initialize(IApplication* piApp, Char* name, IAttributes* piAttributes);
        virtual Result output(Ulong level, Char* format, ...);

        static Result createInstance(ILogTrace **ppv)
        {
            LogTraceImpl *p = new LogTraceImpl();
            if (p)
            {
                *ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }
    private:
        LogTraceImpl()
            : refcount_(1)
        {
            logAttributes_.ul=0;
        }

        Ulong refcount_;


        // set in initialization
        sptr<IApplication> spApp_;
        CHAR name_[256];
        LogAttributes logAttributes_;

    };

};

#endif // _UAPBE_LOGTRACEIMPL_H_
