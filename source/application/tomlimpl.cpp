#include "common.h"


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
            UAP_TRACE("TomlImpl delete!!!!\n");
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

    Result TomlImpl::getInt(const Char *k, int &v)
    {
        Result r = R_SUCCESS;

        try
        {
            v = toml::find<int>(data_, k);
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

    Result TomlImpl::getString(const Char *k,Char *v ,Size_t length, Size_t *actureLength)
    {
        Result r = R_SUCCESS;

        try
        {
            auto  as =toml::find<std::string>(data_, k);
            
            if (length <as.length())
            {
                r = R_BUFFER_TOO_SMALL;
                if (actureLength)
                        *actureLength = as.length();
                return r;
            }

            //strncpy(v, as.c_str(),as.length()+1);

            StringCchCopyA(v,length,as.c_str());
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

    Result TomlImpl::getBool(const Char *s, const Char *k, bool &v)
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

    Result TomlImpl::getInt(const Char *s, const Char *k, int &v)
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
    
    Result TomlImpl::getString(const Char* s,const Char *k, Char *v, Size_t length, Size_t *actureLength)
    {
        Result r = R_SUCCESS;

        try
        {

            const auto &section = toml::find(data_, s);
            auto as = toml::find<std::string>(section, k);

            if (length <as.length())
            {
                r = R_BUFFER_TOO_SMALL;
                if (actureLength)
                        *actureLength = as.length();
                return r;
            }

            //strncpy(v, as.c_str(),as.length()+1);

            StringCchCopyA(v,length,as.c_str());

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

    Result TomlImpl::getBool(const Char *s, const Char *ss, const Char *k, bool &v)
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

    Result TomlImpl::getInt(const Char *s, const Char *ss, const Char *k, int &v)
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

    Result TomlImpl::getString(const Char *s, const Char *ss, const Char *k, Char *v, Size_t length, Size_t *actureLength)
    {
        Result r = R_SUCCESS;

        try
        {

            const auto &section = toml::find(data_, s);
            const auto &sub = toml::find(section, ss);
            auto as = toml::find<std::string>(sub, k);

            if (length <as.length())
            {
                r = R_BUFFER_TOO_SMALL;
                if (actureLength)
                        *actureLength = as.length();
                return r;
            }

            //strncpy(v, as.c_str(),as.length()+1);

            StringCchCopyA(v,length,as.c_str());

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

    Result TomlImpl::getBool(const Char *k, bool &v)
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

    Result TomlImpl::setBool(const Char *k,bool& v)
    {
        Result r = R_SUCCESS;

        try
        {          
            data_[k] = v;        
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

    Result TomlImpl::setInt(const Char *k,int &v)
    {
        Result r = R_SUCCESS;

        try
        {          
            data_[k] = v;        
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

    Result TomlImpl::setString(const Char *k,const Char *v, Size_t length)
    {
        Result r = R_SUCCESS;

        try
        {  
            data_[k] = v;   
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

    Result TomlImpl::setBool(const Char *s, const Char *k, bool& v)
    {
        Result r = R_SUCCESS;

        try
        {
           data_[s][k] = v;  
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

    Result TomlImpl::setInt(const Char *s, const Char *k, int &v)
    {
        Result r = R_SUCCESS;

        try
        {
           data_[s][k] = v;  
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

    Result TomlImpl::setString(const Char *s, const Char *k, const Char *v, Size_t length)
    {
        Result r = R_SUCCESS;

        try
        {
           data_[s][k] = v;  
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

    Result TomlImpl::setBool(const Char *s, const Char *ss, const Char *k, bool& v)
    {
        Result r = R_SUCCESS;

        try
        {
            data_[s][ss][k] = v;  
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

    Result TomlImpl::setInt(const Char *s, const Char *ss, const Char *k, int &v)
    {
        Result r = R_SUCCESS;

        try
        {
            data_[s][ss][k] = v;  
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

    Result TomlImpl::setString(const Char *s, const Char *ss, const Char *k, const Char *v, Size_t length)
    {
        Result r = R_SUCCESS;

        try
        {
            data_[s][ss][k] = v;  
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
