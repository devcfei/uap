#ifndef _COMP_H_
#define _COMP_H_


// uap
#define MODULE_NAME "imageengine"
#include <uap.h>
#include <uapimageengine.h>
using namespace uap;

// Windows specical
#include <windows.h>




#include "imageengineimpl.h"


#ifdef UAP_IMAGEENGINE_EXPORTS
#define DLL_EXPORTS _declspec(dllexport)
#else
#define DLL_EXPORTS _declspec(dllimport)
#endif



namespace uap
{
    extern "C" DLL_EXPORTS Result compGetInterface(const Uuid &iid, void **ppv);
    extern "C" DLL_EXPORTS Result compRegisterInterface(const Uuid *iidArr, Ulong *count);

};




#endif // _COMP_H_
