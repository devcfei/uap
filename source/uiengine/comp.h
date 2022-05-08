#ifndef _COMP_H_
#define _COMP_H_


#include <uap.h>
#include <uapuiengine.h>


// Windows specical
#include <windows.h>
#include <tchar.h>

// WRL
#include <wrl\client.h>
using namespace Microsoft::WRL;

// Direct3D9

#include <d3d9.h>

//imgui
#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>

// UiEngine
#include "uiengineimpl.h"


#ifdef UAP_UIENGINE_EXPORTS
#define DLL_EXPORTS _declspec(dllexport)
#else
#define DLL_EXPORTS _declspec(dllimport)
#endif



#if defined (_DEBUG)
#define TRACE(fmt, ...) uap::logPrint("uiengine.dll!" fmt, __VA_ARGS__)
#define ASSERT(_expr_)
#else
#define TRACE(fmt, ...) 
#define ASSERT(_expr_)
#endif

namespace uap
{
    extern "C" DLL_EXPORTS Result compGetInterface(const Uuid &iid, void **ppv);
    extern "C" DLL_EXPORTS Result compRegisterInterface(const Uuid *iidArr, Ulong *count);

};




#endif // _COMP_H_
