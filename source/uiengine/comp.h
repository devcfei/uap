#ifndef _COMP_H_
#define _COMP_H_


// uap
#define MODULE_NAME "uiengine"
#include <uap.h>
#include <uapuiengine.h>
using namespace uap;

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


#include "tahoma.h"


#define FONT_SIZE 17.0f
#define TOOLBAR_HEIGHT 32.0f

//#define IMGUI_ENABLE_FREETYPE
//imgui
#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

// imgui_tex_inspect
#include <tex_inspect_directx11.h> //TEX_INSPECT_CHANGE
#include <imgui_tex_inspect.h> //TEX_INSPECT_CHANGE
#include <imgui_tex_inspect_demo.h> //TEX_INSPECT_CHANGE


// UiEngine implementation
#include "uimenubarimpl.h"
#include "uitoolbarimpl.h"
#include "uistatusbarimpl.h"
#include "uiimagewindowimpl.h"
#include "uitextureinspectorimpl.h"
#include "uilayoutimplsimple.h"
#include "uilayoutimpldocking.h"
#include "uilayoutimpldemo.h"
#include "uienginebackenddx9impl.h"
#include "uienginebackenddx11impl.h"
#include "uiengineimpl.h"
#include "uitextureimpl.h"


#ifdef UAP_UIENGINE_EXPORTS
#define DLL_EXPORTS _declspec(dllexport)
#else
#define DLL_EXPORTS _declspec(dllimport)
#endif



#define RESULT_CHECK(r, _message_) \
        if(!UAP_SUCCESS(r)) \
        { \
            UAP_TRACE( _message_ ## " failed! r = 0x%8.8x\n",r); \
            return r; \
        } 

#define VERIFY(r, _message_) \
        if(!UAP_SUCCESS(r)) \
        { \
            spLogTrace_->output(LT_ERROR, _message_ ## " failed! r = 0x%8.8x\n",r); \
            return r; \
        } 

#define VERBOSE(_message_, ...) \
        do{ spLogTrace_->output(LT_VERBOSE, _message_, __VA_ARGS__ ); } while(0)


#define WARN(_message_, ...) \
            spLogTrace_->output(LT_WARN, _message_, __VA_ARGS__ ); 


namespace uap
{
    extern "C" DLL_EXPORTS Result compGetInterface(const Uuid &iid, void **ppv);
    extern "C" DLL_EXPORTS Result compRegisterInterface(const Uuid *iidArr, Ulong *count);

};




#endif // _COMP_H_
