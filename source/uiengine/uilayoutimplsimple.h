#ifndef _UAP_UILAYOUTIMPL_SIMPLE_
#define _UAP_UILAYOUTIMPL_SIMPLE_

namespace uap
{



    class UiLayoutImplSimple: public ILayout
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &,void **);

        // ILayout
        virtual Result initializeLayout(IAttributes* piAttributes);
        virtual Result drawLayout();

        virtual Result addFrame(IUniversal *piDraw);
        virtual Result deleteFrame(IUniversal *piDraw);
#ifdef _DEBUG
        virtual void openImGuiDemo(Boolean open)
        {
        }
        virtual void openImPlotDemo(Boolean open)
        {
        }
#endif  
        static Result createInstance(void **ppv)
        {
            UiLayoutImplSimple *p = new UiLayoutImplSimple();
            if (p)
            {
                *(ILayout **)ppv = p;
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
