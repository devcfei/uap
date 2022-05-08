#ifndef _UAP_IMAGEENGINEIMPL_H_
#define _UAP_IMAGEENGINEIMPL_H_


namespace uap
{

    class ImageEngineImpl : public IImageEngine
    {
    public:
        ImageEngineImpl()
            : refcount_(1)
        {
        }
        virtual const Uuid& uuidof();
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const uap::Uuid &,void **);

        // IImageEngine
        virtual Result initialize(IApp* piApp);
    private:
        const Uuid uuid_= IID_IMAGEENGINE;
        Ulong refcount_;

        sptr<IApp> spApp_;
    };

};

#endif //_UAP_IMAGEENGINEIMPL_H_
