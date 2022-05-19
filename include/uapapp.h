#ifndef _UAP_APP_H_
#define _UAP_APP_H_

#ifndef _UAP_RESULT_H_
#error uapapp.h requires uapresult.h to be included first
#endif


namespace uap
{   
    class IApplication : public IUnknown
    {
    public:
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const uap::Uuid &, void **) = 0;

        // IApplication
        virtual Result initialize(IAttributes* piAttributes) = 0;
        virtual Result createInterface(const uap::Uuid & rUuid, void **ppv) = 0;

    }; // @class IApplication


    // application attributes
    
    // {181e8813-adad-4e43-826d-6553d11ed520}
    DEFINE_UUID(UUID_APP_INIT_FLAGS, 
        0x181e8813, 0xadad, 0x4e43, 0x82, 0x6d, 0x65, 0x53, 0xd1, 0x1e, 0xd5, 0x20);

    enum AppInitFlags
    {
        APP_INIT_LOGTRACE_ENALBE=   0x00000001,
        APP_INIT_COMPONENT_ENALBE=  0x00000002,
    };


}; // @namespace uap

#endif // _UAP_APP_H_