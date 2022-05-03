#include "uapbe.h"

using namespace uap;

struct uapbeComponents
{
    Uuid uidComponent;
    TCHAR path[MAX_PATH];	// Component file(DLL) path
	HMODULE hDll;			// Handle to the DLL
};


struct uapbeGlobals
{
    
};


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

static Result uapbeEnumerateComponent()
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
			TRACE("  %s   <DIR>\n", ffd.cFileName);
		}
		else
		{
			filesize.LowPart = ffd.nFileSizeLow;
			filesize.HighPart = ffd.nFileSizeHigh;
			TRACE("  %s   %ld bytes\n", ffd.cFileName, filesize.QuadPart);

            if(lstrcmp(ffd.cFileName,_T("uapbe.dll"))==0)
            {
                // for a DLL which is uapbe.dll, just continue
                continue;
            }

			// for a DLL

			if (IsDll(ffd.cFileName))
			{
				HMODULE hDll = LoadLibrary(ffd.cFileName);
				if (hDll)
				{					
					// PFN_RegisterNxComponent pfn = (PFN_RegisterNxComponent)GetProcAddress(hDll, "RegisterNxComponent");
					// if (pfn == NULL)
					// {
					// 	FreeLibrary(hDll);// free dll if not a nx component
					// 	continue;
					// }

					// // for DLL which is a nx component, register				
					// NXUID* uids = NULL;
					// int size=0;
					// nr = pfn(NULL,&size);
					// if (size)
					// {
					// 	uids = new NXUID[size];
					// 	nr = pfn(uids, &size);
					// }
					

					// if (uids)
					// {
					// 	for (int i = 0; i < size; ++i)
					// 	{
					// 		NxComponentInfo info;

					// 		info.uid = uids[i];
					// 		lstrcpy(info.path, ffd.cFileName);

					// 		info.hDll = hDll;	// save DLL handle
					// 		TRACE("Registered interface! %s\n", ffd.cFileName);

					// 		GlobalNxComponentInfo.push_back(info);
					// 	}
					// }
				}

				else
				{
					// for a library damaged, just ignore and output a warning mesage 
					TRACE("WARN: LoadLibrary failed! %s\n", ffd.cFileName);
				}
			}

		}
	} while (FindNextFile(hFind, &ffd) != 0);


	FindClose(hFind);

	r = R_OK;
	return r;
}


extern "C" DLL_EXPORTS Result uapbeInitialize()
{
    Result r = R_OK;

    TRACE("uapbeInitialize\n");

    // TODO: enumerate the component and create the database
    r = uapbeEnumerateComponent();

    return r;
}

extern "C" DLL_EXPORTS Result uapbeVPrint(Char *pszFormat, va_list vaList)
{
    Result r = R_OK;
    HRESULT hr;

    CHAR szMessageBuffer[16380] = {0};
    hr = StringCchVPrintfA(szMessageBuffer, 16380, pszFormat, vaList);
    if (FAILED(hr))
    {
		TRACE("StringCchVPrintfA failed\n");
        r = R_ERROR;
        return r;
    }

    OutputDebugStringA(szMessageBuffer);

    return r;
}

extern "C" DLL_EXPORTS Result uapbeGetInterface(const uap::Uuid &uuid, uap::IUnknown **ppiUnknown)
{
    Result r = R_NO_SUCH_INTERFACE;
    uap::IUnknown *pi;

	// TODO: 
	//	check if uuid in uapbe already, otherwise check the components

    if(UidIsEqual(uuid, IID_IATTRIBUTES))
    {
        pi = new uap::CAttributesImpl();
        if(pi)
        {
            *ppiUnknown = pi;
            r = R_OK;
        }
        else        
        {
            r = R_NO_MEMORY;
        }
    }



    return r;
}