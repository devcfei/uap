#ifndef _UAP_UIMENUBAR_H_
#define _UAP_UIMENUBAR_H_

namespace uap
{

    class UiMenuBarImpl : public IUiMenuBar
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &rUuid, void **ppv);

        // IUiMenuBar
        virtual Result initializeMenuBar(IAttributes *piAttributes);

        /// insert menu
        /// \name the display name
        ///
        virtual Result insertMenuItem(const Char *name, Uint id, Uint flags);

        virtual Result drawMenuBar();


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

        struct UiMenuItem
        {
            std::string name;
            Uint id;
            UiMenuFlags flags;
        };

        std::vector<UiMenuItem> vecMenuItem_;
    }; // @class UiMenuBarImpl

} // @namespace uap

#endif // _UAP_UIMENUBAR_H_
