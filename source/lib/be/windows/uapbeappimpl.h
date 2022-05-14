#ifndef _UAPBE_APPIMPL_H_
#define _UAPBE_APPIMPL_H_

namespace uap
{

    class AppImpl : public IApplication
    {
    public:
        AppImpl()
            : refcount_(1)
        {
        }
        virtual const Uuid& uuidof();
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const uap::Uuid &,void **);

        //
        virtual Result initialize();
        virtual Result createInterface(const uap::Uuid & rUuid, void **ppv);

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

    };

};

#endif // _UAPBE_APPIMPL_H_
