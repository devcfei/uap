#ifndef _UAP_UILAYOUTIMPL_DEMO_
#define _UAP_UILAYOUTIMPL_DEMO_

namespace uap
{



    class UiLayoutImplDemo: public IUiLayout
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &,void **);

        // IUiLayout
        virtual Result initializeLayout(IAttributes* piAttributes);
        virtual Result draw();

        virtual Result addDraw(IUniversal *piDraw);
        virtual Result deleteDraw(IUniversal *piDraw);

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
                *(IUiLayout **)ppv = p;
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
