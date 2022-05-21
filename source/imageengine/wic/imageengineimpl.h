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
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &,void **);

        // IImageEngine
        virtual Result initialize(IApplication* piApp);
    private:
        Ulong refcount_;

        sptr<IApplication> spApp_;
    };

};

#endif //_UAP_IMAGEENGINEIMPL_H_
