#include "common.h"

#define STB_IMAGE_IMPLEMENTATION//TEX_INSPECT_CHANGE
#include <stb_image.h> //TEX_INSPECT_CHANGE


namespace uap
{

    Ulong TextureImpl::addRef()
    {
        return InterlockedIncrement(&refcount_);
    }
    Ulong TextureImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            delete this;
        }
        return ref;
    }
    Result TextureImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_ITEXTURE))
        {
            IUiTexture *pi = static_cast<IUiTexture *>(this);
            addRef();

            *((IUiTexture **)ppv) = pi;
            r = R_SUCCESS;
        }

        return r;
    }


    // IUiTexture
    Result TextureImpl::loadTexture(const Char* path)
    {
        Result r = R_SUCCESS;
        // Load from disk into a raw RGBA buffer

        unsigned char* image_data = stbi_load(path, &width_, &height_, NULL, 4);
        if (image_data == NULL)
        {
            r = R_FILE_NOT_EXIST;
            return r;
        }

        // Create texture
        D3D11_TEXTURE2D_DESC desc;
        ZeroMemory(&desc, sizeof(desc));
        desc.Width = width_;
        desc.Height = height_;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.CPUAccessFlags = 0;

        ID3D11Texture2D *pTexture = NULL;
        D3D11_SUBRESOURCE_DATA subResource;
        subResource.pSysMem = image_data;
        subResource.SysMemPitch = desc.Width * 4;
        subResource.SysMemSlicePitch = 0;
        d3dDevice_->CreateTexture2D(&desc, &subResource, &pTexture);

        // Create texture view
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
        ZeroMemory(&srvDesc, sizeof(srvDesc));
        srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = desc.MipLevels;
        srvDesc.Texture2D.MostDetailedMip = 0;
        d3dDevice_->CreateShaderResourceView(pTexture, &srvDesc, &srv_);
        pTexture->Release();


        stbi_image_free(image_data);

        return r;

    }


} // @namespace uap

