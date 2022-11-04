#ifndef _UAP_UI_STATUSBAR_IMPL_H_
#define _UAP_UI_STATUSBAR_IMPL_H_

namespace uap
{

    class StatusBarImpl : public IStatusBar
                , public IFrame
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &rUuid, void **ppv);

        // IStatusBar
        virtual Result initialize(IAttributes *piAttributes);


        // IFrame
        virtual Result drawFrame();

        static Result createInstance(IStatusBar **ppv)
        {
            StatusBarImpl *p = new StatusBarImpl();
            if (p)
            {
                *ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        StatusBarImpl()
            :refcount_(1)
            ,heightStatusBar_(FONT_SIZE+6.0f)
        {

        }
        Ulong refcount_;

        float heightStatusBar_;

    }; // @class StatusBarImpl

} // @namespace uap

#endif // _UAP_STATUSBAR_IMPL_H_
