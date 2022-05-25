#ifndef _UAP_UITEXTURE_H_
#define _UAP_UITEXTURE_H_

namespace uap
{

    class UiTextureImpl : public IUiTexture
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &rUuid, void **ppv);

        // IUiTexture
        virtual Result loadTexture(Char* path);
        virtual int width()
        {
            return width_;
        }
        virtual int height()
        {
            return height_;

        }
        virtual void* texture()
        {
            return (void*)srv_;
        }

        static Result createInstance(ID3D11Device *d3dDevice, void **ppv)
        {
            UiTextureImpl *p = new UiTextureImpl(d3dDevice);
            if (p)
            {
                *(IUiTexture **)ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }


    private:
        UiTextureImpl(ID3D11Device* d3dDevice)
            : refcount_(1)
            , width_(0)
            , height_(0)
            , d3dDevice_(d3dDevice)
        {
        }
        Ulong refcount_;

        ID3D11Device *d3dDevice_;
        ID3D11ShaderResourceView* srv_;
        int width_;
        int height_;

    }; // @class UiTextureImpl

} // @namespace uap

#endif // _UAP_UITEXTURE_H_