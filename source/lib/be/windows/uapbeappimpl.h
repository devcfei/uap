#ifndef _UAPBE_APPIMPL_H_
#define _UAPBE_APPIMPL_H_

namespace uap
{
    class AppImpl : public IApplication, IFileLogger
    {
    public:
        AppImpl()
            : refcount_(1)
            , initFlags_(APP_INIT_COMPONENT_ENALBE)
        {
        }
        virtual const Uuid& uuidof();
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const uap::Uuid &,void **);

        // IApplication
        virtual Result initialize(IAttributes* piAttributes);
        virtual Result createInterface(const uap::Uuid & rUuid, void **ppv);

        // IFileLogger
        virtual Result initialize(Char* filename);
        virtual Result saveMessage(Char* message);

    private:
        const Uuid uuid_= IDD_IAPP;
        Ulong refcount_;


        // components

        struct interfaceInfo
        {
            const Uuid uidComponent;
            TCHAR path[MAX_PATH];	// Component file(DLL) path
            HMODULE hDll;			// Handle to the DLL
        };

        std::vector<interfaceInfo> vecInterfaceInfo_;

        Result enumComponent();
        Result registerInterface(LPCTSTR szFileName);

        // application init flags
        Uint initFlags_;

        std::ofstream logFile_;

    };

};

#endif // _UAPBE_APPIMPL_H_
