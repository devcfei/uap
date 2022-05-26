#ifndef _UAP_UITOOLBAR_H_
#define _UAP_UITOOLBAR_H_

namespace uap
{

    class UiToolBarImpl : public IUiToolBar
                , public IDraw
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &rUuid, void **ppv);

        // IUiToolBar
        virtual Result initialize(IAttributes *piAttributes);

        virtual Result buildToolBarFromTTF(const Char* filename, Ushort min, Ushort max);
        virtual Result addButton(const Char* label);

        // IDraw
        virtual Result draw();

        static Result createInstance(IUiToolBar **ppv)
        {
            UiToolBarImpl *p = new UiToolBarImpl();
            if (p)
            {
                *ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        UiToolBarImpl()
            :refcount_(1)
            , heightToolBar_(32.0f)
        {

        }
        Ulong refcount_;

        std::vector<const Char* > vecLabel_;

        float heightToolBar_;

    }; // @class UiToolBarImpl

} // @namespace uap

#endif // _UAP_UITOOLBAR_H_
