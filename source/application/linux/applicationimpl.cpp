#include "common.h"




namespace uap
{

    // IUniversal
    Ulong ApplicationImpl::addRef()
    {
        Ulong ref = interlock_increment(&refcount_);
        UAP_TRACE("ApplicationImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong ApplicationImpl::release()
    {
        Ulong ref = interlock_decrement(&refcount_);
        UAP_TRACE("ApplicationImpl::release - refcount=%d\n", ref);
        if (!ref)
        {
            UAP_TRACE("delete ApplicationImpl!!!!!\n");
            delete this;
        }
        return ref;
    }
    Result ApplicationImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_IAPPLICATION))
        {
            IApplication *pi = static_cast<IApplication *>(this);
            addRef();

            *((IApplication **)ppv) = pi;
            r = R_SUCCESS;
        }
        else if (uapUuidIsEqual(rUuid, IID_IFILELOGGER))
        {
            IFileLogger *pi = static_cast<IFileLogger *>(this);
            addRef();

            *((IFileLogger **)ppv) = pi;
            r = R_SUCCESS;
        }
        // else if (uapUuidIsEqual(rUuid, IID_IUNIVERSAL))
        // {
        //     IUniversal *pi = static_cast<IUniversal *>(this);
        //     addRef();

        //     *((IUniversal **)ppv) = pi;
        //     r = R_SUCCESS;
        // }
     
        return r;
    }

    // IApplication
    Result ApplicationImpl::initialize(IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;
        UAP_TRACE("ApplicationImpl::initialize\n");

        sptr<IAttributes> spAttr = piAttributes;

        ApplicationConfiguration ac;
        spAttr->getUint(APPLICATION_ATTRIBUTE_CONFIGURATION, ac.ui);
        if (ac.s.enableLog)
        {
            UAP_TRACE("enabled application log trace\n");
            //
            FileLoggerImpl::initialize("app.log");
            
            // r = FileLoggerImpl::createInstance(fileLogger_.getaddrof());
            // if(!UAP_SUCCESS(r))
            // {
            //     UAP_TRACE("ERROR: create file logger failed\n");

            // }
            // if(UAP_SUCCESS(r))
            // {    
            //     fileLogger_->initialize("app.log");
            // }
        }
        if (ac.s.enableComponent)
        {
            // build the interfaces database
            r = enumComponent();
        }

        appConfig_ = ac;

        return r;
    }

    Result ApplicationImpl::createInstance(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        UAP_TRACE("ApplicationImpl::createInstance\n");

        // create the interfaces implemented by uapbe
        if (uapUuidIsEqual(rUuid, IID_IATTRIBUTES))
        {
            r = AttributesImpl::createInstance((IAttributes **)ppv);
        }
        else if (uapUuidIsEqual(rUuid, IID_LOGTRACE))
        {
            r = LogTraceImpl::createInstance((ILogTrace **)ppv);
        }
        else if (uapUuidIsEqual(rUuid, IID_ITOML))
        {
            r = TomlImpl::createInstance((IToml **)ppv);
        }

        // if not application interface, find in component
        if (!UAP_SUCCESS(r))
        {
            UAP_TRACE("not application interface, find in component\n");

            for (auto it : vecInterfaceInfo_)
            {

                UAP_TRACE("DLL(%s)-%p\n", it.path, it.hDll);
                PFN_CreateInstance pfn = (PFN_CreateInstance)GetProcAddress(it.hDll, "CreateInstance");
                if (pfn)
                {
                    UAP_TRACE("found CreateInstance\n");

                    r = pfn(rUuid, (void **)ppv);
                    if (UAP_SUCCESS(r))
                    {
                        UAP_TRACE("CreateInstance returned! r = %d\n", r);

                        break; // break if find the interface!
                    }
                }
            }
        }

        return r;
    }

    Result ApplicationImpl::getCurrentPath(Char *path, Ulong size)
    {
        Result r = R_SUCCESS;

        return r;
    }

    Result ApplicationImpl::enumComponent()
    {
        Result r = R_SUCCESS;

        return r;
    }

    Result ApplicationImpl::registerInterface(LPCTSTR szFileName)
    {
        Result r = R_ERROR;

        UAP_TRACE("ApplicationImpl::registerInterface - %s\n", szFileName);

        HMODULE hDll = LoadLibrary(szFileName);
        if (hDll)
        {
            PFN_RegisterComponent pfn = (PFN_RegisterComponent)GetProcAddress(hDll, "RegisterComponent");
            if (pfn == NULL)
            {

                UAP_TRACE("RegisterComponent not found! - %s\n", szFileName);

                FreeLibrary(hDll);
                r = R_NO_SUCH_INTERFACE;
                return r;
            }

            UAP_TRACE("RegisterComponent found! - %p\n", pfn);

            Ulong count = 0;
            Uuid *paUuid = NULL;

            r = pfn(paUuid, &count);

            UAP_TRACE("RegisterComponent step 1 ,returned! r = %d, count =%d\n", r, count);
            if (!UAP_SUCCESS(r))
            {
                if (count > 0)
                    paUuid = new Uuid[count];
            }

            if (paUuid)
            {
                r = pfn(paUuid, &count);
            }

            UAP_TRACE("RegisterComponent step 2, returned! r = %d\n", r);
            if (!UAP_SUCCESS(r))
            {
                return r;
            }

            for (Ulong i = 0; i < count; ++i)
            {
                interfaceInfo ifinfo = {paUuid[i], _T(""), hDll};

                StringCchCopy(ifinfo.path, MAX_PATH, szFileName);

                vecInterfaceInfo_.push_back(ifinfo);
            }

            // PFN_compGetInterface pfn = (PFN_compGetInterface)GetProcAddress(hDll, "compGetInterface");
            // if (pfn == NULL)
            // {
            // 	FreeLibrary(hDll);
            // 	continue;
            // }

            r = R_SUCCESS;
        }
        else
        {
            // for a library damaged, just ignore and output a warning mesage
            r = R_FILE_NOT_EXIST;
            UAP_TRACE("WARN: LoadLibrary failed! %s\n", szFileName);
        }
        return r;
    }

} // @namespace uap
