#include "uapbe.h"





namespace uap
{



    Ulong AttributesImpl::addRef()
    {
        TRACE("AttributesImpl::addRef\n");

        return InterlockedIncrement(&refcount_);
    }
    Ulong AttributesImpl::release()
    {
        TRACE("AttributesImpl::release\n");

        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            delete this;
        }
        return ref;
    }
    Result AttributesImpl::queryInterface(const Uuid &, void **)
    {
        return R_OK;
    }

    // IAttributes

    Result AttributesImpl::setUint(const Uuid &key, Uint value)
    {
        TRACE("AttributesImpl::setUint - value=%d\n", value);

        KeyValue var;

        auto it = map_.find(key);
        if (it != map_.end())
        {
            // overwrite the current item
            KeyValue &rvar= it->second;
            ASSERT(rvar.vt == KT_UINT);
            rvar.ui = value;
        }
        else
        {
            var.vt = KT_UINT;
            var.ui = value;
            map_.insert(std::make_pair(key, var));
        }


        return R_OK;
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
                r = R_OK;
            }
            else
            {
                r = R_INVALID_PARAMETERS;
            }
        }

        TRACE("AttributesImpl::getUint - value=%d\n", value);


        return r;
    }

    Result AttributesImpl::setUlong(const Uuid &key, Ulong value)
    {
        TRACE("AttributesImpl::setUlong\n");

        KeyValue var;

        auto it = map_.find(key);
        if (it != map_.end())
        {
            // overwrite the current item
            KeyValue &rvar= it->second;
            ASSERT(rvar.vt == KT_ULONG);
            rvar.ui = value;
        }
        else
        {
            var.vt = KT_ULONG;
            var.ul = value;
            map_.insert(std::make_pair(key, var));
        }


        return R_OK;
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
                r = R_OK;
            }
            else
            {
                r = R_INVALID_PARAMETERS;
            }
        }

        TRACE("AttributesImpl::getUlong - value=%d\n", value);


        return r;
    }

    Result AttributesImpl::setUuid(const Uuid &key, Uuid value)
    {
        TRACE("AttributesImpl::setUuid\n");

        KeyValue var;

        auto it = map_.find(key);
        if (it != map_.end())
        {
            // overwrite the current item
            KeyValue &rvar= it->second;
            ASSERT(rvar.vt == KT_UUID);
            rvar.uuid = value;
        }
        else
        {
            var.vt = KT_UUID;
            var.uuid = value;
            map_.insert(std::make_pair(key, var));
        }

       
        return R_OK;
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
                r = R_OK;
            }
            else
            {
                r = R_INVALID_PARAMETERS;
            }
        }

        TRACE("AttributesImpl::getUuid \n");

        return r;
    }

    Result AttributesImpl::setBlob(const Uuid &key, const Uchar *buff, Ulong bufSize)
    {
        Result r = R_OK;

        KeyValue var;

        TRACE("AttributesImpl::setBlob\n");


        auto it = map_.find(key);
        if (it != map_.end())
        {
            // overwrite the current item
            KeyValue& rvar = it->second;
            ASSERT(rvar.vt == KT_BLOB);
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

        TRACE("AttributesImpl::getBlob\n");

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
                r = R_OK;
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


        TRACE("AttributesImpl::deleteKey\n");

        auto it = map_.find(key);
        if (it != map_.end())
        {
            KeyValue var = it->second;

            if (var.vt == KT_BLOB)
            {
                delete [] var.blob.pbuf;
            }

            map_.erase(it++);
            r = R_OK;

        }

        return r;
    }

    Result AttributesImpl::deleteAllKeys()
    {
        Result r = R_NOT_IMPLEMENTED;
        TRACE("AttributesImpl::deleteAllKeys\n");

        return r;
    }

}; //@namespace uap
