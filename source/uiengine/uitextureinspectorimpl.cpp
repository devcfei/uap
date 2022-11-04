#include "common.h"

namespace uap
{

    Ulong TextureInspectorImpl::addRef()
    {
        Ulong ref = InterlockedIncrement(&refcount_);
        // UAP_TRACE("TextureInspectorImpl::addRef- refcount=%d\n", ref);
        return ref;
    }
    Ulong TextureInspectorImpl::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        // UAP_TRACE("TextureInspectorImpl::release - refcount=%d\n", ref);
        if (!ref)
        {
            // UAP_TRACE("delete TextureInspectorImpl!!!!!\n");
            delete this;
        }
        return ref;
    }
    Result TextureInspectorImpl::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;

        if (uapUuidIsEqual(rUuid, IID_ITEXTURE_INSPECTOR))
        {
            ITextureInspector *pi = static_cast<ITextureInspector *>(this);
            addRef();

            *((ITextureInspector **)ppv) = pi;
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
    Result TextureInspectorImpl::drawPrimitives()
    {
        Result r = R_SUCCESS;

        // set the dock
        ImGuiWindow* pWindow = ImGui::FindWindowByName("mainframe");
        ImGuiID dockspace_id = pWindow->GetID("MainFrame-Top");
        ImGui::SetWindowDock(ImGui::GetCurrentWindow(), dockspace_id, ImGuiCond_Once);

        
        // calculate the size
        ImVec2 vMin = ImGui::GetWindowContentRegionMin();
        ImVec2 vMax = ImGui::GetWindowContentRegionMax();
        ImVec2 sizeWindow = ImVec2(vMax.x - vMin.x, vMax.y - vMin.y);
        if (initCreate_)
        {
            sizeWindow = ImVec2((float)spTexture_->width(), (float)spTexture_->height());
            initCreate_ = false;
        }

        ImGuiTexInspect::InspectorFlags flags = ImGuiTexInspect::InspectorFlags_FillHorizontal;


        if (ImGuiTexInspect::BeginInspectorPanel("##ColorFilters", spTexture_->texture(),
                                                 ImVec2((float)spTexture_->width(), (float)spTexture_->height()),
                                                 flags,
                                                 ImGuiTexInspect::SizeIncludingBorder(sizeWindow)))
        {

            ImGuiTexInspect::DrawAnnotations(ImGuiTexInspect::ValueText(ImGuiTexInspect::ValueText::BytesDec));
        }
        ImGuiTexInspect::EndInspectorPanel();

        return r;
    }

    // ITextureInspector
    Result TextureInspectorImpl::loadImage(const Char *name)
    {
        Result r = R_SUCCESS;

        r = spUiEngineBackend_->createTexture(name, spTexture_.getaddrof());
        return r;
    }
}