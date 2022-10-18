#ifndef _UAP_UIMENUBAR_H_
#define _UAP_UIMENUBAR_H_

namespace uap
{

    class UiMenuBarImpl : public IUiMenuBar
                , public IDraw
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &rUuid, void **ppv);

        // IUiMenuBar
        virtual Result initialize(IAttributes *piAttributes);
        virtual Result setMenu(IMenu* piMenu) ;

        // IDraw
        virtual Result draw();

        static Result createInstance(void **ppv)
        {
            UiMenuBarImpl *p = new UiMenuBarImpl();
            if (p)
            {
                *(IUiMenuBar **)ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        UiMenuBarImpl()
            :refcount_(1)
        {

        }
        Ulong refcount_;

        sptr<IMenu> spMenu_;
    }; // @class UiMenuBarImpl

} // @namespace uap

#endif // _UAP_UIMENUBAR_H_
