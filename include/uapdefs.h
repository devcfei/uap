#ifndef _UAP_DEFS_H_
#define _UAP_DEFS_H_

#if defined(_MSC_VER)

//
// DEFINE an UID(Unified ID, compatible to GUID, UUID)
// __declspec(selectany) helps to avoid multiple defination
// 
#define DEFINE_UUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    extern "C" const uap::Uuid  __declspec(selectany) name \
    = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }


#elif defined(__linux__)


#endif


#endif // _UAP_DEFS_H_