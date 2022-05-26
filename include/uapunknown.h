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

    // {00000000-0000-0000-0000-000000000001}
    DEFINE_UUID(IID_IUNIVERSAL,
                0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01);

    class IUniversal
    {
    public:
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &uuid, void **ppv) = 0;
    };

    template <typename T>
    class sptr
    {
    public:
        sptr() throw() : ptr_(nullptr)
        {
        }

        sptr(T *lp) : ptr_(lp)
        {
            if (ptr_ != nullptr)
                ptr_->addRef();
        }

        sptr(const sptr &r) : ptr_(r.ptr_)
        {
            if (ptr_ != nullptr)
                ptr_->addRef();
        }

        ~sptr() throw()
        {
            releasep();
        }

        T *operator->() const throw()
        {
            return ptr_;
        }

        T *get() const throw()
        {
            return ptr_;
        }

        T *const *getaddrof() const throw()
        {
            return &ptr_;
        }
        T** getaddrof() throw()
        {
            return &ptr_;
        }

        T **releasegetaddrof() throw()
        {
            releasep();
            return &ptr_;
        }

        // operator=
        // sptr& operator=(nullptr) throw()
        // {
        //     releasep();
        //     return *this;
        // }

        sptr &operator=(T *other) throw()
        {
            if (ptr_ != other)
            {
                sptr(other).swap(*this);
            }
            return *this;
        }

        template <typename U>
        sptr& operator=(U *other) throw()
        {
            sptr(other).swap(*this);
            return *this;
        }

        sptr &operator=(const sptr &other) throw()
        {
            if (ptr_ != other.ptr_)
            {
                sptr(other).swap(*this);
            }
            return *this;
        }

        template<class U>
        sptr& operator=(const sptr<U>& other) throw()
        {
            sptr(other).swap(*this);
            return *this;
        }

        sptr& operator=(sptr &&other) throw()
        {
            sptr(static_cast<sptr&&>(other)).swap(*this);
            return *this;
        }

        template<class U>
        sptr& operator=(sptr<U>&& other) throw()
        {
            sptr(static_cast<sptr<U>&&>(other)).swap(*this);
            return *this;
        }

        void swap(sptr &&r) throw()
        {
            T *tmp = ptr_;
            ptr_ = r.ptr_;
            r.ptr_ = tmp;
        }

        void swap(sptr &r) throw()
        {
            T *tmp = ptr_;
            ptr_ = r.ptr_;
            r.ptr_ = tmp;
        }

        template <typename U>
        Result as(sptr<U> *lp) const throw()
        {
            return ptr_->queryInterface(U::uuid(), reinterpret_cast<void **>(lp->releasegetaddrof()));
        }

    protected:
        unsigned long releasep() throw()
        {
            unsigned long ref = 0;
            T *temp = ptr_;

            if (temp != nullptr)
            {
                ptr_ = nullptr;
                ref = temp->release();
            }

            return ref;
        }
        T *ptr_;
    };

} // @namespace uap

#endif // _UAP_UNKNOWN_H_