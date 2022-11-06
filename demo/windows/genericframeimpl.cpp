#include "framework.h"


Ulong GenericFrameImpl::addRef()
{
    Ulong ref = InterlockedIncrement(&refcount_);
    // UAP_TRACE("GenericFrameImpl::addRef- refcount=%d\n", ref);
    return ref;
}
Ulong GenericFrameImpl::release()
{
    Ulong ref = InterlockedDecrement(&refcount_);
    // UAP_TRACE("GenericFrameImpl::release - refcount=%d\n", ref);
    if (!ref)
    {
        UAP_TRACE("GenericFrameImpl delete!!!!\n");
        delete this;
    }
    return ref;
}
Result GenericFrameImpl::queryInterface(const Uuid &rUuid, void **ppv)
{
    Result r = R_NO_SUCH_INTERFACE;

    if (uapUuidIsEqual(rUuid, IID_IFRAME))
    {
        IFrame *pi = static_cast<IFrame *>(this);
        addRef();

        *((IFrame **)ppv) = pi;
        r = R_SUCCESS;
    }
    return r;
}

Result GenericFrameImpl::drawFrame()
{
    Result r = R_SUCCESS;

    spDraw_->addText("text",false);
    spDraw_->addButton("button",false);
    static Boolean checked =false;
    spDraw_->addCheckBox("checkbox", false, &checked);


    // Path browse
    spDraw_->addText("Path",false);
    spDraw_->addEdit("##Edit", true,  path_, MAX_PATH);

    auto choseexe = [this](){

        std::string pFilePath = "";
        CoInitialize(nullptr);
        IFileDialog *pdf;
        HRESULT hr = NULL;
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pdf));
        if (SUCCEEDED(hr))
        {
            COMDLG_FILTERSPEC rgSpec[] =
                {
                    {L"Executable File(*.exe)", L"*.exe"},
                    {L"All", L"*.*"},
                };

            hr = pdf->SetFileTypes(ARRAYSIZE(rgSpec), rgSpec);
            hr = pdf->SetFileTypeIndex(0);
            hr = pdf->Show(NULL);
            if (SUCCEEDED(hr))
            {
                IShellItem *pSelItem;
                hr = pdf->GetResult(&pSelItem);
                if (SUCCEEDED(hr))
                {
                    LPWSTR pszFilePath = nullptr;
                    hr = pSelItem->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &pszFilePath);

                    USES_CONVERSION;
                    StringCchCopyA(path_,256, W2A(pszFilePath));


                    CoTaskMemFree(pszFilePath);
                }
                pSelItem->Release();
            }
        }
        pdf->Release();

    };
    spDraw_->addButton("Browse...",true, choseexe);


    auto run=[this](){

        UAP_TRACE("Run...");

        USES_CONVERSION;

        LPTSTR path= A2T(path_);

        STARTUPINFO si = {sizeof(si)} ;  
        PROCESS_INFORMATION pi ;

        TCHAR dir[MAX_PATH];

        StringCchCopy(dir,MAX_PATH,path);
        PathRemoveFileSpec(dir);

        CreateProcess(NULL,path,NULL,NULL,FALSE,0,NULL,dir,&si,&pi);

    };

    
    spDraw_->addButton("Run",false, run);
    




    return r;
}