#ifndef _UAP_DEFS_H_
#define _UAP_DEFS_H_



#ifndef _UAP_TYPES_H_
#error uapresult.h requires uaptypes.h to be included first
#endif

namespace uap
{


/// check if Result success
#define UAP_SUCCESS(_r_) (R_SUCCESS == (_r_))




/// UAP_TRACE macro
#if defined(_WIN32)

#if defined(_DEBUG)
#if defined(MODULE_NAME)
#define UAP_TRACE(fmt, ...) uapPrintMessage(MODULE_NAME "!" fmt, __VA_ARGS__)
#else
#define UAP_TRACE(fmt, ...) uapPrintMessage(fmt, __VA_ARGS__)
#endif
#else
#define UAP_TRACE(...)
#endif

#elif defined(__linux__)

//#define UAP_TRACE(fmt, args...) printf(fmt, ##args)
#define UAP_TRACE(fmt, args...) // TODO: not impl
#endif



/// UAP_ASSERT macro
#if defined(_WIN32)

#if defined (_DEBUG)
#define UAP_ASSERT(_expr_) _ASSERT(_expr_)
#else
#define UAP_ASSERT(_expr_)
#endif

#elif defined(__linux__)

#define UAP_ASSERT(_expr_) // TODO: not impl

#endif


/// macro to define the Uuid
#if defined(_WIN32)
//
// DEFINE an UUID(Unified ID, compatible to GUID, UUID)
// __declspec(selectany) helps to avoid multiple defination
// 
#define DEFINE_UUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    extern "C" const Uuid  __declspec(selectany) name \
    = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }


#elif defined(__linux__)

#define DEFINE_UUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    extern "C" inline const Uuid name \
    = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

#endif






} // @namespace uap

#endif // _UAP_DEFS_H_