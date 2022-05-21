#include "comp.h"


namespace uap
{

    // globals

    static const Uuid iidGlobal[]=
    {
        IID_UIENGINE,
    };


    // component funcitons
    Result compGetInterface(const Uuid& iid, void** ppv)
    {

        Result r = R_NO_SUCH_INTERFACE;

        UAP_TRACE("compGetInterface\n");


        IUiEngine* pi;

        if(uapUuidIsEqual(iid, IID_UIENGINE))
        {
            pi = new UiEngineImpl();
            if(pi)
            {
                *ppv = pi;
                r = R_SUCCESS;
            }
            else        
            {
                r = R_NO_MEMORY;
            }
        }
        
        return r;
    }



    Result compRegisterInterface(const Uuid *iidArr, Ulong* count)
    {
        Result r = R_SUCCESS;

        UAP_TRACE("compRegisterInterface\n");


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