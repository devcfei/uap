#include "uapbe.h"

namespace uap
{
    const Uuid& LogTraceImpl::uuidof()
    {
        return uuid_;
    }

    Ulong LogTraceImpl::addRef()
    {
        TRACE("LogTraceImpl::addRef\n");

        return InterlockedIncrement(&refcount_);
    }
    Ulong LogTraceImpl::release()
    {
        TRACE("LogTraceImpl::release\n");

        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            TRACE("delete this(%p)\n",this);
            delete this;
        }
        return ref;
    }
    Result LogTraceImpl::queryInterface(const uap::Uuid &, void **)
    {
        return R_OK;
    }

    Result LogTraceImpl::initialize(IApplication* piApp, Char* name, IAttributes* piAttributes)
    {
        Result r = R_OK;

        spApp_ = piApp;

        StringCchCopyA(name_, 256, name);

        sptr<IAttributes> spAttr = piAttributes;
        r = spAttr->getUlong(UUID_LOGTRACE_ATTRIBUTES,logAttributes_.ul);


        return r;
    }


    Result LogTraceImpl::output(Ulong level, Char* format, ...)
    {
        Result r = R_OK;

        #define MBUF_LEN  16380      

        if(level<=logAttributes_.s.defaultLevel)
        {
            HRESULT hr;
            const CHAR *szLevelTag[LT_MAX] =
            {
                "[FATAL] ",
                "[ERROR] ",
                "[WARN] ",
                "[OK] ",     // INFO show OK
                "[OK] ",     // VEBOSE show OK
            };
            CHAR szMessageBuffer[MBUF_LEN] = {0};

            // check if level tag enabled
            if(logAttributes_.s.enableLevelTag)
            {
                hr = StringCchCatA(szMessageBuffer,MBUF_LEN, szLevelTag[level]);
            }

            // always have a name
            hr = StringCchCatA(szMessageBuffer,MBUF_LEN, name_);
            hr = StringCchCatA(szMessageBuffer,MBUF_LEN, "!");


            // start the format message
            size_t len;
            hr = StringCchLengthA(szMessageBuffer,MBUF_LEN,&len);

            va_list args;
            va_start(args, format);
            hr = StringCchVPrintfA(szMessageBuffer+len, MBUF_LEN, format, args);
            va_end(args);

            if (FAILED(hr))
            {
                TRACE("StringCchVPrintfA failed\n");
                r = R_ERROR;
                return r;
            }

            // check if debug trace needed
            if(logAttributes_.s.enableDebugTrace)
                OutputDebugStringA(szMessageBuffer);

            // check if debug application log needed
            if(logAttributes_.s.enableAppLogTrace)
            {
                sptr<IFileLogger> spFileLogger;
                r = spApp_->queryInterface(IID_FILELOGGER, (void**)&spFileLogger);
                if(UAP_SUCCESS(r))
                {
                    spFileLogger->saveMessage(szMessageBuffer);
                }
            }
      
        }

        return r;
    }




}; //@namespace uap
