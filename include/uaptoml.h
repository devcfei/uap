#ifndef _UAP_TOML_H_
#define _UAP_TOML_H_

#ifndef _UAP_APP_H_
#error uaptoml.h requires uapapp.h to be included first
#endif

namespace uap
{

    // {67a79d9e-2826-4ebb-bd87-40e0c9d61a1c}
    DEFINE_UUID(IID_ITOML,
                0x67a79d9e, 0x2826, 0x4ebb, 0xbd, 0x87, 0x40, 0xe0, 0xc9, 0xd6, 0x1a, 0x1c);

    class IToml : public IUniversal
    {
    public:
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IToml
        virtual Result initialize(IApplication *piApp, Char *filename) = 0;

        virtual Result getBool(const Char *k, bool& v) = 0;       
        virtual Result getInt(const Char *k, int& v) = 0;
        virtual Result getString(const Char *k,Char *v ,Size_t length, Size_t *actureLength) = 0;      
        virtual Result getBool(const Char* s, const Char *k, bool& v) = 0;        
        virtual Result getInt(const Char* s,const Char *k, int& v) = 0;
        virtual Result getString(const Char* s, const Char *k, Char *v, Size_t length, Size_t *actureLength) = 0;
        virtual Result getBool(const Char* s, const Char* ss,  const Char *k, bool& v) = 0;
        virtual Result getInt(const Char* s,const Char *ss, const Char *k, int& v) = 0;
        virtual Result getString(const Char* s,const Char *ss, const Char *k, Char *v, Size_t length, Size_t *actureLength) = 0;

        virtual Result setBool(const Char *k, bool& v) = 0;
        virtual Result setInt(const Char *k , int &v) = 0;
        virtual Result setString(const Char *k , const Char *v, Size_t length) = 0;
        virtual Result setBool(const Char* s,const Char *k, bool& v) = 0;
        virtual Result setInt(const Char* s,const Char *k, int& v) = 0;
        virtual Result setString(const Char* s,const Char *k, const Char *v, Size_t length) = 0;
        virtual Result setBool(const Char* s,const Char *ss, const Char *k, bool& v) = 0;
        virtual Result setInt(const Char* s,const Char *ss, const Char *k, int& v) = 0;
        virtual Result setString(const Char* s,const Char *ss, const Char *k, const Char *v, Size_t length)= 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_ITOML;
    }; // @class IToml

} // @namespace uap

#endif // _UAP_TOML_H_