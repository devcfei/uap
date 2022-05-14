#ifndef _UAP_ATTRIBUTES_H_
#define _UAP_ATTRIBUTES_H_


#ifndef _UAP_RESULT_H_
#error uapattributes.h requires uapresult.h to be included first
#endif

namespace uap
{

    class IAttributes : public IUnknown
    {
    public:
        virtual const Uuid& uuidof()=0;
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &,void **) = 0;

        // IAttributes
        virtual Result setUint(const Uuid & key, Uint value) = 0;
        virtual Result getUint(const Uuid & key, Uint &value) = 0;

        virtual Result setUlong(const Uuid & key, Ulong value) = 0;
        virtual Result getUlong(const Uuid & key, Ulong &value) = 0;

        virtual Result setUuid(const Uuid & key, Uuid value) = 0;
        virtual Result getUuid(const Uuid & key, Uuid &value) = 0;

        virtual Result setBlob(const Uuid & key, const Uchar* buff, Ulong bufSize) = 0;
        virtual Result getBlob(const Uuid & key, Uchar* buff, Ulong bufSize, Ulong* actualSize) = 0;

        virtual Result deleteKey(const Uuid & key) = 0;
        virtual Result deleteAllKeys() = 0;



    }; // @class IAttributes

}; // @namespace uap


#endif // _UAP_ATTRIBUTES_H_