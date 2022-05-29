#ifndef _UAP_FILESYSTEM_H_
#define _UAP_FILESYSTEM_H_

#ifndef _UAP_H_
#error uapfilesystem.h requires uap.h to be included first
#endif

namespace uap
{

    // {58bc7b94-dd98-4b96-a7f7-f96469262be4}
    DEFINE_UUID(IID_IFILE,
                0x58bc7b94, 0xdd98, 0x4b96, 0xa7, 0xf7, 0xf9, 0x64, 0x69, 0x26, 0x2b, 0xe4);

    class IFile : public IUniversal
    {
    public:
        // IUniversal
        virtual Ulong addRef() = 0;
        virtual Ulong release() = 0;
        virtual Result queryInterface(const Uuid &, void **) = 0;

        // IFile
        virtual Result initialize(IApplication *piApp) = 0;

        // uuid
        static const Uuid uuid()
        {
            return uuid_;
        }

    private:
        inline static const Uuid uuid_ = IID_IFILE;

    }; // @class IFile

} // @namespace uap

#endif // _UAP_FILESYSTEM_H_