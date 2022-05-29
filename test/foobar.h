#ifndef _FOOBAR_H_
#define _FOOBAR_H_

#include <uap.h>

namespace uap
{

    // {b9c5cea4-c552-4464-a33a-b8b49e2a3ff0}
    DEFINE_UUID(IID_IFOO,
                0xb9c5cea4, 0xc552, 0x4464, 0xa3, 0x3a, 0xb8, 0xb4, 0x9e, 0x2a, 0x3f, 0xf0);

    class IFoo : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IFoo
        virtual Result foo() = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IFOO;
    }; // @class IFoo



    // {06605a84-5ebb-428e-9c5a-85405d557565}
    DEFINE_UUID(IID_IFOOBAR,
                0x06605a84, 0x5ebb, 0x428e, 0x9c, 0x5a, 0x85, 0x40, 0x5d, 0x55, 0x75, 0x65);

    class IFooBar : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;


        // create instance
        virtual Result createInstance(const Uuid &, void **) = 0;

        // IFooBar
        virtual Result foobar()=0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IFOOBAR;
    }; // @class IFooBar



    // {42b58fca-6e66-403b-b3b4-1cd51a2a3fd1}
    DEFINE_UUID(IID_IBAR, 
                0x42b58fca, 0x6e66, 0x403b, 0xb3, 0xb4, 0x1c, 0xd5, 0x1a, 0x2a, 0x3f, 0xd1);

    class IBar : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &uuid, void **ppv) = 0;

        // IBar
        virtual Result bar() = 0;
        virtual Result setFooBar(IFooBar* piFooBar) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IBAR;
    };


}

#endif //_FOOBAR_H_