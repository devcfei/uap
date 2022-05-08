#include "comp.h"


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }


    if(ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        uap::Result r = uap::uapInitialize();
        TRACE("dllmain process attach!\n");
    }

    return TRUE;
}

