#ifndef _TOML_IMPL_H_
#define _TOML_IMPL_H_

namespace uap
{

    class TomlImpl : public IToml
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &, void **);

        // IToml
        virtual Result initialize(IApplication *piApp, Char *filename);

        virtual Result getBool(const Char *k, bool& v);
        virtual Result getInt(const Char *k, int& v);
        virtual Result getString(const Char *k,Char *v ,Size_t length, Size_t *actureLength);
        virtual Result getBool(const Char* s, const Char *k, bool& v);
        virtual Result getInt(const Char* s,const Char *k, int& v);
        virtual Result getString(const Char* s,const Char *k, Char *v, Size_t length, Size_t *actureLength);
        virtual Result getBool(const Char* s, const Char* ss,  const Char *k, bool& v);
        virtual Result getInt(const Char* s,const Char *ss, const Char *k, int& v);
        virtual Result getString(const Char* s,const Char *ss, const Char *k, Char *v, Size_t length, Size_t *actureLength);

        virtual Result setBool(const Char *k, bool& v);
        virtual Result setInt(const Char *k , int &v);
        virtual Result setString(const Char *k , const Char *v, Size_t length);
        virtual Result setBool(const Char* s,const Char *k, bool& v);
        virtual Result setInt(const Char* s,const Char *k, int& v);
        virtual Result setString(const Char* s,const Char *k, const Char *v, Size_t length);
        virtual Result setBool(const Char* s,const Char *ss, const Char *k, bool& v) ;
        virtual Result setInt(const Char* s,const Char *ss, const Char *k, int& v);
        virtual Result setString(const Char* s,const Char *ss, const Char *k, const Char *v, Size_t length);

        static Result createInstance(IToml **ppv)
        {
            TomlImpl *p = new TomlImpl();
            if (p)
            {
                *ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }
    private:
        TomlImpl()
            : refcount_(1)
        {
        }
        Ulong refcount_;

        toml::value data_;

    }; // @class TomlImpl
}

#endif // _TOML_IMPL_H_
