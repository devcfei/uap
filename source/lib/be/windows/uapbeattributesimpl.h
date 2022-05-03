#ifndef _UAPBE_ATTRIBUTESIMPL_H_
#define _UAPBE_ATTRIBUTESIMPL_H_

namespace uap
{

    class CAttributesImpl : public IAttributes
    {
    public:
        CAttributesImpl()
            : refcount_(1)
        {
        }
        virtual const Uuid& uuidof();
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const uap::Uuid &,void **);

        //
        virtual Result setUint(Ulong key, Uint value) ;
        virtual Result getUint(Ulong key, Uint &value) ;
    private:
        const Uuid uuid_= IID_IATTRIBUTES;
        Ulong refcount_;
    };

};

#endif // _UAPBE_ATTRIBUTESIMPL_H_
