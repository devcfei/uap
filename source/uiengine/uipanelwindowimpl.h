#ifndef _UAP_UIPANELWINDOW_H_
#define _UAP_UIPANELWINDOW_H_

namespace uap
{

    class UiPanelWindowImpl : public IPanelWindow
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &rUuid, void **ppv);

        // IDraw
        virtual Result draw();

        // IPanelWindow
        virtual Result initialize(IAttributes *pAttributes);
        virtual Result drawPrimitives();
        virtual Boolean isOpen() const;
        virtual Boolean setOpen(Boolean open);

        static Result createInstance(IPanelWindow **ppv)
        {
            UiPanelWindowImpl *p = new UiPanelWindowImpl();
            if (p)
            {
                *ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        UiPanelWindowImpl()
            : refcount_(1), open_(true), title_("Panel"), pos_(ImVec2(100, 100)), size_(ImVec2(100, 100))
        {
        }
        Ulong refcount_;

    protected:
        Boolean open_;
        std::string title_;
        ImVec2 pos_;
        ImVec2 size_;

    }; // @class UiPanelWindowImpl

} // @namespace uap

#endif // _UAP_UIPANELWINDOW_H_
