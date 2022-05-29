#ifndef _APPLICATION_IMPL_H_
#define _APPLICATION_IMPL_H_

// implementation for uap::application::IApplication

namespace uap
{

    class ApplicationImpl : public IApplication
        , public FileLoggerImpl
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &, void **);

        // IApplication
        virtual Result initialize(IAttributes *piAttributes);
        virtual Result createInstance(const Uuid &rUuid, void **ppv);
        virtual Result getCurrentPath(Char *path, Ulong size);

        static Result createInstance(IApplication **ppiApplication)
        {
            ApplicationImpl *p = new ApplicationImpl();
            if (p)
            {
                *ppiApplication = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        ApplicationImpl()
            : refcount_(1)
        {
        }
        Ulong refcount_;

        ApplicationConfiguration appConfig_;

        // components
        struct interfaceInfo
        {
            const Uuid uidComponent;
            TCHAR path[MAX_PATH]; // Component file(DLL) path
            HMODULE hDll;         // Handle to the DLL
        };

        std::vector<interfaceInfo> vecInterfaceInfo_;

        Result enumComponent();
        Result registerInterface(LPCTSTR szFileName);


        // filelogger

        sptr<IFileLogger> fileLogger_;

    }; //@class ApplicationImpl

} // @namespace uap

#endif //_APPLICATION_IMPL_H_