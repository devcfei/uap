#ifndef _UAPBE_ATTRIBUTESIMPL_H_
#define _UAPBE_ATTRIBUTESIMPL_H_

namespace uap
{

    inline bool operator<(const Uuid& lhs, const Uuid& rhs)
    {
        return (memcmp(&lhs, &rhs, sizeof(Uuid)) > 0 ? true : false);
    }



    class AttributesImpl : public IAttributes
    {
    public:
        AttributesImpl()
            : refcount_(1)
        {
        }
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &,void **);

        // IAttributes
        virtual Result setUint(const Uuid & key, Uint value);
        virtual Result getUint(const Uuid & key, Uint &value);

        virtual Result setUlong(const Uuid & key, Ulong value);
        virtual Result getUlong(const Uuid & key, Ulong &value);

        virtual Result setPtr(const Uuid &key, void *value);
        virtual Result getPtr(const Uuid &key, void *&value);

        virtual Result setUuid(const Uuid & key, Uuid value);
        virtual Result getUuid(const Uuid & key, Uuid &value);

        virtual Result setBlob(const Uuid & key, const Uchar* buff, Ulong bufSize);
        virtual Result getBlob(const Uuid & key, Uchar* buff, Ulong bufSize, Ulong* actualSize);


        virtual Result setString(const Uuid & key, const Char* s, Ulong length);
        virtual Result getString(const Uuid & key, Char* s, Ulong length, Ulong* actureLength);


        virtual Result deleteKey(const Uuid & key);
        virtual Result deleteAllKeys();
    private:
        Ulong refcount_;

        enum KeyType
        {
            KT_UINT,
            KT_ULONG,
            KT_POINTER,
            KT_UUID,
            KT_BLOB,
            KT_STRING,
        };
        struct KeyValue
        {
            KeyType vt;
            union
            {
                Uint ui;
                Ulong ul;
                void* ptr;
                Uuid uuid;
                struct Blob
                {
                    Uchar *pbuf;
                    Ulong size;
                } blob;

                struct String
                {
                    Char *p;
                    Ulong len;
                } str;  
            };
        };

        std::map<Uuid, KeyValue> map_;
    };

};

#endif // _UAPBE_ATTRIBUTESIMPL_H_
