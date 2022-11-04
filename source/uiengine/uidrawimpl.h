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
        virtual Result addText(Char *label, Boolean sameline)
        {
            Result r = R_SUCCESS;
            if (sameline)
                ImGui::SameLine();
            ImGui::TextUnformatted(label);
            return r;
        }

        virtual Result addButton(Char *label, Boolean sameline)
        {
            Result r = R_SUCCESS;
            if (sameline)
                ImGui::SameLine();
            ImGui::Button(label);
            return r;
        }

        virtual Result addCheckBox(Char *label, Boolean sameline, Boolean *value)
        {
            Result r = R_SUCCESS;
            if (sameline)
                ImGui::SameLine();
            ImGui::Checkbox(label, value);
            return r;
        }

        virtual Result addEdit(Char *label, Boolean sameline, Char *buf, Size_t buf_size)
        {
            Result r = R_SUCCESS;
            if (sameline)
                ImGui::SameLine();
            ImGui::InputText(label, buf, buf_size);
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
