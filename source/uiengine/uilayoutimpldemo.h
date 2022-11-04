#ifndef _UAP_UI_LAYOUTIMPL_DEMO_
#define _UAP_UI_LAYOUTIMPL_DEMO_

namespace uap
{



    class UiLayoutImplDemo: public ILayout
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
            UiLayoutImplDemo *p = new UiLayoutImplDemo();
            if (p)
            {
                *(ILayout **)ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        UiLayoutImplDemo()
            : refcount_(1)
        {
        }

        Ulong refcount_;
    }; // @class UiLayoutImplDemo




} // @namespace uap

#endif // _UAP_UILAYOUTIMPL_DEMO_
