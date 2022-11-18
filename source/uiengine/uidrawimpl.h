#ifndef _UAP_UI_DRAWIMPL_H_
#define _UAP_UI_DRAWIMPL_H_

namespace uap
{
    class DrawImpl : public IDraw
    {
    public:
        // IUnversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &, void **);

        // IDraw
        virtual Result addText(const Char *label, Boolean sameline)
        {
            Result r = R_SUCCESS;
            if (sameline)
                ImGui::SameLine();
            ImGui::TextUnformatted(label);
            return r;
        }

        virtual Result addButton(const Char *label, Boolean sameline,std::function<void()> onclick)
        {
            Result r = R_SUCCESS;
            if (sameline)
                ImGui::SameLine();
            if(ImGui::Button(label))
            {
                if(onclick)
                    onclick();
            }
            return r;
        }

        virtual Result addCheckBox(const Char *label, Boolean sameline, Boolean *value)
        {
            Result r = R_SUCCESS;
            if (sameline)
                ImGui::SameLine();
            ImGui::Checkbox(label, value);
            return r;
        }

        virtual Result addEdit(const Char *label, Boolean sameline, Char *buf, Size_t buf_size)
        {
            Result r = R_SUCCESS;
            if (sameline)
                ImGui::SameLine();
            ImGui::InputText(label, buf, buf_size);
            return r;
        }


        virtual Result addTreeNode(const Char *label, bool Sub, std::function<void()> onclick)
        {
            Result r = R_SUCCESS;

            if(Sub)
            {
                if (ImGui::TreeNodeEx(label) )
                {
                    if(onclick)
                        onclick();

                    ImGui::TreePop();
                }
            }
            else
            {
                ImGui::TreeNodeEx(label, ImGuiTreeNodeFlags_Leaf|ImGuiTreeNodeFlags_NoTreePushOnOpen);

                if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                {
                    if(onclick)
                        onclick();
                }
            }

            return r;
        }  

        virtual Result addImage(ITexture *texture, bool sameline)
        {
            Result r = R_SUCCESS;

            ImGui::Image((void*)texture->texture(),ImVec2(texture->width(), texture->height() ));

            return r;

        }


        static Result createInstance(IDraw **ppv)
        {
            DrawImpl *p = new DrawImpl();
            if (p)
            {
                *ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        DrawImpl()
            : refcount_(1)
        {
        }
        Ulong refcount_;
    };

}

#endif //_UAP_UI_DRAWIMPL_H_
