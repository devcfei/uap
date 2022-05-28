#include "uapbe.h"

namespace uap
{

    Ulong TomlImpl::addRef()
    {
        return InterlockedIncrement(&refcount_);
    }
    Ulong TomlImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            delete this;
        }
        return ref;
    }
    Result TomlImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;
        // create the interfaces implemented by
        if (uapUuidIsEqual(rUuid, IID_ITOML))
        {
            IToml *pi = static_cast<IToml *>(this);
            addRef();

            *((IToml **)ppv) = pi;
            r = R_SUCCESS;
        }

        return r;
    }

    Result TomlImpl::initialize(IApplication *piApp, Char *filename)
    {
        Result r = R_SUCCESS;

        try
        {
            data_ = toml::parse(filename);
        }
        catch (const toml::syntax_error &e)
        {
            const char *errmsg = e.what();

            r = R_FILE_NOT_EXIST;
        }
        catch (...)
        {

            r = R_FILE_NOT_EXIST;
        }

        return r;
    }

    Result TomlImpl::getBool(Char *k, bool &v)
    {
        Result r = R_SUCCESS;

        try
        {
            v = toml::find<bool>(data_, k);
        }
        catch (toml::syntax_error &e)
        {
            const char *errmsg = e.what();
            r = R_NOT_FOUND;
        }
        catch (...)
        {
            r = R_NOT_FOUND;
        }

        return r;
    }

    Result TomlImpl::getInt(Char *k, int &v)
    {
        Result r = R_SUCCESS;

        try
        {
            v = toml::find<bool>(data_, k);
        }
        catch (toml::syntax_error &e)
        {
            const char *errmsg = e.what();
            v = false;
            r = R_NOT_FOUND;
        }
        catch (...)
        {
            r = R_NOT_FOUND;
        }

        return r;
    }

    Result TomlImpl::getBool(Char *s, Char *k, bool &v)
    {
        Result r = R_SUCCESS;

        try
        {

            const auto &section = toml::find(data_, s);
            v = toml::find<bool>(section, k);
        }
        catch (toml::syntax_error &e)
        {
            const char *errmsg = e.what();
            r = R_NOT_FOUND;
        }
        catch (...)
        {
            r = R_NOT_FOUND;
        }

        return r;
    }

    Result TomlImpl::getInt(Char *s, Char *k, int &v)
    {
        Result r = R_SUCCESS;

        try
        {

            const auto &section = toml::find(data_, s);
            v = toml::find<int>(section, k);
        }
        catch (toml::syntax_error &e)
        {
            const char *errmsg = e.what();
            r = R_NOT_FOUND;
        }
        catch (...)
        {
            v = 0;
            r = R_NOT_FOUND;
        }

        return r;
    }

    Result TomlImpl::getBool(Char *s, Char *ss, Char *k, bool &v)
    {
        Result r = R_SUCCESS;

        try
        {

            const auto &section = toml::find(data_, s);
            const auto &sub = toml::find(section, ss);
            v = toml::find<bool>(sub, k);
        }
        catch (toml::syntax_error &e)
        {
            const char *errmsg = e.what();
            r = R_NOT_FOUND;
        }
        catch (...)
        {
            r = R_NOT_FOUND;
        }

        return r;
    }

    Result TomlImpl::getInt(Char *s, Char *ss, Char *k, int &v)
    {
        Result r = R_SUCCESS;

        try
        {

            const auto &section = toml::find(data_, s);
            const auto &sub = toml::find(section, ss);
            v = toml::find<int>(sub, k);
        }
        catch (toml::syntax_error &e)
        {
            const char *errmsg = e.what();
            r = R_NOT_FOUND;
        }
        catch (...)
        {
            r = R_NOT_FOUND;
        }

        return r;
    }

}
