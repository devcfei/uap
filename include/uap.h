#ifndef _UAP_H_
#define _UAP_H_

#include <uapbase.h>
#include <uapresult.h>
#include <uapdefs.h>
#include <uapuuid.h>
#include <uaplog.h>

// Component
#include <uapunknown.h>
#include <uapattributes.h>


namespace uap
{

    // Global functions
    Result uapInitialize();

    Result uapGetInterface(const Uuid &uuid, IUnknown **ppiUnknown);


    // Component functions
    typedef Result (*PFN_compRegisterInterface)(const Uuid *iidArr, Ulong* count);
    typedef Result (*PFN_compGetInterface)(const Uuid& iid, void** ppv);

};


// // Component functions
// typedef uap::Result (*PFN_compRegisterInterface)(const uap::Uuid *iidArr, uap::Ulong* count);
// typedef uap::Result (*PFN_compGetInterface)(const uap::Uuid& iid, void** ppv);

#endif //_UAP_H_
