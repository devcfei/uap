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

        virtual Result getBool(Char *k, bool& v) = 0;
        virtual Result getInt(Char *k, int& v) = 0;
        virtual Result getBool(Char* s, Char *k, bool& v) = 0;
        virtual Result getInt(Char* s,Char *k, int& v) = 0;
        virtual Result getBool(Char* s, Char* ss,  Char *k, bool& v) = 0;
        virtual Result getInt(Char* s,Char *ss, Char *k, int& v) = 0;

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