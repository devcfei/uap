#include "framework.h"

Result FileListManager::addFile(std::tstring filename)
{
    Result r = R_NOT_FOUND;

    bool bFound = false;
    // go through if file exist
    for (auto it: vecFileList_)
    {
        if(it == filename)
        {
            bFound = true;
        }
    }

    if(!bFound)
    {
        vecFileList_.push_back(filename);
        r = R_SUCCESS;
    }

    return r;
}


Result FileListManager::deleteFile(std::tstring filename)
{
    Result r = R_NOT_FOUND;

    for (std::list<std::tstring>::iterator it = vecFileList_.begin();
         it != vecFileList_.end();
         ++it)
    {
        if(*it == filename)
        {
            vecFileList_.erase(it);
            r = R_SUCCESS;
            break;
        }
    }
    return r;
}