#include "common.h"

static int GetModuleFilePath(LPCTSTR lpszModuleFile, int size, LPTSTR lpszPath)
{
    TCHAR path[MAX_PATH] = _T("");

    lstrcpy(path, lpszModuleFile);

    int nSize = size;
    for (int i = nSize - 1; i > 0; --i)
    {
        if (path[i] == _T('\\'))
        {
            path[i + 1] = 0;
            break;
        }
    }

    lstrcpy(lpszPath, path);

    return 0;
}

static BOOL IsDll(LPCTSTR lpszName)
{
    BOOL bDll = FALSE;
    LPCTSTR p;

    int nSize = lstrlen(lpszName);
    for (int i = nSize - 1; i > 0; --i)
    {
        if (lpszName[i] == _T('.')) // find the suffix
        {
            p = &lpszName[i];

            if (!lstrcmp(p, _T(".dll")))
            {
                bDll = TRUE;
            }
            break;
        }
    }
    return bDll;
}

namespace uap
{

    // IUniversal
    Ulong ApplicationImpl::addRef()
    {
        Ulong ref = InterlockedIncrement(&refcount_);
        UAP_TRACE("ApplicationImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong ApplicationImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
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
        spAttr->getUint(UUID_APPLICATION_CONFIGURATION, ac.ui);
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
        UAP_TRACE("ApplicationImpl::getCurrentPath\n");

        CHAR szModuleFileName[MAX_PATH];
        int nSize = GetModuleFileNameA(NULL, szModuleFileName, MAX_PATH);
        for (int i = nSize - 1; i > 0; --i)
        {
            if (szModuleFileName[i] == _T('\\'))
            {
                szModuleFileName[i + 1] = 0;
                break;
            }
        }

        StringCchCopyA(path, size - 1, szModuleFileName);

        return r;
    }

    Result ApplicationImpl::enumComponent()
    {
        Result r = R_SUCCESS;

        HANDLE hFind = INVALID_HANDLE_VALUE;
        WIN32_FIND_DATA ffd;
        LARGE_INTEGER filesize;
        TCHAR szCurDir[MAX_PATH];
        ::GetCurrentDirectory(MAX_PATH, szCurDir);

        TCHAR szFileName[MAX_PATH];
        int nSize = GetModuleFileName(NULL, szFileName, MAX_PATH);

        GetModuleFilePath(szFileName, nSize, szCurDir);
        StringCchCat(szCurDir, MAX_PATH, TEXT("*"));

        hFind = FindFirstFile(szCurDir, &ffd);

        if (INVALID_HANDLE_VALUE == hFind)
        {
            r = R_FILE_NOT_EXIST;
            return r;
        }

        // List all the files in the directory with some info about them.
        do
        {
            if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                UAP_TRACE("%s   <DIR>\n", ffd.cFileName);
            }
            else
            {
                filesize.LowPart = ffd.nFileSizeLow;
                filesize.HighPart = ffd.nFileSizeHigh;
                UAP_TRACE("%s   %ld bytes\n", ffd.cFileName, filesize.QuadPart);

                if (lstrcmp(ffd.cFileName, _T("application.dll")) == 0)
                {
                    // for a DLL which is uapbe.dll, ignore and continue
                    continue;
                }

                // for a DLL

                if (IsDll(ffd.cFileName))
                {
                    r = registerInterface(ffd.cFileName);
                }
            }
        } while (FindNextFile(hFind, &ffd) != 0);

        FindClose(hFind);

        r = R_SUCCESS;
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
