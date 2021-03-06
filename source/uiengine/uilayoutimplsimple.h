#ifndef _UAP_UILAYOUTIMPL_SIMPLE_
#define _UAP_UILAYOUTIMPL_SIMPLE_

namespace uap
{



    class UiLayoutImplSimple: public IUiLayout
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &,void **);

        // IUiLayout
        virtual Result initializeLayout(IUiEngine* piUiEngine, IAttributes* piAttributes);
        virtual Result draw();

        static Result createInstance(void **ppv)
        {
            UiLayoutImplSimple *p = new UiLayoutImplSimple();
            if (p)
            {
                *(IUiLayout **)ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        UiLayoutImplSimple()
            : refcount_(1)
        {
        }

        Ulong refcount_;
    }; // @class UiLayoutImplSimple




} // @namespace uap

#endif // _UAP_UILAYOUTIMPL_SIMPLE_
