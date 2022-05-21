#ifndef _UAP_IMAGEENGINE_H_
#define _UAP_IMAGEENGINE_H_


#ifndef _UAP_H_
#error uapimageengine.h requires uap.h to be included first
#endif

namespace uap
{

    // {b9076045-4991-4dd0-8a6f-f44486168acd}
    DEFINE_UUID(IID_IMAGEENGINE, 
        0xb9076045, 0x4991, 0x4dd0, 0x8a, 0x6f, 0xf4, 0x44, 0x86, 0x16, 0x8a, 0xcd);


    class IImageEngine : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &,void **) = 0;

        // IImageEngine
        virtual Result initialize(IApplication* piApp)=0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IMAGEENGINE;

    }; // @class IAttributes

} // @namespace uap


#endif // _UAP_IMAGEENGINE_H_