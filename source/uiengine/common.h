#ifndef _COMP_H_
#define _COMP_H_


// uap
#define MODULE_NAME "uiengine"
#include <uap.h>
#include <uapcomponent.h>
#include <uapuiengine.h>

// STL

#include <vector>

// Windows specical
#include <windows.h>
#include <strsafe.h>
#include <tchar.h>
#include <shlobj.h>

// WRL
#include <wrl\client.h>
using namespace Microsoft::WRL;

// Direct3D9

#include <d3d9.h>
#include <d3d11.h>



#define FONT_SIZE 18.0f
#define TOOLBAR_HEIGHT 32.0f

#define IMGUI_ENABLE_FREETYPE
//imgui
#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

// imgui_tex_inspect
#include <tex_inspect_directx11.h> //TEX_INSPECT_CHANGE
#include <imgui_tex_inspect.h> //TEX_INSPECT_CHANGE
#include <imgui_tex_inspect_demo.h> //TEX_INSPECT_CHANGE


// implot
#include <implot.h>


// UiEngine implementation
#include "uimenubarimpl.h"
#include "uitoolbarimpl.h"
#include "uistatusbarimpl.h"
#include "uilogwindowimpl.h"
#include "uiimagewindowimpl.h"
#include "uitextureinspectorimpl.h"
#include "uilayoutimplsimple.h"
#include "uilayoutimpldocking.h"
#include "uilayoutimpldemo.h"
#include "uienginebackenddx9impl.h"
#include "uienginebackenddx11impl.h"
#include "uiengineimpl.h"
#include "uitextureimpl.h"
#include "uifilebrowser.h"






#define INFO(_message_, ...) \
        do{ \
            ILogTrace* p= UiEngineImpl::getLogTrace(); \
            if(p) \
                p->output(LT_INFO, _message_, __VA_ARGS__ ); \
        } while(0)


#define WARN(_message_, ...) \
        do{ \
            ILogTrace* p= UiEngineImpl::getLogTrace(); \
            if(p) \
                p->output(LT_WARN, _message_, __VA_ARGS__ ); \
        } while(0)



#define VERIFY(r, _message_) \
        do{ \
            ILogTrace* p= UiEngineImpl::getLogTrace(); \
            if(!UAP_SUCCESS(r)) \
            { \
                if(p) \
                    p->output(LT_ERROR, _message_ ## " failed! r = 0x%8.8x\n",r); \
                return r; \
            } \
            else \
            { \
                if(p) \
                    p->output(LT_INFO, _message_ ## " success! r = 0x%8.8x\n",r); \
            } \
        }while(0)



#endif // _COMP_H_
