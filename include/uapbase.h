#ifndef _UAP_BASE_H_
#define _UAP_BASE_H_

namespace uap
{

// Global basic data type
typedef char Char;
typedef short Short;
typedef int Int;
typedef long Long;
typedef long long LongLong;

typedef unsigned char Uchar;
typedef unsigned short Ushort;
typedef unsigned int Uint;
typedef unsigned long Ulong;
typedef unsigned long long UlongLong;





typedef struct 
{
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];
}Uuid;

inline int UidIsEqual(const Uuid &uid1, const Uuid &uid2)
{
    return (
        ((unsigned long *)&uid1)[0] == ((unsigned long *)&uid2)[0] &&
        ((unsigned long *)&uid1)[1] == ((unsigned long *)&uid2)[1] &&
        ((unsigned long *)&uid1)[2] == ((unsigned long *)&uid2)[2] &&
        ((unsigned long *)&uid1)[3] == ((unsigned long *)&uid2)[3]);
}





// Global functions

};

#endif //_UAP_BASE_H_