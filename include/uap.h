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

};

#endif //_UAP_H_
