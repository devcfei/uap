#include "uapbe.h"





namespace uap
{



    Ulong AttributesImpl::addRef()
    {
        UAP_TRACE("AttributesImpl::addRef\n");

        return InterlockedIncrement(&refcount_);
    }
    Ulong AttributesImpl::release()
    {
        UAP_TRACE("AttributesImpl::release\n");

        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            delete this;
        }
        return ref;
    }
    Result AttributesImpl::queryInterface(const Uuid &, void **)
    {
        return R_SUCCESS;
    }

    // IAttributes

    Result AttributesImpl::setUint(const Uuid &key, Uint value)
    {
        UAP_TRACE("AttributesImpl::setUint - value=%d\n", value);

        KeyValue var;

        auto it = map_.find(key);
        if (it != map_.end())
        {
            // overwrite the current item
            KeyValue &rvar= it->second;
            UAP_ASSERT(rvar.vt == KT_UINT);
            rvar.ui = value;
        }
        else
        {
            var.vt = KT_UINT;
            var.ui = value;
            map_.insert(std::make_pair(key, var));
        }


        return R_SUCCESS;
    }

    Result AttributesImpl::getUint(const Uuid &key, Uint &value)
    {
        Result r = R_NOT_FOUND;

        auto it = map_.find(key);
        if (it != map_.end())
        {
            KeyValue var = it->second;
            if (var.vt == KT_UINT)
            {
                value = var.ui;
                r = R_SUCCESS;
            }
            else
            {
                r = R_INVALID_PARAMETERS;
            }
        }

        UAP_TRACE("AttributesImpl::getUint - value=%d\n", value);


        return r;
    }

    Result AttributesImpl::setUlong(const Uuid &key, Ulong value)
    {
        UAP_TRACE("AttributesImpl::setUlong\n");

        KeyValue var;

        auto it = map_.find(key);
        if (it != map_.end())
        {
            // overwrite the current item
            KeyValue &rvar= it->second;
            UAP_ASSERT(rvar.vt == KT_ULONG);
            rvar.ui = value;
        }
        else
        {
            var.vt = KT_ULONG;
            var.ul = value;
            map_.insert(std::make_pair(key, var));
        }


        return R_SUCCESS;
    }

    Result AttributesImpl::getUlong(const Uuid &key, Ulong &value)
    {
        Result r = R_NOT_FOUND;

        auto it = map_.find(key);
        if (it != map_.end())
        {
            KeyValue var = it->second;
            if (var.vt == KT_ULONG)
            {
                value = var.ul;
                r = R_SUCCESS;
            }
            else
            {
                r = R_INVALID_PARAMETERS;
            }
        }

        UAP_TRACE("AttributesImpl::getUlong - value=%d\n", value);


        return r;
    }



    Result AttributesImpl::setPtr(const Uuid &key, void *value)
    {
        UAP_TRACE("AttributesImpl::setPtr\n");

        KeyValue var;

        auto it = map_.find(key);
        if (it != map_.end())
        {
            // overwrite the current item
            KeyValue &rvar= it->second;
            UAP_ASSERT(rvar.vt == KT_POINTER);
            rvar.ptr = value;
        }
        else
        {
            var.vt = KT_POINTER;
            var.ptr = value;
            map_.insert(std::make_pair(key, var));
        }


        return R_SUCCESS;
    }
    Result AttributesImpl::getPtr(const Uuid &key, void *&value)
    {
        Result r = R_NOT_FOUND;

        auto it = map_.find(key);
        if (it != map_.end())
        {
            KeyValue var = it->second;
            if (var.vt == KT_POINTER)
            {
                value = var.ptr;
                r = R_SUCCESS;
            }
            else
            {
                r = R_INVALID_PARAMETERS;
            }
        }

        UAP_TRACE("AttributesImpl::getUlong - value=%d\n", value);


        return r;
    }


    Result AttributesImpl::setUuid(const Uuid &key, Uuid value)
    {
        UAP_TRACE("AttributesImpl::setUuid\n");

        KeyValue var;

        auto it = map_.find(key);
        if (it != map_.end())
        {
            // overwrite the current item
            KeyValue &rvar= it->second;
            UAP_ASSERT(rvar.vt == KT_UUID);
            rvar.uuid = value;
        }
        else
        {
            var.vt = KT_UUID;
            var.uuid = value;
            map_.insert(std::make_pair(key, var));
        }

       
        return R_SUCCESS;
    }
    Result AttributesImpl::getUuid(const Uuid &key, Uuid &value)
    {
        Result r = R_NOT_FOUND;

        auto it = map_.find(key);
        if (it != map_.end())
        {
            KeyValue var = it->second;
            if (var.vt == KT_UUID)
            {
                value = var.uuid;
                r = R_SUCCESS;
            }
            else
            {
                r = R_INVALID_PARAMETERS;
            }
        }

        UAP_TRACE("AttributesImpl::getUuid \n");

        return r;
    }

    Result AttributesImpl::setBlob(const Uuid &key, const Uchar *buff, Ulong bufSize)
    {
        Result r = R_SUCCESS;

        KeyValue var;

        UAP_TRACE("AttributesImpl::setBlob\n");


        auto it = map_.find(key);
        if (it != map_.end())
        {
            // overwrite the current item
            KeyValue& rvar = it->second;
            UAP_ASSERT(rvar.vt == KT_BLOB);
            if (rvar.blob.size != bufSize)
            {
                delete [] rvar.blob.pbuf;
                rvar.blob.pbuf = new Uchar[bufSize];
                if (rvar.blob.pbuf == NULL)
                {
                    r = R_NO_MEMORY;
                    return r;
                }
                rvar.blob.size = bufSize;
            }

            CopyMemory(rvar.blob.pbuf, buff, bufSize);
        }
        else
        {
            var.vt = KT_BLOB;
            var.blob.pbuf = new Uchar[bufSize];
            if (var.blob.pbuf == NULL)
            {
                r = R_NO_MEMORY;
                return r;
            }
            CopyMemory(var.blob.pbuf, buff, bufSize);
            var.blob.size = bufSize;

            map_.insert(std::make_pair(key, var));

        }



        return r;
    }

    Result AttributesImpl::getBlob(const Uuid &key, Uchar *buff, Ulong bufSize, Ulong *actualSize)
    {
        Result r = R_NOT_FOUND;

        UAP_TRACE("AttributesImpl::getBlob\n");

        auto it = map_.find(key);
        if (it != map_.end())
        {
            KeyValue var = it->second;
            if (var.vt == KT_BLOB)
            {
                if (bufSize < var.blob.size)
                {
                    r = R_BUFFER_TOO_SMALL;
                    *actualSize = var.blob.size;
                    return r;
                }

                CopyMemory(buff, var.blob.pbuf, var.blob.size);
                *actualSize = var.blob.size;
                r = R_SUCCESS;
            }
            else
            {
                r = R_INVALID_PARAMETERS;
            }
        }
        return r;
    }

    Result AttributesImpl::setString(const Uuid &key, const Char *s, Ulong length)
    {
        Result r = R_SUCCESS;

        KeyValue var;

        UAP_TRACE("AttributesImpl::setString\n");

        auto it = map_.find(key);
        if (it != map_.end())
        {
            // overwrite the current item
            KeyValue &rvar = it->second;
            UAP_ASSERT(rvar.vt == KT_STRING);
            if (rvar.str.len != length)
            {
                delete[] rvar.str.p;
                rvar.str.p = new Char[length + 1];
                if (rvar.str.p == NULL)
                {
                    r = R_NO_MEMORY;
                    return r;
                }
                rvar.str.len = length;
            }

            StringCbCopyA(rvar.str.p, length + 1, s);
        }
        else
        {
            var.vt = KT_STRING;
            var.str.p = new Char[length + 1];
            if (var.str.p == NULL)
            {
                r = R_NO_MEMORY;
                return r;
            }
            StringCbCopyA(var.str.p, length + 1, s);

            var.str.len = length;

            map_.insert(std::make_pair(key, var));
        }

        return r;
    }


    Result AttributesImpl::getString(const Uuid &key, Char *s, Ulong length, Ulong *actureLength)
    {
        Result r = R_NOT_FOUND;

        UAP_TRACE("AttributesImpl::getString\n");

        auto it = map_.find(key);
        if (it != map_.end())
        {
            KeyValue var = it->second;
            if (var.vt == KT_STRING)
            {
                if (length < var.str.len)
                {
                    r = R_BUFFER_TOO_SMALL;
                    if(actureLength)
                        *actureLength = var.str.len;
                    return r;
                }

                StringCbCopyA(s, length, var.str.p);
                if(actureLength)
                    *actureLength = var.str.len;
                r = R_SUCCESS;
            }
            else
            {
                r = R_INVALID_PARAMETERS;
            }
        }
        return r;
    }

    Result AttributesImpl::deleteKey(const Uuid &key)
    {
        Result r = R_NOT_FOUND;


        UAP_TRACE("AttributesImpl::deleteKey\n");

        auto it = map_.find(key);
        if (it != map_.end())
        {
            KeyValue var = it->second;

            if (var.vt == KT_BLOB)
            {
                delete [] var.blob.pbuf;
            }

            if (var.vt == KT_STRING)
            {
                delete [] var.str.p;
            }


            map_.erase(it++);
            r = R_SUCCESS;

        }

        return r;
    }

    Result AttributesImpl::deleteAllKeys()
    {
        Result r = R_NOT_IMPL;
        UAP_TRACE("AttributesImpl::deleteAllKeys\n");

        return r;
    }

}; //@namespace uap
