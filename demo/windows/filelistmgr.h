#ifndef _FILELISTMGR_H_
#define _FILELISTMGR_H_

class FileListManager
{
public:
    Result addFile(std::tstring filename);
    Result deleteFile(std::tstring filename);

private:
    std::list<std::tstring> vecFileList_;
};


#endif // _FILELISTMGR_H_