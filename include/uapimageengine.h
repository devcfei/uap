#ifndef _UAP_IMAGEENGINE_H_
#define _UAP_IMAGEENGINE_H_


#ifndef _UAP_H_
#error uapimageengine.h requires uap.h to be included first
#endif

namespace uap
{

    class IImageEngine : public IUnknown
    {
    public:
        // IUnknown
        virtual const Uuid& uuidof()=0;
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const uap::Uuid &,void **) = 0;

        // IImageEngine
        virtual Result initialize()=0;

    }; // @class IAttributes

}; // @namespace uap


#endif // _UAP_IMAGEENGINE_H_