#ifndef _APP_H_
#define _APP_H_





class App : public LogTraceHelper
{
public:
    App();
    ~App();

    Result createApplication();
    Result initApplication();

    Result startUI();
    Result setLayout();

    void onFileOpenClicked()
    {
        std::string pFilePath = "";
        CoInitialize(nullptr);
        IFileDialog *pdf;
        HRESULT hr = NULL;
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pdf));
        if (SUCCEEDED(hr))
        {
            COMDLG_FILTERSPEC rgSpec[] =
                {
                    {L"Pictures", L"*.jpg;*.jpeg;*.bmp;*.png"},
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
                    std::tstring str = pszFilePath;

                    USES_CONVERSION;
                    spLogWindow_->addMessage(W2A(pszFilePath));


                    //openImageFile(str);
                    openImageFileByTextureInspector(str);

                    CoTaskMemFree(pszFilePath);
                }
                pSelItem->Release();
            }
        }
        pdf->Release();
    }

    void onFolderOpenClicked()
    {
        std::string pFilePath = "";
        CoInitialize(nullptr);
        IFileDialog *pdf;
        HRESULT hr = NULL;
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pdf));
        if (SUCCEEDED(hr))
        {
            hr=pdf->SetOptions(FOS_PICKFOLDERS);
            hr = pdf->Show(NULL);
            if (SUCCEEDED(hr))
            {
                IShellItem *pSelItem;
                hr = pdf->GetResult(&pSelItem);
                if (SUCCEEDED(hr))
                {
                    LPWSTR pszFilePath = nullptr;
                    hr = pSelItem->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &pszFilePath);
                    std::wstring str = pszFilePath;

                    USES_CONVERSION;
                    spLogWindow_->addMessage(W2A(pszFilePath));


                    spFileBrowserWindow_->addPath(W2A(pszFilePath));

                    Result r;
                    sptr<IWindow> spWindow;
                    r = spFileBrowserWindow_.as(&spWindow);
                    if(UAP_SUCCESS(r))
                    {
                        spWindow->setOpen(true);
                    }

                    

                    CoTaskMemFree(pszFilePath);
                }
                pSelItem->Release();
            }
        }
        pdf->Release();
    }

    void onFileSaveAsClicked()
    {
        std::string pFilePath = "";
        CoInitialize(nullptr);
        IFileDialog *pdf;
        HRESULT hr = NULL;
        hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pdf));
        if (SUCCEEDED(hr))
        {
            COMDLG_FILTERSPEC rgSpec[] =
                {
                    {L"Pictures", L"*.jpg;*.jpeg;*.bmp"},
                    {L"All", L"*.*"},
                };

            hr = pdf->SetFileTypes(ARRAYSIZE(rgSpec), rgSpec);
            hr = pdf->SetDefaultExtension(L"bmp");
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
                    std::wstring str = pszFilePath;

                    USES_CONVERSION;
                    spLogWindow_->addMessage(W2A(pszFilePath));

                    CoTaskMemFree(pszFilePath);
                }
                pSelItem->Release();
            }
        }
        pdf->Release();
    }

    void onViewPanelGenericClicked()
    {
        spGenericWindow_->setOpen(!spGenericWindow_->isOpen());
    }
    void onViewPanelLogClicked()
    {
        Result r;
        sptr<IWindow> spWindow;
        r = spLogWindow_.as(&spWindow);
        if(UAP_SUCCESS(r))
        {
            spWindow->setOpen(!spWindow->isOpen());
        }
        //spLogWindow_->setOpen(!spLogWindow_->isOpen());
    }

    void onViewPanelFileBrowserClicked()
    {
        Result r;
        sptr<IWindow> spWindow;
        r = spFileBrowserWindow_.as(&spWindow);
        if(UAP_SUCCESS(r))
        {
            spWindow->setOpen(!spWindow->isOpen());
        }
        //spLogWindow_->setOpen(!spLogWindow_->isOpen());
    }
    
#if defined(_DEBUG)
    void onHelpImGuiDemoClicked()
    {
        static Boolean open=true;
        spLayout_->openImGuiDemo(open);
        open=!open;
    }

    void onHelpImPlotDemoClicked()
    {
        static Boolean open=true;
        spLayout_->openImPlotDemo(open);
        open=!open;
    }
#endif  


    void onWindowClosed(IWindow* piWindow)
    {
        // remove the draw from layout
        sptr<IWindow> spWindow=piWindow;
        sptr<IDraw> spDraw;

        spWindow.as(&spDraw);

        spLayout_->deleteDraw(spDraw.get());

        // delete the file from file list manager


        auto it = mapWindowFile_.find(spWindow.get());
        if (it != mapWindowFile_.end())
        {
            std::tstring& filename = it->second;

            fileListManager_.deleteFile(filename);

            mapWindowFile_.erase(it++);

        }

    }


    void onFileBrowserClicked(std::tstring& file)
    {
        openImageFileByTextureInspector(file);

    }

private:
    sptr<IApplication> spApp_;
    sptr<IToml> spToml_;
    Result initApplicationConfiguration();
    Result initAppEvent();

    sptr<IUiEngine> spUiEngine_;
    sptr<IAttributes> spUiAttributes_;
    sptr<IEventDispatcher> spEventDispatcher_;
    sptr<IEvent> spEvent_;
    

    Result initUiEngine();

    sptr<IUiLayout> spLayout_;
    sptr<IAttributes> spLayoutAttributes_;

    std::string strAppPath_;
    Result buildLayout();
    Result buildMenuBar();
    Result buildToolBar();
    Result buildStatusBar();
    Result buildLogWindow();
    Result buildFileBrowserWindow();
    Result buildGenericWindow();


    // UI element

    // menubar
    sptr<IMenu> spMenuTop_;
    sptr<IMenu> spMenuFile_;
    sptr<IMenu> spMenuView_;
    sptr<IMenu> spMenuViewPanelWindow_;
    sptr<IMenu> spMenuHelp_;
    sptr<IMenuBar> spMenuBar_;

    // toolbar
    sptr<IToolBar> spToolBar_;

    // statusbar
    sptr<IStatusBar> spStatusBar_;


    sptr<IWindow> spGenericWindow_;
    sptr<ILogWindow> spLogWindow_;
    sptr<IFileBrowserWindow> spFileBrowserWindow_;


    std::vector<sptr<IImageWindow> > vecImageWindows_;
    std::vector<sptr<ITextureInspector> > vecTextureInspectorWindows_;

private:
    FileListManager fileListManager_;

    std::map<IWindow*, std::tstring> mapWindowFile_;


private:
    Result openImageFile(std::tstring filename);
    Result openImageFileByTextureInspector(std::tstring filename);

};

#endif //@_APP_H_