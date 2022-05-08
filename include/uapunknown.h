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
        virtual const Uuid& uuidof() = 0;
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid& uuid, void** ppv) = 0;
    };


    // Smart pointer
    template <typename T>
    class sptr
    {
    public:
        sptr() throw() : ptr_(nullptr)
        {
        }

        sptr(T *lp)
        {
            ptr_ = lp;
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

        template <typename U>
        Result as(sptr<U> *lp) const throw()
        {
            return ptr_->queryInterface(lp->uuidof(), reinterpret_cast<void **>(lp->releasegetaddrof()));
        }

        T **releasegetaddrof() throw()
        {
            releasep();
            return &ptr_;
        }

        // copy constructors

        sptr &operator=(T *other) throw()
        {
            if (ptr_ != other)
            {
                sptr(other).Swap(*this);
            }
            return *this;
        }

        void Swap(sptr &&r) throw()
        {
            T *tmp = ptr_;
            ptr_ = r.ptr_;
            r.ptr_ = tmp;
        }

        void Swap(sptr &r) throw()
        {
            T *tmp = ptr_;
            ptr_ = r.ptr_;
            r.ptr_ = tmp;
        }

    protected:
        unsigned long releasep() throw()
        {
            unsigned long ref = 0;
            T* temp = ptr_;

            if (temp != nullptr)
            {
                ptr_ = nullptr;
                ref = temp->release();
            }

            return ref;
        }
        T *ptr_;
    };


}; // @namespace uap


#endif // _UAP_UNKNOWN_H_