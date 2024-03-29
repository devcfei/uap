#ifndef _UAP_UI_WINDOW_IMPL_H_
#define _UAP_UI_WINDOW_IMPL_H_

namespace uap
{

    class WindowImpl : public IWindow
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &rUuid, void **ppv);

        // IFrame
        virtual Result drawFrame();

        // IWindow
        virtual Result initialize(const Char* title, IAttributes *pAttributes, IEvent* piEvent);
        virtual Result drawPrimitives();

        virtual Boolean isOpen() const
        {
            return open_;
        }
        virtual Boolean setOpen(Boolean open)
        {
            return open_ = open; // TODO: need atomic operation?
        }

        virtual Result setFrame(IFrame* pFrame)
        {
            spFrame_ = pFrame;
            return R_SUCCESS;
        }


        static Result createInstance(IWindow **ppv)
        {
            WindowImpl *p = new WindowImpl();
            if (p)
            {
                *ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        Ulong refcount_;

    protected:
        WindowImpl()
            : refcount_(1)
            , open_(false)
            , title_("Window")
            , evtIdWindowClose_(0)
            , pos_(ImVec2(100, 100))
            , size_(ImVec2(100, 100))
        {
        }
        WindowImpl(char *title)
            : refcount_(1)
            , open_(false)
            , title_(title)
            , evtIdWindowClose_(0)
            , pos_(ImVec2(100, 100))
            , size_(ImVec2(100, 100))
        {
        }

        WindowImpl(char *title, Boolean open)
            : refcount_(1)
            , open_(open)
            , title_(title)
            , evtIdWindowClose_(0)
            , pos_(ImVec2(100, 100))
            , size_(ImVec2(100, 100))
        {
        }

        Boolean open_;
        std::string title_;
        Uint evtIdWindowClose_;
        ImVec2 pos_;
        ImVec2 size_;

        sptr<IEvent> spEvent_;


        sptr<IFrame> spFrame_;

    }; // @class WindowImpl

} // @namespace uap

#endif // _UAP_UI_WINDOW_IMPL_H_
