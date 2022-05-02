#ifndef _UAP_UNKNOWN_H_
#define _UAP_UNKNOWN_H_


#ifndef _UAP_RESULT_H_
#error uapunknown.h requires uapresult.h to be included first
#endif


// #define UAP_DECLEAR_UNKNOWN_INTERFACE()
//     virtual Ulong addRef() = 0; \
//     virtual Ulong release() = 0; \
//     virtual Result queryInterface() = 0; 

namespace uap
{

    class IUnknown
    {
    public:
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface() = 0;
    };

}; // @namespace uap


#endif // _UAP_UNKNOWN_H_