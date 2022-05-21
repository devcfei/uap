#ifndef _UAP_APP_H_
#define _UAP_APP_H_

#ifndef _UAP_RESULT_H_
#error uapapp.h requires uapresult.h to be included first
#endif


namespace uap
{
    // {90911642-e6ef-4699-851a-296f1e90cd4b}
    DEFINE_UUID(IDD_IAPP,
                0x90911642, 0xe6ef, 0x4699, 0x85, 0x1a, 0x29, 0x6f, 0x1e, 0x90, 0xcd, 0x4b);

    class IApplication : public IUniversal
    {
    public:
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IApplication
        virtual Result initialize(IAttributes* piAttributes) = 0;
        virtual Result createInterface(const Uuid & rUuid, void **ppv) = 0;

    // uuid
    static const Uuid uuid()
    {
        return uuid_;
    }

private:
    inline static const Uuid uuid_ = IDD_IAPP;

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

    // {406aa44a-cccc-4bc8-a7ba-325db6240409}
    DEFINE_UUID(UUID_APP_NAME,
                0x406aa44a, 0xcccc, 0x4bc8, 0xa7, 0xba, 0x32, 0x5d, 0xb6, 0x24, 0x04, 0x09);

} // @namespace uap

#endif // _UAP_APP_H_