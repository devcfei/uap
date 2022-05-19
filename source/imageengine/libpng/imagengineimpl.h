#ifndef _UAP_IMAGEENGINEIMPL_H_
#define _UAP_IMAGEENGINEIMPL_H_

#include <uap.h>

namespace uap
{

    class ImageEngineImpl : public IImageEngine
    {
    public:
        ImageEngineImpl()
            : refcount_(1)
        {
        }
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const uap::Uuid &,void **);

        // IImageEngine
        virtual Result initialize()=0;
    private:
        const Uuid uuid_= IID_IMAGEENGINE;
        Ulong refcount_;
    };

};

#endif //_UAP_IMAGEENGINEIMPL_H_
