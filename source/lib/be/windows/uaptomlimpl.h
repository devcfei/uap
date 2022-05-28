#ifndef _UAPBE_TOML_H_
#define _UAPBE_TOML_H_

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

        virtual Result getBool(Char *k, bool& v);
        virtual Result getInt(Char *k, int& v);
        virtual Result getBool(Char* s, Char *k, bool& v);
        virtual Result getInt(Char* s,Char *k, int& v);
        virtual Result getBool(Char* s, Char* ss,  Char *k, bool& v);
        virtual Result getInt(Char* s,Char *ss, Char *k, int& v);

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

#endif // _UAPBE_TOML_H_
