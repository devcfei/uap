#ifndef _UAP_UIENGINEIMPL_H_
#define _UAP_UIENGINEIMPL_H_


namespace uap
{

    class UiEngineImpl : public IUiEngine
    {
    public:
        UiEngineImpl()
            : refcount_(1)
        {
        }
        virtual const Uuid& uuidof();
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const uap::Uuid &,void **);

        // IUiEngine
        virtual Result initialize();
    private:
        const Uuid uuid_= IID_IMAGEENGINE;
        Ulong refcount_;
    };

};

#endif //_UAP_UIENGINEIMPL_H_
