#ifndef _SETTING_FRAME_H_
#define _SETTING_FRAME_H_

namespace uap
{
    class SettingFrameImpl : public IFrame
    {

    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &rUuid, void **ppv);

        // IFrame
        virtual Result drawFrame();


        static Result createInstance(IFrame **ppv, IDraw* pDraw)
        {
            SettingFrameImpl *p = new SettingFrameImpl(pDraw);
            if (p)
            {
                *ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        Ulong refcount_;

        SettingFrameImpl(IDraw* pDraw)
            : refcount_(1)
            , spDraw_(pDraw)
        {

        }


        sptr<IDraw> spDraw_;

    };

}

#endif