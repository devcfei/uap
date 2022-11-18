#include "common.h"

namespace uap
{

    ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) noexcept
    {
        return { lhs.x + rhs.x, lhs.y + rhs.y };
    }


   void FileBrowserIcons::draw_none_icon(float width, float height) const noexcept
    {
        ImGui::Dummy({ width, height });
        ImGui::SameLine();
    }


    void FileBrowserIcons::draw_home_icon(float width, float height, uint32_t color) const noexcept
    {
        this->draw_none_icon(width, height);

        // min .....* p0       //
        //     .   / \         //
        //     .  /   \        //
        //  p3 . *     *   p1  //
        //     ./|p5   |\.     //
        //  p4 * | *-+ | * p2  //
        //       | | | | .     //
        //       *-+-*-*.. max //
        //     p6   p7 p8      //

        const auto item_size = ImVec2{width, height};

        const auto icon_min = ImGui::GetItemRectMin();
        const auto icon_max = icon_min + item_size;

        const auto p0 = ImVec2{icon_min.x + width * 0.5f, icon_min.y};

        const auto p1 = ImVec2{p0.x + width * 0.3f, p0.y + height * 0.3f};
        const auto p2 = ImVec2{icon_max.x, p1.y + height * 0.2f};

        const auto p3 = ImVec2{p0.x - width * 0.3f, p0.y + height * 0.3f};
        const auto p4 = ImVec2{icon_min.x, p3.y + height * 0.2f};

        const auto p5 = ImVec2{p0.x - width * 0.1f, p4.y + height * 0.1f};

        const auto p6 = ImVec2{p3.x, icon_max.y};
        const auto p7 = ImVec2{p0.x + width * 0.1f, icon_max.y};
        const auto p8 = ImVec2{p1.x, icon_max.y};

        const auto roof_points = {p4, p0, p2};
        const auto wall_points = {p3, p6, p8, p1};

        auto draw_list = ImGui::GetWindowDrawList();
        draw_list->AddPolyline(roof_points.begin(), roof_points.size(), color, false, 1.0f);
        draw_list->AddPolyline(wall_points.begin(), wall_points.size(), color, false, 1.0f);

        draw_list->AddRectFilled(p5, p7, color);
    }

    void FileBrowserIcons::draw_desktop_icon(float width, float height, uint32_t color) const noexcept
    {
        this->draw_none_icon(width, height);

        // min *-------------+     //
        //     |             |     //
        //     |             |     //
        //     |             |     //
        //     +-------------* p0  //
        //       p1   *      .     //
        //           / \  p3 .     //
        //       p2 *---*..... max //

        const auto item_size = ImVec2{width, height};

        const auto icon_min = ImGui::GetItemRectMin();
        const auto icon_max = icon_min + item_size;

        const auto p0 = ImVec2{icon_max.x, icon_min.y + height * 0.75f};

        const auto p1 = ImVec2{icon_min.x + width * 0.5f, p0.y};
        const auto p2 = ImVec2{p1.x - width * 0.2f, icon_max.y};
        const auto p3 = ImVec2{p1.x + width * 0.2f, icon_max.y};

        auto draw_list = ImGui::GetWindowDrawList();
        draw_list->AddRect(icon_min, p0, color, 2.0f);
        draw_list->AddTriangleFilled(p1, p2, p3, color);
    }

    void FileBrowserIcons::draw_recent_icon(float width, float height, uint32_t color) const noexcept
    {
        this->draw_none_icon(width, height);

        //   p1  *` ' `   p2   //
        //      ` \   * `      //
        //    `    \ /    `    //
        //   -      *      -   //
        //    `     p0    `    //
        //      `       `      //
        //        ` ' `        //

        const auto radius = width * 0.5f;
        const auto icon_min = ImGui::GetItemRectMin();

        const auto p0 = ImVec2{icon_min.x + radius, icon_min.y + radius};

        const auto p1 = ImVec2{p0.x - width * 0.2f, p0.y - radius * 0.65f};
        const auto p2 = ImVec2{p0.x + width * 0.3f, p0.y - radius * 0.15f};

        const auto points = {p1, p0, p2};

        auto draw_list = ImGui::GetWindowDrawList();
        draw_list->AddCircle(p0, radius, color);
        draw_list->AddPolyline(points.begin(), points.size(), color, false, 1.0f);
    }

    void FileBrowserIcons::draw_trash_icon(float width, float height, uint32_t color) const noexcept
    {
        const auto item_size = ImVec2{width, height};
        this->draw_none_icon(width, height);

        width *= 0.8f;
        const auto icon_size = ImVec2{width, item_size.y};

        // min ......*---+           //
        //     .  p0 |   |           //
        //  p1 *-----+---*-----* p3  //
        //              p2           //
        //          p6    p10        //
        //  p4 *    *     *    * p5  //
        //     |    |     |    |     //
        //     |    |     |    |     //
        //     |    *     *    |     //
        //     |    p7    p11  |     //
        // p12 *---------------* max //

        const auto icon_min = ImGui::GetItemRectMin() + ImVec2{(item_size.x - width) * 0.5f, 0.0f};
        const auto icon_max = icon_min + icon_size;

        const auto p0 = ImVec2{icon_min.x + icon_size.x * 0.3f, icon_min.y};

        const auto p1 = ImVec2{icon_min.x, icon_min.y + height * 0.15f};
        const auto p2 = ImVec2{icon_max.x - icon_size.x * 0.3f, p1.y};
        const auto p3 = ImVec2{icon_max.x, p1.y};

        const auto p4 = ImVec2{icon_min.x, p1.y + height * 0.2f};
        const auto p5 = ImVec2{icon_max.x, p4.y};

        const auto x_offset = icon_size.x * 0.3f;
        const auto y_offset = icon_size.y * 0.15f;

        const auto p6 = ImVec2{p4.x + x_offset, p4.y};
        const auto p7 = ImVec2{p6.x, icon_max.y - y_offset};

        const auto p8 = ImVec2{p6.x + x_offset, p6.y};
        const auto p9 = ImVec2{p8.x, p7.y};

        const auto p12 = ImVec2{icon_min.x, icon_max.y};

        const auto points = {p4, p12, icon_max, p5};

        auto draw_list = ImGui::GetWindowDrawList();
        draw_list->AddLine(p1, p3, color);
        draw_list->AddRect(p0, p2, color);

        draw_list->AddPolyline(points.begin(), points.size(), color, false, 1.0f);
        draw_list->AddLine(p6, p7, color);
        draw_list->AddLine(p8, p9, color);
    }

    void FileBrowserIcons::draw_image_file_icon(float width, float height, uint32_t color) const noexcept
    {
        const auto item_size = ImVec2{width, height};
        this->draw_none_icon(width, height);

        height *= 0.9f;
        const auto icon_size = ImVec2{item_size.x, height};

        // TODO(FiTH)
        // min *------------------+
        //     |                  |
        //     |                  |
        //     |                  |
        //     |                  |
        //     |                  |
        //     +------------------* max

        const auto icon_min = ImGui::GetItemRectMin() + ImVec2{0.0f, (item_size.y - height) * 0.5f};
        const auto icon_max = icon_min + icon_size;

        const auto border_thickness = max(width * 0.05f, 2.0f);

        const auto r1 = ImVec2{icon_min + ImVec2{width * 0.5f, height * 0.2f}};
        const auto r2 = r1 + ImVec2{width * 0.35f, height * 0.45f};

        const auto c = icon_min + ImVec2{width * 0.35f, height * 0.5f};
        const auto radius = width * 0.25f;

        const auto t1 = ImVec2{icon_min + ImVec2{width * 0.25f, height * 0.85f}};
        const auto t2 = t1 + ImVec2{width * 0.3f, height * -0.4f};
        const auto t3 = ImVec2{t2.x + width * 0.3f, t1.y};

        const auto red_color = 0xFF4444AAu;
        const auto green_color = 0xFF44AA44u;
        const auto blue_color = 0xFFFF6060u;

        auto draw_list = ImGui::GetWindowDrawList();
        draw_list->AddRect(icon_min, icon_max, color, 0.0f, ImDrawCornerFlags_None, border_thickness);

        draw_list->AddRectFilled(r1, r2, green_color);
        draw_list->AddCircleFilled(c, radius, red_color);
        draw_list->AddTriangleFilled(t1, t2, t3, blue_color);
    }

    void FileBrowserIcons::draw_dir_icon(float width, float height, uint32_t color) const noexcept
    {
        const auto item_size = ImVec2{width, height};
        this->draw_none_icon(width, height);

        height *= 0.9f;
        const auto icon_size = ImVec2{item_size.x, height};

        //          min *------* p0
        //              |       \        p2
        //              |        *-------*
        //              |        p1      |
        //              |                |
        //              |                |
        // min.x, max.y *----------------* max

        const auto icon_min = ImGui::GetItemRectMin() + ImVec2{0.0f, (item_size.y - height) * 0.5f};
        const auto icon_max = icon_min + icon_size;

        const auto p0 = ImVec2{icon_min.x + width * 0.4f, icon_min.y};
        const auto p1 = ImVec2{p0.x + width * 0.15f, icon_min.y + height * 0.25f};
        const auto p2 = ImVec2{icon_max.x, p1.y};

        const auto points = {
            icon_min,
            p0,
            p1,
            p2,
            icon_max,
            {icon_min.x, icon_max.y}};

        auto draw_list = ImGui::GetWindowDrawList();
        draw_list->AddPolyline(points.begin(), points.size(), color, true, 1.0f);
    }

    void FileBrowserIcons::draw_file_icon(float width, float height, uint32_t color) const noexcept
    {
        const auto item_size = ImVec2{width, height};
        this->draw_none_icon(width, height);

        width *= 0.7f;
        const auto icon_size = ImVec2{width, item_size.y};
        const auto triangle_size = ImVec2{icon_size.x * 0.4f, icon_size.x * 0.4f};

        //          min *----------*.... p2
        //              |          |\...
        //              |          | \..
        //              |          |  \.
        //              |       p0 *---* p1
        //              |              |
        //              |              |
        //              |              |
        //              |              |
        // min.x, max.y *--------------* max

        const auto icon_min = ImGui::GetItemRectMin() + ImVec2{(item_size.x - width) * 0.5f, 0.0f};
        const auto icon_max = icon_min + icon_size;

        const auto p0 = ImVec2{icon_max.x - triangle_size.x, icon_min.y + triangle_size.y};
        const auto p1 = ImVec2{p0.x + triangle_size.x, p0.y};
        const auto p2 = ImVec2{p0.x, p0.y - triangle_size.y};

        auto draw_list = ImGui::GetWindowDrawList();
        draw_list->AddTriangleFilled(p0, p1, p2, color);

        const auto points = {
            p2,
            icon_min,
            {icon_min.x, icon_max.y},
            icon_max,
            p1};

        draw_list->AddPolyline(points.begin(), points.size(), color, false, 1.0f);
    }

    FileBrowserIcons::ButtonState FileBrowserIcons::draw_wide_button(bool selected,
                                                               uint32_t hovered_color, uint32_t active_color) const noexcept
    {
        const auto &style = ImGui::GetStyle();
        auto cursor_pos = ImGui::GetCursorPos();
        ImGui::Dummy({ImGui::GetContentRegionMax().x, ImGui::GetTextLineHeight() + style.FramePadding.y * 2.0f});

        const auto item_min = ImGui::GetItemRectMin();
        const auto item_max = ImGui::GetItemRectMax();

        cursor_pos.y += style.FramePadding.y;
        ImGui::SetCursorPos(cursor_pos);

        auto draw_list = ImGui::GetWindowDrawList();

        if (ImGui::IsItemHovered())
        {
            if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
            {
                draw_list->AddRectFilled(item_min, item_max, active_color);
                return ButtonState::CLICKED;
            }

            draw_list->AddRectFilled(item_min, item_max, hovered_color);
            return ButtonState::HOVERED;
        }

        if (selected)
            draw_list->AddRectFilled(item_min, item_max, active_color);

        return ButtonState::NONE;
    }




    Ulong FileBrowserWindowImpl::addRef()
    {
        Ulong ref = InterlockedIncrement(&refcount_);
        // UAP_TRACE("FileBrowserWindowImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong FileBrowserWindowImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        // UAP_TRACE("FileBrowserWindowImpl::release - refcount=%d\n", ref);
        if (!ref)
        {
            UAP_TRACE("FileBrowserWindowImpl delete!!!!\n");
            delete this;
        }
        return ref;
    }
    Result FileBrowserWindowImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_IFILEBROWSERWINDOW))
        {
            IFileBrowserWindow *pi = static_cast<IFileBrowserWindow *>(this);
            addRef();

            *((IFileBrowserWindow **)ppv) = pi;
            r = R_SUCCESS;
        }
        else if (uapUuidIsEqual(rUuid, IID_IWINDOW))
        {
            IWindow *pi = static_cast<IWindow *>(this);
            addRef();

            *((IWindow **)ppv) = pi;
            r = R_SUCCESS;
        }
        else if (uapUuidIsEqual(rUuid, IID_IFRAME))
        {
            IFrame *pi = static_cast<IFrame *>(this);
            addRef();

            *((IFrame **)ppv) = pi;
            r = R_SUCCESS;
        }
        return r;
    }

    // IWindow
    Result FileBrowserWindowImpl::initialize(const Char* title, IAttributes* pAttributes, IEvent* piEvent)
    {
        Result r;

        r = WindowImpl::initialize(title, pAttributes,piEvent );
        if(!UAP_SUCCESS(r))
        {
            return r;
        }

        if(pAttributes)
        {

            r = pAttributes->getUint(FILEBROWSERWINDOW_ATTRBUTE_FILECLICKED_EVENT_ID, evtIdFileClicked_);
            if(!UAP_SUCCESS(r))
            {
                r = R_SUCCESS; // ignore error for WINDOW_CLOSE_EVENTID not set
            }
        }

        return r;

    }


    Result FileBrowserWindowImpl::drawPrimitives()
    {
        Result r = R_SUCCESS;

        for(auto it:vecPath_)
        {
            USES_CONVERSION;
            std::string folderPath = T2A(it.c_str());
            if (ImGui::TreeNodeEx(folderPath.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
            {   
                drawFiles(it.c_str());
                ImGui::TreePop();
            }
        }  
        return r;
    }

    // IFileBrowserWindow
    Result FileBrowserWindowImpl::addPath(Char *name)
    {
        Result r = R_SUCCESS;
        USES_CONVERSION;

        vecPath_.push_back(A2T(name));
    
        return r;
        
    }


    void FileBrowserWindowImpl::drawFiles(std::tstring path)
    {

        const auto icon_color = 0xFF999999;
        const auto icon_size = ImGui::GetTextLineHeight();


        auto& style = ImGui::GetStyle();
        const auto btn_hovered_color = ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_FrameBgHovered]);
        const auto btn_active_color = ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_FrameBgActive]);


        HANDLE hFind = INVALID_HANDLE_VALUE;
        WIN32_FIND_DATA ffd;


        std::tstring pathenum = path;
        pathenum+=_T("\\*");

        hFind = FindFirstFile(pathenum.c_str(), &ffd);

        if (INVALID_HANDLE_VALUE == hFind)
        {
            return;
        }

        // List all the files in the directory with some info about them.
        do
        {
            if( 0==lstrcmp(ffd.cFileName, _T(".")) || 0==lstrcmp(ffd.cFileName, _T("..")) )
            {
                // filter the . and .. 
                continue;
            }

            bool isDir;
            bool isNormal;

            isDir = (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
            isNormal = (ffd.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE);

            USES_CONVERSION;
            std::string filename = T2A(ffd.cFileName);

            if(isDir)
            {
                //draw_dir_icon(icon_size, icon_size, icon_color);
                //ImGui::SameLine();


                if (ImGui::TreeNodeEx(filename.c_str()))
                {
                    std::tstring sub = path;
                    sub+=_T("\\");
                    sub+=ffd.cFileName;
                    drawFiles(sub.c_str()); // here is a recursive call
                    ImGui::TreePop();
                }
            }
            else if(isNormal)
            {
                //draw_file_icon(icon_size, icon_size, icon_color);
                //ImGui::SameLine();

                ImGui::TreeNodeEx(filename.c_str(), ImGuiTreeNodeFlags_Leaf|ImGuiTreeNodeFlags_NoTreePushOnOpen);

                if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                {
                    std::tstring file;
                    file = path;
                    file+=_T("\\");
                    file+=ffd.cFileName;

                    USES_CONVERSION;
                    UAP_TRACE("file clicked: %s\n",T2A(file.c_str()));


                    strFileLastClicked_ = file;


                    spEvent_->postEvent(evtIdFileClicked_, (EventArg)strFileLastClicked_.c_str(), 0);
                    
                }
            }

        } while (FindNextFile(hFind, &ffd) != 0);

        FindClose(hFind);
    }
}
