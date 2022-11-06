#ifndef _GENERIC_FRAME_H_
#define _GENERIC_FRAME_H_

namespace uap
{
    class GenericFrameImpl : public IFrame
    {

    public:
        // IUniversal
        virtual Ulong addRef();
        virtual Ulong release();
        virtual Result queryInterface(const Uuid &rUuid, void **ppv);

        // IFrame
        virtual Result drawFrame();


        static Result createInstance(IFrame **ppv, IDraw* pDraw)
        {
            GenericFrameImpl *p = new GenericFrameImpl(pDraw);
            if (p)
            {
                *ppv = p;
                return R_SUCCESS;
            }
            return R_ERROR;
        }

    private:
        Ulong refcount_;

        GenericFrameImpl(IDraw* pDraw)
            : refcount_(1)
            , spDraw_(pDraw)
        {

        }


        sptr<IDraw> spDraw_;

        //std::tstring strPath_;


        char path_[MAX_PATH]={0};

    };

}

#endif