#include <common.h>

namespace uap
{

    Ulong LogTraceImpl::addRef()
    {
        UAP_TRACE("LogTraceImpl::addRef\n");

        return InterlockedIncrement(&refcount_);
    }
    Ulong LogTraceImpl::release()
    {
        UAP_TRACE("LogTraceImpl::release\n");

        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            UAP_TRACE("LogTraceImpl delete!!!!! this(%p)\n", this);
            delete this;
        }
        return ref;
    }
    Result LogTraceImpl::queryInterface(const Uuid &, void **)
    {
        return R_SUCCESS;
    }

    Result LogTraceImpl::initialize(IApplication *piApp, Char *name, IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;

        spApp_ = piApp;

        StringCchCopyA(name_, 256, name);

        sptr<IAttributes> spAttr = piAttributes;
        r = spAttr->getUlong(UUID_LOGTRACE_ATTRIBUTES, logAttributes_.ul);

        return r;
    }

    Result LogTraceImpl::output(Ulong level, Char *format, ...)
    {
        Result r = R_SUCCESS;

#define MBUF_LEN 16380

        if (level <= logAttributes_.s.defaultLevel)
        {
            HRESULT hr;
            const CHAR *szLevelTag[LT_MAX] =
                {
                    "[FATAL] ",
                    "[ERROR] ",
                    "[WARN] ",
                    "[INFO] ", // INFO show OK
                    "[VERBOSE] ", // VEBOSE show OK
                };
            CHAR szMessageBuffer[MBUF_LEN] = {0};

            // check if level tag enabled
            if (logAttributes_.s.enableLevelTag)
            {
                hr = StringCchCatA(szMessageBuffer, MBUF_LEN, szLevelTag[level]);
            }

            // always have a name
            hr = StringCchCatA(szMessageBuffer, MBUF_LEN, name_);
            hr = StringCchCatA(szMessageBuffer, MBUF_LEN, "!");

            // start the format message
            size_t len;
            hr = StringCchLengthA(szMessageBuffer, MBUF_LEN, &len);

            va_list args;
            va_start(args, format);
            hr = StringCchVPrintfA(szMessageBuffer + len, MBUF_LEN, format, args);
            va_end(args);

            if (FAILED(hr))
            {
                UAP_TRACE("StringCchVPrintfA failed\n");
                r = R_ERROR;
                return r;
            }

            // check if debug trace needed
            if (logAttributes_.s.enableMessageToDebugger)
                OutputDebugStringA(szMessageBuffer);

            // check if file log needed
            if (logAttributes_.s.enableFileLogger)
            {
                sptr<IFileLogger> spFileLogger;
                r = this->spApp_->queryInterface(IID_IFILELOGGER, (void **)&spFileLogger);
                if (UAP_SUCCESS(r))
                {
                    spFileLogger->saveMessage(szMessageBuffer);
                }
            }


            

        }

        return r;
    }

}; //@namespace uap
