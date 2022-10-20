#ifndef _UAP_MENUBAR_IMPL_H_
#define _UAP_MENUBAR_IMPL_H_

namespace uap
{

    class MenuBarImpl : public IMenuBar
                , public IDraw
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &rUuid, void **ppv);

        // IMenuBar
        virtual Result initialize(IAttributes *piAttributes);
        virtual Result setMenu(IMenu* piMenu) ;

        // IDraw
        virtual Result draw();

        static Result createInstance(IMenuBar **ppv)
        {
            MenuBarImpl *p = new MenuBarImpl();
            if (p)
            {
                *(IMenuBar **)ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        MenuBarImpl()
            :refcount_(1)
        {

        }
        Ulong refcount_;

        sptr<IMenu> spMenu_;
    }; // @class MenuBarImpl

} // @namespace uap

#endif // _UAP_MENUBAR_IMPL_H_
