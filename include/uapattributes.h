#ifndef _UAP_ATTRIBUTES_H_
#define _UAP_ATTRIBUTES_H_


#ifndef _UAP_RESULT_H_
#error uapattributes.h requires uapresult.h to be included first
#endif

namespace uap
{

    class IAttributes : public IUnknown
    {
    public:
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface() = 0;

        //
        virtual Result setUint(Ulong key, Uint value) = 0;
        virtual Result getUint(Ulong key, Uint &value) = 0;
    }; // @class IAttributes

}; // @namespace uap


#endif // _UAP_ATTRIBUTES_H_