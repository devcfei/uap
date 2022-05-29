#ifndef _FOOBAR_IMPL_H_
#define _FOOBAR_IMPL_H_


namespace uap
{


    class FooImpl : public IFoo
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release() ;
        virtual Result queryInterface(const Uuid &, void **) ;

        // IFoo
        virtual Result foo();



        static Result createInstance(IFoo **ppv)
        {
            FooImpl *p = new FooImpl();
            if (p)
            {
                *ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

        inline static int memcount = 0;
        void *operator new(size_t size)
        {
            memcount++;
            UAP_TRACE("FooImpl::new memcount = %d\n", memcount);

            return malloc(size);
        }

        void operator delete(void *p)
        {
            memcount--;
            UAP_TRACE("FooImpl::delete memcount = %d\n", memcount);
            free(p);
        }

    private:
        FooImpl()
            : refcount_(1)
        {
        }
        Ulong refcount_;
    }; // @class IFooBar



    class BarImpl : public IBar
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release() ;
        virtual Result queryInterface(const Uuid &, void **) ;

        // IBar
        virtual Result bar();
        virtual Result setFooBar(IFooBar* piFooBar);



        static Result createInstance(IBar **ppv)
        {
            BarImpl *p = new BarImpl();
            if (p)
            {
                *ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

        inline static int memcount = 0;
        void *operator new(size_t size)
        {
            memcount++;
            UAP_TRACE("BarImpl::new memcount = %d\n", memcount);

            return malloc(size);
        }

        void operator delete(void *p)
        {
            memcount--;
            UAP_TRACE("BarImpl::delete memcount = %d\n", memcount);
            free(p);
        }

    private:
        BarImpl()
            : refcount_(1)
        {
        }
        Ulong refcount_;

        sptr<IFooBar> spFooBar_;
    }; // @class IFooBar




    class FooBarImpl : public IFooBar
        , public IFoo
    {
    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release() ;
        virtual Result queryInterface(const Uuid &, void **) ;

        // IFooBar
        virtual Result foobar();
        virtual Result createInstance(const Uuid &, void **);

        // IFoo
        virtual Result foo();



        static Result createInstance(IFooBar **ppv)
        {
            FooBarImpl *p = new FooBarImpl();
            if (p)
            {
                *ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

        inline static int memcount = 0;
        void *operator new(size_t size)
        {
            memcount++;
            UAP_TRACE("FooBarImpl::new memcount = %d\n", memcount);

            return malloc(size);
        }

        void operator delete(void *p)
        {
            memcount--;
            UAP_TRACE("FooBarImpl::delete memcount = %d\n", memcount);
            free(p);
        }

    private:
        FooBarImpl()
            : refcount_(1)
        {
        }
        Ulong refcount_;
    }; // @class IFooBar

}

#endif //_FOOBAR_IMPL_H_