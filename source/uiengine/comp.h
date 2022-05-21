#ifndef _COMP_H_
#define _COMP_H_


// uap
#define MODULE_NAME "uiengine"
#include <uap.h>
#include <uapuiengine.h>
using namespace uap;

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




// UiEngine implementation
#include "uiengineimpl.h"


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
            spLogTrace_->output(LT_VERBOSE, _message_, __VA_ARGS__ ); 

#define WARN(_message_, ...) \
            spLogTrace_->output(LT_WARN, _message_, __VA_ARGS__ ); 


namespace uap
{
    extern "C" DLL_EXPORTS Result compGetInterface(const Uuid &iid, void **ppv);
    extern "C" DLL_EXPORTS Result compRegisterInterface(const Uuid *iidArr, Ulong *count);

};




#endif // _COMP_H_
