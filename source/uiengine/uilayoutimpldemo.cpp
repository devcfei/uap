#include "common.h"

namespace uap
{

    Ulong UiLayoutImplDemo::addRef()
    {
        return InterlockedIncrement(&refcount_);
    }
    Ulong UiLayoutImplDemo::release()
    {
        Ulong ref = InterlockedDecrement(&refcount_);
        if (!ref)
        {
            UAP_TRACE("UiLayoutImplDemo delete!!!!\n");
            delete this;
        }
        return ref;
    }
    Result UiLayoutImplDemo::queryInterface(const Uuid &rUuid, void **ppv)
    {
        Result r = R_NO_SUCH_INTERFACE;
        if (uapUuidIsEqual(rUuid, IID_ILAYOUT))
        {
            UiLayoutImplDemo *pi = static_cast<UiLayoutImplDemo *>(this);
            addRef();

            *((UiLayoutImplDemo **)ppv) = pi;
            r = R_SUCCESS;
        }
        return r;
    }

    Result UiLayoutImplDemo::initializeLayout(IAttributes *piAttributes)
    {
        Result r = R_SUCCESS;

        INFO("UiLayoutImplDemo::initializeLayout\n");
        return r;
    }

    Result UiLayoutImplDemo::drawLayout()
    {
        Result r = R_SUCCESS;
        bool showImGuiDemo_ = true;
        bool show_another_window = false;

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (showImGuiDemo_)
            ImGui::ShowDemoWindow(&showImGuiDemo_);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &showImGuiDemo_); // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
            //ImGui::ColorEdit3("clear color", (float *)&colorClear_); // Edit 3 floats representing a color

            if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        return r;
    }


    Result UiLayoutImplDemo::addFrame(IUniversal *piDraw)
    {
        return R_SUCCESS;
    }

    Result UiLayoutImplDemo::deleteFrame(IUniversal *piDraw)
    {
        return R_SUCCESS;
    }

} // @namespace uap