#ifndef ZHIHE_Make_GUARD_H__
#define ZHIHE_Make_GUARD_H__

#include "./compiler.h"

#if ME_TARGET == ME_TARGET_WIN
#elif ME_TARGET == ME_TARGET_ANDROID

#elif ME_TARGET == ME_TARGET_APPLE_IOS

#else

#endif

#if ME_COMPILER == ME_COMPILER_GNU
#if ME_TARGET == ME_TARGET_APPLE_IOS
#define mem_size unsigned long
#else
#define mem_size size_t
#endif
#else
#define mem_size size_t
#endif

/// when define returns true it means that our architecture uses big endian
#define ME_HOST_IS_BIG_ENDIAN (bool)(*(unsigned short *)"\0\xff" < 0x100) 
#define ME_SWAP32(i)  ((i & 0x000000ff) << 24 | (i & 0x0000ff00) << 8 | (i & 0x00ff0000) >> 8 | (i & 0xff000000) >> 24)
#define ME_SWAP16(i)  ((i & 0x00ff) << 8 | (i &0xff00) >> 8)   
#define ME_SWAP_INT32_LITTLE_TO_HOST(i) ((ME_HOST_IS_BIG_ENDIAN)? ME_SWAP32(i) : (i) )
#define ME_SWAP_INT16_LITTLE_TO_HOST(i) ((ME_HOST_IS_BIG_ENDIAN)? ME_SWAP16(i) : (i) )
#define ME_SWAP_INT32_BIG_TO_HOST(i)    ((ME_HOST_IS_BIG_ENDIAN)? (i) : ME_SWAP32(i) )
#define ME_SWAP_INT16_BIG_TO_HOST(i)    ((ME_HOST_IS_BIG_ENDIAN)? (i):  ME_SWAP16(i) )

#endif // ZHIHE_Make_GUARD_H__
