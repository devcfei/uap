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
        }
        virtual const Uuid& uuidof();
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const uap::Uuid &,void **);

        // ILogTrace
        virtual Result initialize(Char* name, Ulong defaultLevel);
        virtual Result output(Ulong level, Char* format, ...);
    private:
        const Uuid uuid_= IID_LOGTRACE;
        Ulong refcount_;

        Ulong defaultLevel_;
        CHAR name_[256];
    };

};

#endif // _UAPBE_LOGTRACEIMPL_H_
