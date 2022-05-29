#ifndef _FILELOGGER_IMPL_H_
#define _FILELOGGER_IMPL_H_

namespace uap
{
    class FileLoggerImpl : public IFileLogger
    {
    public:
        FileLoggerImpl()
            : refcount_(1)
            , enable_(true)
        {
        }
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &, void **);


        // IFileLogger
        virtual Result initialize(Char *filename);
        virtual Result saveMessage(Char *message);

        // static Result createInstance(IFileLogger **ppv)
        // {
        //     FileLoggerImpl *p = new FileLoggerImpl();
        //     if (p)
        //     {
        //         *ppv = p;
        //         return R_SUCCESS;
        //     }
        //     return R_ERROR;
        // }

    private:

        Ulong refcount_;
        std::ofstream logFile_;

        Boolean enable_;
    };

}

#endif //_FILELOGGER_IMPL_H_
