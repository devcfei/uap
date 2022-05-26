#include "comp.h"


namespace uap
{

    Ulong UiTextureInspectorImpl::addRef()
    {
        Ulong ref = InterlockedIncrement(&refcount_);
        //UAP_TRACE("UiTextureInspectorImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong UiTextureInspectorImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        //UAP_TRACE("UiTextureInspectorImpl::release - refcount=%d\n", ref);
        if (!ref)
        {
            //UAP_TRACE("delete UiTextureInspectorImpl!!!!!\n");
            delete this;
        }
        return ref;
    }
    Result UiTextureInspectorImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_IUITEXTURE_INSPECTOR))
        {
            IUiTextureInspector *pi = static_cast<IUiTextureInspector *>(this);
            addRef();

            *((IUiTextureInspector **)ppv) = pi;
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


    // IUiTextureInspector

    Result UiTextureInspectorImpl::initialize(IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;
        return r;
    }

    Result UiTextureInspectorImpl::loadImage(Char *name)
    {
        Result r = R_SUCCESS;

        r = spUiEngineBackend_->createTexture(name,spTexture_.getaddrof());
        return r;
    }

    // IDraw
    Result UiTextureInspectorImpl::draw()
    {
        Result r = R_SUCCESS;


        static bool flipX = false;
        static bool flipY = false;

        ImGuiTexInspect::InspectorFlags flags = 0;
        if (flipX) 
            flags|= ImGuiTexInspect::InspectorFlags_FlipX;
        if (flipY)
            flags|= ImGuiTexInspect::InspectorFlags_FlipY;





        if(ImGui::Begin("Simple Texture Inspector"))
        {
            if (ImGuiTexInspect::BeginInspectorPanel("##ColorFilters", spTexture_->texture(),
                                                    ImVec2((float)spTexture_->width(), (float)spTexture_->height())))
            {
                
                
                ImGuiTexInspect::DrawAnnotations(ImGuiTexInspect::ValueText(ImGuiTexInspect::ValueText::BytesDec));

            }
            ImGuiTexInspect::EndInspectorPanel();

            // Now some ordinary ImGui elements to provide some explanation
            ImGui::BeginChild("Controls", ImVec2(600, 100));
            ImGui::TextWrapped("Basics:");
            ImGui::BulletText("Use mouse wheel to zoom in and out.  Click and drag to pan.");
            ImGui::BulletText("Use the demo select buttons at the top of the window to explore");
            ImGui::BulletText("Use the controls below to change basic color filtering options");
            ImGui::EndChild();


            /* DrawColorChannelSelector & DrawGridEditor are convenience functions that 
            * draw ImGui controls to manipulate config of the most recently drawn 
            * texture inspector
            **/
            ImGuiTexInspect::DrawColorChannelSelector();
            ImGui::SameLine(200);
            ImGuiTexInspect::DrawGridEditor();

            ImGui::Separator();

            ImGui::Checkbox("Flip X", &flipX);
            ImGui::Checkbox("Flip Y", &flipY);
        }


        ImGui::End();

        return r;
    }
}