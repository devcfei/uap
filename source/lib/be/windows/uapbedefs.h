#ifndef _UAPBE_DEFS_H_
#define _UAPBE_DEFS_H_

#if defined(_DEBUG)
#define TRACE(fmt, ...) TraceMessage(TEXT("uapbe.dll!") fmt, __VA_ARGS__)
#define ASSERT(_expr_)
#else
#define TRACE(fmt, ...)
#define ASSERT(_expr_)
#endif

#endif // _UAPBE_DEFS_H_
