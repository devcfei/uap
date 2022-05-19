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

        TRACE("AppImpl::addRef- refcount=%d\n", ref);

        return ref;
    }
    Ulong AppImpl::release()
    {

        Ulong ref = InterlockedDecrement(&refcount_);
        TRACE("AppImpl::release - refcount=%d\n", ref);

        if (!ref)
        {
            TRACE("delete AppImpl()\n");

            logFile_.close();

            delete this;
        }
        return ref;
    }
    Result AppImpl::queryInterface(const uap::Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;
        // create the interfaces implemented by uapbe
        if (UidIsEqual(rUuid, IDD_IAPP))
        {
            IApplication *pi = static_cast<IApplication *>(this);
            addRef();

            *((IApplication **)ppv) = pi;
            r = R_OK;
        }
        else if (UidIsEqual(rUuid, IID_FILELOGGER))
        {
            IFileLogger *pi = static_cast<IFileLogger *>(this);
            addRef();

            *((IFileLogger **)ppv) = pi;
            r = R_OK;
        }

        return r;
    }

    Result AppImpl::initialize(IAttributes *piAttributes)
    {
        Result r = R_OK;
        TRACE("AppImpl::initialize\n");

        sptr<IAttributes> spAttr = piAttributes;

        spAttr->getUint(UUID_APP_INIT_FLAGS, initFlags_);
        if (initFlags_ & APP_INIT_LOGTRACE_ENALBE)
        {
            TRACE("enabled application log trace\n");
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

    Result AppImpl::createInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;
        IUnknown *pi;

        TRACE("AppImpl::createInterface\n");

        // create the interfaces implemented by uapbe
        if (UidIsEqual(rUuid, IID_IATTRIBUTES))
        {

            pi = new AttributesImpl();
            if (pi)
            {
                *ppv = (void **)pi;
                r = R_OK;
            }
            else
            {
                r = R_NO_MEMORY;
            }
        }
        else if (UidIsEqual(rUuid, IID_LOGTRACE))
        {
            pi = new LogTraceImpl();
            if (pi)
            {
                *ppv = (void **)pi;
                r = R_OK;
            }
            else
            {
                r = R_NO_MEMORY;
            }
        }

        // if not uapbe interface, find in component
        if (!UAP_SUCCESS(r))
        {
            TRACE("not uapbe interface, find in component\n");

            for (auto it : vecInterfaceInfo_)
            {

                TRACE("DLL(%s)-%p\n", it.path, it.hDll);
                PFN_compGetInterface pfn = (PFN_compGetInterface)GetProcAddress(it.hDll, "compGetInterface");
                if (pfn)
                {
                    TRACE("found compGetInterface\n");

                    r = pfn(rUuid, (void **)ppv);
                    if (UAP_SUCCESS(r))
                    {
                        TRACE("compGetInterface returned! r = %d\n", r);

                        break; // break if find the interface!
                    }
                }
            }
        }

        return r;
    }

    Result AppImpl::initialize(Char *filename)
    {
        Result r = R_OK;

        logFile_.open(filename);

        return r;
    }

    Result AppImpl::saveMessage(Char *message)
    {
        Result r = R_OK;

        logFile_ << message;

        return r;
    }

    Result AppImpl::enumComponent()
    {
        Result r = R_OK;

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
                TRACE("%s   <DIR>\n", ffd.cFileName);
            }
            else
            {
                filesize.LowPart = ffd.nFileSizeLow;
                filesize.HighPart = ffd.nFileSizeHigh;
                TRACE("%s   %ld bytes\n", ffd.cFileName, filesize.QuadPart);

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

        r = R_OK;
        return r;
    }

    Result AppImpl::registerInterface(LPCTSTR szFileName)
    {
        Result r = R_ERROR;

        TRACE("AppImpl::registerInterface - %s\n", szFileName);

        HMODULE hDll = LoadLibrary(szFileName);
        if (hDll)
        {
            PFN_compRegisterInterface pfn = (PFN_compRegisterInterface)GetProcAddress(hDll, "compRegisterInterface");
            if (pfn == NULL)
            {

                TRACE("compRegisterInterface not found! - %s\n", szFileName);

                FreeLibrary(hDll);
                r = R_NO_SUCH_INTERFACE;
                return r;
            }

            TRACE("compRegisterInterface found! - %p\n", pfn);

            Ulong count = 0;
            Uuid *paUuid = NULL;

            r = pfn(paUuid, &count);

            TRACE("compRegisterInterface step 1 ,returned! r = %d, count =%d\n", r, count);
            if (!UAP_SUCCESS(r))
            {
                if (count > 0)
                    paUuid = new Uuid[count];
            }

            if (paUuid)
            {
                r = pfn(paUuid, &count);
            }

            TRACE("compRegisterInterface step 2, returned! r = %d\n", r);
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

            r = R_OK;
        }
        else
        {
            // for a library damaged, just ignore and output a warning mesage
            r = R_FILE_NOT_EXIST;
            TRACE("WARN: LoadLibrary failed! %s\n", szFileName);
        }
        return r;
    }

}; //@namespace uap
