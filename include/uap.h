#ifndef _UAP_H_
#define _UAP_H_

#include <uaptypes.h>
#include <uapresult.h>
#include <uapdefs.h>


// Component
#include <uapunknown.h>
#include <uapattributes.h>
#include <uapapp.h>
#include <uaplogtrace.h>
#include <uaptoml.h>

namespace uap
{

    //{00000000-0000-0000-0000-000000000000}
    DEFINE_UUID(UUID_NULL,
                0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

    // Global functions
    Result uapInitialize();
    Result uapPrintMessage(Char* format, ...);
    const Char *uapGetResultString(Result r);
    const Char* uapGetUuidString(const Uuid &uuid);

    Result uapCreateApplication(IApplication **ppiApp);

    // Component functions
    typedef Result (*PFN_compRegisterInterface)(const Uuid *iidArr, Ulong *count);
    typedef Result (*PFN_compGetInterface)(const Uuid &iid, void **ppv);

} // @namespace uap

#endif //_UAP_H_
