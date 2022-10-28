#ifndef _UAP_FILWBROWSERWINDOW_IMPL_H_
#define _UAP_FILWBROWSERWINDOW_IMPL_H_

namespace uap
{

    class FileBrowserIcons
    {
    public:
        void draw_none_icon(float width, float height) const noexcept;

        void draw_home_icon(float width, float height, uint32_t color) const noexcept;
        void draw_desktop_icon(float width, float height, uint32_t color) const noexcept;
        void draw_recent_icon(float width, float height, uint32_t color) const noexcept;
        void draw_trash_icon(float width, float height, uint32_t color) const noexcept;

        void draw_image_file_icon(float width, float height, uint32_t color) const noexcept;
        void draw_file_icon(float width, float height, uint32_t color) const noexcept;
        void draw_dir_icon(float width, float height, uint32_t color) const noexcept;


    	enum class ButtonState
        {
            NONE = 0,
            HOVERED,
            CLICKED
        };

        ButtonState draw_wide_button(bool selected, uint32_t hovered_color, uint32_t active_color) const noexcept;


        void show_item_context_menu() const noexcept;
        void show_general_context_menu() const noexcept;

        void show_nav_menu() noexcept;
        void show_side_menu() noexcept;
        void show_dir_browser_list() noexcept;

    };





    class FileBrowserWindowImpl : public IFileBrowserWindow, public WindowImpl, FileBrowserIcons
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &rUuid, void **ppv);


        // IWindow
        virtual Result initialize(IAttributes* pAttributes, IEvent* piEvent);
        virtual Result drawPrimitives();

        // IFileBrowserWindow
        virtual Result addPath(Char *name) ;

        static Result createInstance(IFileBrowserWindow **ppv)
        {
            FileBrowserWindowImpl *p = new FileBrowserWindowImpl();
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
        FileBrowserWindowImpl()
            : refcount_(1)
            , WindowImpl("File Browser")
        {

        }

        void drawFiles(std::tstring path);

        std::vector<std::tstring> vecPath_;

        std::tstring strFileLastClicked_;

        Uint evtIdFileClicked_;


    }; // @class FileBrowserWindowImpl

} // @namespace uap

#endif // _UAP_FILWBROWSERWINDOW_IMPL_H_
