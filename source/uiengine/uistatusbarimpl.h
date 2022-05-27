#ifndef _UAP_UISTATUSBAR_H_
#define _UAP_UISTATUSBAR_H_

namespace uap
{

    class UiStatusBarImpl : public IUiStatusBar
                , public IDraw
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &rUuid, void **ppv);

        // IUiStatusBar
        virtual Result initialize(IAttributes *piAttributes);


        // IDraw
        virtual Result draw();

        static Result createInstance(IUiStatusBar **ppv)
        {
            UiStatusBarImpl *p = new UiStatusBarImpl();
            if (p)
            {
                *ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        UiStatusBarImpl()
            :refcount_(1)
            ,heightStatusBar_(FONT_SIZE+6.0f)
        {

        }
        Ulong refcount_;

        float heightStatusBar_;

    }; // @class UiStatusBarImpl

} // @namespace uap

#endif // _UAP_UISTATUSBAR_H_
