#ifndef _UAP_APP_H_
#define _UAP_APP_H_

#ifndef _UAP_RESULT_H_
#error uapapp.h requires uapresult.h to be included first
#endif


namespace uap
{
    // {90911642-e6ef-4699-851a-296f1e90cd4b}
    DEFINE_UUID(IID_IAPPLICATION,
                0x90911642, 0xe6ef, 0x4699, 0x85, 0x1a, 0x29, 0x6f, 0x1e, 0x90, 0xcd, 0x4b);

    class IApplication : public IUniversal
    {
    public:
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IApplication
        virtual Result initialize(IAttributes* piAttributes) = 0;
        virtual Result createInstance(const Uuid & rUuid, void **ppv) = 0;
        virtual Result getCurrentPath(Char* path, Ulong size) = 0;

    // uuid
    static const Uuid uuid()
    {
        return uuid_;
    }

private:
    inline static const Uuid uuid_ = IID_IAPPLICATION;

    }; // @class IApplication


    // application attributes    


    // application configuration UUID

    // {40930e7b-d2d4-4250-809d-ab05d5388c09}
    DEFINE_UUID(UUID_APPLICATION_CONFIGURATION,
                0x40930e7b, 0xd2d4, 0x4250, 0x80, 0x9d, 0xab, 0x05, 0xd5, 0x38, 0x8c, 0x09);

    // application configurations
    union ApplicationConfiguration
    {
        Uint ui;
        struct
        {
            Uchar enableLog:1;
            Uchar enableComponent:1;

            Uchar logLevel:4;
        }s;
    };


    // {406aa44a-cccc-4bc8-a7ba-325db6240409}
    DEFINE_UUID(UUID_APP_NAME,
                0x406aa44a, 0xcccc, 0x4bc8, 0xa7, 0xba, 0x32, 0x5d, 0xb6, 0x24, 0x04, 0x09);

} // @namespace uap

#endif // _UAP_APP_H_