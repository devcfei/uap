#ifndef _UAP_INTERNAL_H_
#define _UAP_INTERNAL_H_

namespace uap
{

    // Global functions

    typedef Result (*PFN_beInitialize)();
    typedef Result (*PFN_beCreateApplication)(IApplication **ppiApp);

    struct uapbePfn
    {
        PFN_beInitialize pfn_beInitialize;
        PFN_beCreateApplication pfn_beCreateApplication;
    };

    extern struct uapbePfn global_Pfn;


};


#endif //_UAP_INTERNAL_H_