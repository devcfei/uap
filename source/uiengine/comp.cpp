#include "comp.h"


namespace uap
{

    // globals

    static const Uuid iidGlobal[]=
    {
        IID_UIENGINE,
    };


    // component funcitons
    uap::Result compGetInterface(const uap::Uuid& iid, void** ppv)
    {

        Result r = R_NO_SUCH_INTERFACE;

        TRACE("compGetInterface\n");


        IUiEngine* pi;

        if(UidIsEqual(iid, IID_UIENGINE))
        {
            pi = new UiEngineImpl();
            if(pi)
            {
                *ppv = pi;
                r = R_OK;
            }
            else        
            {
                r = R_NO_MEMORY;
            }
        }
        
        return r;
    }



    uap::Result compRegisterInterface(const uap::Uuid *iidArr, uap::Ulong* count)
    {
        Result r = R_OK;

        TRACE("compRegisterInterface\n");


        if(iidArr ==nullptr || count ==nullptr)
        {

            *count = sizeof(iidGlobal)/sizeof(iidGlobal[0]);
            r = R_INVALID_PARAMETERS;
            return r;
        }

        if(*count<sizeof(iidGlobal)/sizeof(iidGlobal[0]))
        {
            r = R_BUFFER_TOO_SMALL;
            return r;
        }

    
        CopyMemory((void*)iidArr,iidGlobal,sizeof(iidGlobal));

        return r;        
    }


};