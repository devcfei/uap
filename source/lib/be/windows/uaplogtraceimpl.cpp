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

    Result LogTraceImpl::initialize(Char* name, Ulong defaultLevel)
    {
        Result r = R_OK;

        defaultLevel_ = defaultLevel;

        StringCchCopyA(name_, 256, name);

        return r;
    }


    Result LogTraceImpl::output(Ulong level, Char* format, ...)
    {
        Result r = R_OK;

        if(level<=defaultLevel_)
        {
            HRESULT hr;
            CHAR szMessageBuffer[16380] = {0};

            va_list args;
            va_start(args, format);  

            hr = StringCchVPrintfA(szMessageBuffer, 16380, format, args);

            va_end(args);

            if (FAILED(hr))
            {
                TRACE("StringCchVPrintfA failed\n");
                r = R_ERROR;
                return r;
            }

            OutputDebugStringA(szMessageBuffer);
        }

        return r;
    }




}; //@namespace uap
