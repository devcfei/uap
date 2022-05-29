#include "common.h"


namespace uap
{

    Ulong FileLoggerImpl::addRef()
    {
        return InterlockedIncrement(&refcount_);
    }
    Ulong FileLoggerImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            UAP_TRACE("FileLoggerImpl delete!!!!\n");
            delete this;
        }
        return ref;
    }

    Result FileLoggerImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;
        // create the interfaces implemented by
        if (uapUuidIsEqual(rUuid, IID_IUNIVERSAL))
        {
            IUniversal *pi = static_cast<IUniversal *>(this);
            addRef();

            *((IUniversal **)ppv) = pi;
            r = R_SUCCESS;
        }
        else if (uapUuidIsEqual(rUuid, IID_IFILELOGGER))
        {
            IFileLogger *pi = static_cast<IFileLogger *>(this);
            addRef();

            *((IFileLogger **)ppv) = pi;
            r = R_SUCCESS;
        }

        return r;
    }

    Result FileLoggerImpl::initialize(Char *filename)
    {
        Result r = R_SUCCESS;

        logFile_.open(filename,std::ios::app);

        auto t = std::time(nullptr);

        struct tm ltm;
        localtime_s(&ltm,&t);

        logFile_<<"============================================="<<std::endl;
        logFile_<<std::put_time(&ltm,"%Y/%m/%d %H:%M:%S")<<std::endl;
        logFile_<<"============================================="<<std::endl;


        return r;
    }

    Result FileLoggerImpl::saveMessage(Char *message)
    {
        Result r = R_SUCCESS;

        if(enable_)
        {
            logFile_ << message;
        }

        return r;
    }
}

