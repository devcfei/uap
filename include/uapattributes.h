#ifndef _UAP_ATTRIBUTES_H_
#define _UAP_ATTRIBUTES_H_


#ifndef _UAP_RESULT_H_
#error uapattributes.h requires uapresult.h to be included first
#endif


#include <string>

namespace uap
{

    // {50bee31c-be5e-4327-9b8f-dbfca279f3d6}
    DEFINE_UUID(IID_IATTRIBUTES, 
	    0x50bee31c, 0xbe5e, 0x4327, 0x9b, 0x8f, 0xdb, 0xfc, 0xa2, 0x79, 0xf3, 0xd6);


    class IAttributes : public IUniversal
    {
    public:
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &,void **) = 0;

        // IAttributes
        virtual Result setUint(const Uuid & key, Uint value) = 0;
        virtual Result getUint(const Uuid & key, Uint &value) = 0;

        virtual Result setUlong(const Uuid & key, Ulong value) = 0;
        virtual Result getUlong(const Uuid & key, Ulong &value) = 0;

        virtual Result setPtr(const Uuid & key, void* value) = 0;
        virtual Result getPtr(const Uuid & key, void* &value) = 0;

        virtual Result setUuid(const Uuid & key, Uuid value) = 0;
        virtual Result getUuid(const Uuid & key, Uuid &value) = 0;

        virtual Result setBlob(const Uuid & key, const Uchar* buff, Ulong bufSize) = 0;
        virtual Result getBlob(const Uuid & key, Uchar* buff, Ulong bufSize, Ulong* actualSize) = 0;


        virtual Result setString(const Uuid & key, const Char* s, Size_t length) = 0;
        virtual Result getString(const Uuid & key, Char* s, Size_t length, Size_t* actureLength) = 0;



        virtual Result deleteKey(const Uuid & key) = 0;
        virtual Result deleteAllKeys() = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IATTRIBUTES;

    }; // @class IAttributes

} // @namespace uap


#endif // _UAP_ATTRIBUTES_H_