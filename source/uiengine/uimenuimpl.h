#ifndef _UAP_MENU_IMPL_H_
#define _UAP_MENU_IMPL_H_

namespace uap
{
    // IMenu implementation
    class MenuImpl : public IMenu
        , public IDraw
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &,void **);

        // IDraw
        virtual Result draw();

        // IMenu
        virtual Result initialize(IAttributes *piAttributes, IEvent* piEvent);
        virtual Result addItem(const Char *name, Boolean check, IMenu* submenu, EventId evtId);
        virtual Result addSeparator();


        static Result createInstance(IMenu **ppi)
        {
            MenuImpl *p = new MenuImpl();
            if (p)
            {
                *ppi = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }


    private:
        MenuImpl()
            : refcount_(1)
        {
        }
        Ulong refcount_;

        std::string title_;

        struct MenuItem
        {
            Boolean separator;
            std::string name;   // display name
            Boolean check;      // check status
            IMenu* submenu;     // sub-menu
            EventId evtId;      // event ID
        };

        std::vector<MenuItem> vecMenuItem_;
        Result drawMenu(IMenu* pMenu);

        sptr<IEvent> spEvent_;

    };
}


#endif //_UAP_MENU_IMPL_H_
