#ifndef _UAP_TOOLBAR_IMPL_H_
#define _UAP_TOOLBAR_IMPL_H_

namespace uap
{

    class ToolBarImpl : public IToolBar
                , public IDraw
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &rUuid, void **ppv);

        // IToolBar
        virtual Result initialize(IAttributes *piAttributes);

        virtual Result buildToolBarFromTTF(const Char* filename, Ushort min, Ushort max);
        virtual Result addButton(const Char* label);

        // IDraw
        virtual Result draw();

        static Result createInstance(IToolBar **ppv)
        {
            ToolBarImpl *p = new ToolBarImpl();
            if (p)
            {
                *ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        ToolBarImpl()
            :refcount_(1)
            , heightToolBar_(TOOLBAR_HEIGHT)
        {

        }
        Ulong refcount_;

        std::vector<const Char* > vecLabel_;

        float heightToolBar_;

    }; // @class ToolBarImpl

} // @namespace uap

#endif // _UAP_TOOLBAR_IMPL_H_
