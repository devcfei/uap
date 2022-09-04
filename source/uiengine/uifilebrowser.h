#ifndef _UAP_UIFILEBROWSER_H_
#define _UAP_UIFILEBROWSER_H_



namespace uap
{

    class UiFileBrowser:  public IUiFileBrowser,
            public IDraw
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &rUuid, void **ppv);


        // IDraw
        virtual Result draw();

        // IUiFileBrowser

        virtual Result initialize(char* path);



        static Result createInstance(IUiFileBrowser **ppi)
        {
            UiFileBrowser *p = new UiFileBrowser();
            if (p)
            {
                *ppi = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }


    private:
        UiFileBrowser()
            : refcount_(1)
        {
        }
        Ulong refcount_;


        //
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


	    uint32_t m_selected_item_id = 0xffffffff;

	    void unselect_item() noexcept;

        std::string m_current_dir;

    }; // @class UiTextureImpl

} // @namespace uap

#endif // _UAP_UIFILEBROWSER_H_