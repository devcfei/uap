#include "common.h"

#include <algorithm>

namespace uap
{

    ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) noexcept
    {
        return { lhs.x + rhs.x, lhs.y + rhs.y };
    }


    Ulong UiFileBrowser::addRef()
    {
        return InterlockedIncrement(&refcount_);
    }
    Ulong UiFileBrowser::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            delete this;
        }
        return ref;
    }
    Result UiFileBrowser::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_IFILEBROSWER))
        {
            IUiFileBrowser *pi = static_cast<IUiFileBrowser *>(this);
            addRef();

            *((IUiFileBrowser **)ppv) = pi;
            r = R_SUCCESS;
        }
        else if (uapUuidIsEqual(rUuid, IID_IDRAW))
        {
            IDraw *pi = static_cast<IDraw *>(this);
            addRef();

            *((IDraw **)ppv) = pi;
            r = R_SUCCESS;
        }

        return r;
    }

    Result UiFileBrowser::initialize(char* path)
    {
        m_current_dir = path;

        return R_SUCCESS;
    }




    void UiFileBrowser::draw_none_icon(float width, float height) const noexcept
    {
        ImGui::Dummy({ width, height });
        ImGui::SameLine();
    }


    void UiFileBrowser::draw_home_icon(float width, float height, uint32_t color) const noexcept
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

    void UiFileBrowser::draw_desktop_icon(float width, float height, uint32_t color) const noexcept
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

    void UiFileBrowser::draw_recent_icon(float width, float height, uint32_t color) const noexcept
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

    void UiFileBrowser::draw_trash_icon(float width, float height, uint32_t color) const noexcept
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

    void UiFileBrowser::draw_image_file_icon(float width, float height, uint32_t color) const noexcept
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

    void UiFileBrowser::draw_dir_icon(float width, float height, uint32_t color) const noexcept
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

    void UiFileBrowser::draw_file_icon(float width, float height, uint32_t color) const noexcept
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

    UiFileBrowser::ButtonState UiFileBrowser::draw_wide_button(bool selected,
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




    void UiFileBrowser::show_nav_menu() noexcept
    {
        if (ImGui::ArrowButton("Back", ImGuiDir_Left)) {
            //m_current_dir = m_current_dir.parent_path();
            // TODO:
            unselect_item();
        }

        ImGui::SameLine();
        ImGui::TextUnformatted(m_current_dir.c_str());
    }



    void UiFileBrowser::show_side_menu() noexcept
    {
        const auto icon_color = 0xFF999999;
        const auto icon_size = ImGui::GetTextLineHeight();

        ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        if (ImGui::TreeNode("Bookmarks")) {
            this->draw_home_icon(icon_size, icon_size, icon_color);
            ImGui::Text("Home");

            this->draw_desktop_icon(icon_size, icon_size, icon_color);
            ImGui::Text("Desktop");

            this->draw_recent_icon(icon_size, icon_size, icon_color);
            ImGui::Text("Recent");

            this->draw_trash_icon(icon_size, icon_size, icon_color);
            ImGui::TextDisabled("Trash");

            ImGui::TreePop();
        }
    }


    void UiFileBrowser::unselect_item() noexcept
    {
        m_selected_item_id = -1;
    }




    void UiFileBrowser::show_item_context_menu() const noexcept
    {
        if (ImGui::MenuItem("Rename")) {
        }

        ImGui::Separator();
        this->show_general_context_menu();
    }


    void UiFileBrowser::show_general_context_menu() const noexcept
    {
        if (ImGui::BeginMenu("Create New ...")) {
            if (ImGui::MenuItem("Empty File")) {
            }
            if (ImGui::MenuItem("Directory")) {
            }

            ImGui::Separator();

            if (ImGui::MenuItem("C++ File")) {
            }
            if (ImGui::MenuItem("C++ Header File")) {
            }

            ImGui::EndMenu();
        }
    }


    void UiFileBrowser::show_dir_browser_list() noexcept
    {
        const auto icon_color = 0xFF999999;
        const auto icon_size = ImGui::GetTextLineHeight();

        auto& style = ImGui::GetStyle();
        const auto btn_hovered_color = ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_FrameBgHovered]);
        const auto btn_active_color = ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_FrameBgActive]);

        if (ImGui::BeginChild("Dir Browser", { 0.0f, -style.CellPadding.y })) {
            float cellPaddingY = style.CellPadding.y;
            style.CellPadding.y = 0.0f;

            if (ImGui::BeginTable("Dir Browser Table", 1, ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg)) {
                uint32_t id = 0;
                // auto dir_iter = std::filesystem::directory_iterator(m_current_dir);
                // for (auto& p: dir_iter) {
                //     ImGui::TableNextRow();

                //     const bool selected = (id == m_selected_item_id);
                //     const auto btn_state = this->draw_wide_button(selected, btn_hovered_color, btn_active_color);

                //     ImGui::PushID(p.path().filename().c_str());
                //     if (ImGui::BeginPopupContextItem("general context menu")) {
                //         if (selected) {
                //             this->show_item_context_menu();
                //         } else {
                //             this->unselect_item();
                //             this->show_general_context_menu();
                //         }

                //         ImGui::EndPopup();
                //     }

                //     if (btn_state == ButtonState::CLICKED) {
                //         if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
                //             if (p.is_directory()) {
                //                 m_current_dir = p.path();
                //                 this->unselect_item();
                //             }
                //         } else {
                //             m_selected_item_id = id;
                //         }
                //     }

                //     if (p.is_regular_file()) this->draw_file_icon(icon_size, icon_size, icon_color);
                //     else if (p.is_directory()) this->draw_dir_icon(icon_size, icon_size, icon_color);
                //     else this->draw_none_icon(icon_size, icon_size);

                //     ImGui::TextUnformatted(p.path().filename().c_str());
                //     if (ImGui::BeginPopupContextItem("item context menu")) {
                //         m_selected_item_id = id;

                //         this->show_item_context_menu();
                //         ImGui::EndPopup();
                //     }

                //     ImGui::PopID();
                //     ++id;
                // }

    
                
                CHAR szCurDir[MAX_PATH]="";

                StringCchCatA(szCurDir,MAX_PATH,m_current_dir.c_str());
                StringCchCatA(szCurDir, MAX_PATH, "*");

                HANDLE hFind = INVALID_HANDLE_VALUE;
                WIN32_FIND_DATAA ffd;

                hFind = FindFirstFileA(szCurDir, &ffd);

                if (INVALID_HANDLE_VALUE != hFind)
                {

                    // List all the files in the directory with some info about them.
                    do
                    {
                        ImGui::TableNextRow();

                        ImGui::TableSetColumnIndex(0);


                        bool isDir;
                        bool isNormal;


                        isDir =  (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
                        isNormal =  (ffd.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE);


                        const bool selected = (id == m_selected_item_id);
                        const auto btn_state = this->draw_wide_button(selected, btn_hovered_color, btn_active_color);

                        ImGui::PushID(ffd.cFileName);
                        if (ImGui::BeginPopupContextItem("general context menu")) {
                            if (selected) {
                                this->show_item_context_menu();
                            } else {
                                this->unselect_item();
                                this->show_general_context_menu();
                            }

                            ImGui::EndPopup();
                        }

                        if (btn_state == ButtonState::CLICKED) {
                            if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
                                if (isDir) {
                                    m_current_dir = ffd.cFileName;
                                    this->unselect_item();
                                }
                            } else {
                                m_selected_item_id = id;
                            }
                        }

                        if (isNormal) 
                            this->draw_file_icon(icon_size, icon_size, icon_color);
                        else if (isDir) 
                            this->draw_dir_icon(icon_size, icon_size, icon_color);
                        else 
                            this->draw_none_icon(icon_size, icon_size);


                        ImGui::SameLine();

                        ImGui::TextUnformatted(ffd.cFileName);
                        if (ImGui::BeginPopupContextItem("item context menu")) {
                            m_selected_item_id = id;

                            this->show_item_context_menu();
                            ImGui::EndPopup();
                        }

                        ImGui::PopID();
                        ++id;



                    } while (FindNextFileA(hFind, &ffd) != 0);

                    FindClose(hFind);
                }


                //
                ImGui::EndTable();
            }


		    style.CellPadding.y = cellPaddingY;


        }

        ImGui::EndChild();
    }

    // IDraw
    Result UiFileBrowser::draw()
    {
        Result r = R_SUCCESS;



	    ImGui::SetNextWindowSize({ 420.0f, 280.0f }, ImGuiCond_FirstUseEver);


        const auto icon_color = 0xFF999999;
        const auto icon_size = ImGui::GetTextLineHeight();
        auto &style = ImGui::GetStyle();
        const auto btn_hovered_color = ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_FrameBgHovered]);
        const auto btn_active_color = ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_FrameBgActive]);

        if(ImGui::Begin("ImGroot"))
        {

		    show_nav_menu();

            if (ImGui::BeginTable("ImGroot Main", 2, ImGuiTableFlags_Resizable))
            {

               // ImGui::TableSetupColumn(nullptr, 0);

                ImGui::TableNextRow();
                show_side_menu();

                ImGui::TableSetColumnIndex(1);
                show_dir_browser_list();

                ImGui::EndTable();
            }

            // draw_file_icon(icon_size, icon_size, icon_color);
            // draw_dir_icon(icon_size, icon_size, icon_color);
            // draw_home_icon(icon_size, icon_size, icon_color);
            // draw_desktop_icon(icon_size, icon_size, icon_color);
            // draw_recent_icon(icon_size, icon_size, icon_color);
            // draw_trash_icon(icon_size, icon_size, icon_color);
            // draw_image_file_icon(icon_size, icon_size, icon_color);


        }

        ImGui::End();

        return r;
    }

} // @namespace uap
