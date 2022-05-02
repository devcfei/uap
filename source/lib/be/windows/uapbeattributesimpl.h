#ifndef _UAPBE_ATTRIBUTESIMPL_H_
#define _UAPBE_ATTRIBUTESIMPL_H_

namespace uap
{

    class CAttributesImpl : public IAttributes
    {
    public:
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface();

        //
        virtual Result setUint(Ulong key, Uint value) ;
        virtual Result getUint(Ulong key, Uint &value) ;
    };

};

#endif // _UAPBE_ATTRIBUTESIMPL_H_
