#include "uapbe.h"

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

    Ulong AppImpl::addRef()
    {
        Ulong ref = InterlockedIncrement(&refcount_);

        UAP_TRACE("AppImpl::addRef- refcount=%d\n", ref);

        return ref;
    }
    Ulong AppImpl::release()
    {

        Ulong ref = InterlockedDecrement(&refcount_);
        UAP_TRACE("AppImpl::release - refcount=%d\n", ref);

        if (!ref)
        {
            UAP_TRACE("delete AppImpl()\n");

            logFile_.close();

            delete this;
        }
        return ref;
    }
    Result AppImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;
        // create the interfaces implemented by uapbe
        if (uapUuidIsEqual(rUuid, IDD_IAPP))
        {
            IApplication *pi = static_cast<IApplication *>(this);
            addRef();

            *((IApplication **)ppv) = pi;
            r = R_SUCCESS;
        }
        else if (uapUuidIsEqual(rUuid, IID_FILELOGGER))
        {
            IFileLogger *pi = static_cast<IFileLogger *>(this);
            addRef();

            *((IFileLogger **)ppv) = pi;
            r = R_SUCCESS;
        }

        return r;
    }

    Result AppImpl::initialize(IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;
        UAP_TRACE("AppImpl::initialize\n");

        sptr<IAttributes> spAttr = piAttributes;

        spAttr->getUint(UUID_APP_INIT_FLAGS, initFlags_);
        if (initFlags_ & APP_INIT_LOGTRACE_ENALBE)
        {
            UAP_TRACE("enabled application log trace\n");
            //
            initialize("app.log");
        }

        if (initFlags_ & APP_INIT_COMPONENT_ENALBE)
        {
            // build the interfaces database
            r = enumComponent();
        }

        return r;
    }

    Result AppImpl::createInstance(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;
        IUniversal *pi;

        UAP_TRACE("AppImpl::createInstance\n");

        // create the interfaces implemented by uapbe
        if (uapUuidIsEqual(rUuid, IID_IATTRIBUTES))
        {

            pi = new AttributesImpl();
            if (pi)
            {
                *ppv = (void **)pi;
                r = R_SUCCESS;
            }
            else
            {
                r = R_NO_MEMORY;
            }
        }
        else if (uapUuidIsEqual(rUuid, IID_LOGTRACE))
        {
            pi = new LogTraceImpl();
            if (pi)
            {
                *ppv = (void **)pi;
                r = R_SUCCESS;
            }
            else
            {
                r = R_NO_MEMORY;
            }
        }

        // if not uapbe interface, find in component
        if (!UAP_SUCCESS(r))
        {
            UAP_TRACE("not uapbe interface, find in component\n");

            for (auto it : vecInterfaceInfo_)
            {

                UAP_TRACE("DLL(%s)-%p\n", it.path, it.hDll);
                PFN_compGetInterface pfn = (PFN_compGetInterface)GetProcAddress(it.hDll, "compGetInterface");
                if (pfn)
                {
                    UAP_TRACE("found compGetInterface\n");

                    r = pfn(rUuid, (void **)ppv);
                    if (UAP_SUCCESS(r))
                    {
                        UAP_TRACE("compGetInterface returned! r = %d\n", r);

                        break; // break if find the interface!
                    }
                }
            }
        }

        return r;
    }


    Result AppImpl::getCurrentPath(Char* path, Ulong size)
    {
        Result r = R_SUCCESS;


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


    Result AppImpl::initialize(Char *filename)
    {
        Result r = R_SUCCESS;

        logFile_.open(filename);

        return r;
    }

    Result AppImpl::saveMessage(Char *message)
    {
        Result r = R_SUCCESS;

        logFile_ << message;

        return r;
    }

    Result AppImpl::enumComponent()
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

                if (lstrcmp(ffd.cFileName, _T("uapbe.dll")) == 0)
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

    Result AppImpl::registerInterface(LPCTSTR szFileName)
    {
        Result r = R_ERROR;

        UAP_TRACE("AppImpl::registerInterface - %s\n", szFileName);

        HMODULE hDll = LoadLibrary(szFileName);
        if (hDll)
        {
            PFN_compRegisterInterface pfn = (PFN_compRegisterInterface)GetProcAddress(hDll, "compRegisterInterface");
            if (pfn == NULL)
            {

                UAP_TRACE("compRegisterInterface not found! - %s\n", szFileName);

                FreeLibrary(hDll);
                r = R_NO_SUCH_INTERFACE;
                return r;
            }

            UAP_TRACE("compRegisterInterface found! - %p\n", pfn);

            Ulong count = 0;
            Uuid *paUuid = NULL;

            r = pfn(paUuid, &count);

            UAP_TRACE("compRegisterInterface step 1 ,returned! r = %d, count =%d\n", r, count);
            if (!UAP_SUCCESS(r))
            {
                if (count > 0)
                    paUuid = new Uuid[count];
            }

            if (paUuid)
            {
                r = pfn(paUuid, &count);
            }

            UAP_TRACE("compRegisterInterface step 2, returned! r = %d\n", r);
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

}; //@namespace uap
