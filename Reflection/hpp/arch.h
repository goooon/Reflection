#ifndef ZHIHE_Arch_GUARD_H__
#define ZHIHE_Arch_GUARD_H__

#define xStaticAssert(expr,msg) static_assert(expr,#msg)

#define ME_TARGET_WIN     1
#define ME_TARGET_LINUX     2
#define ME_TARGET_APPLE     3
#define ME_TARGET_APPLE_IOS 5
#define ME_TARGET_ANDROID   6

#ifndef ME_TARGET
#if defined (WIN)
# define ME_TARGET ME_TARGET_WIN
#elif defined(__APPLE__)
# if __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= 30000 || __IPHONE_OS_VERSION_MIN_REQUIRED >= 30000
#   define ME_TARGET ME_TARGET_APPLE_IOS
# else
#	define ME_TARGET ME_TARGET_APPLE_IOS
# endif
#elif defined(__ANDROID__)
# define ME_TARGET ME_TARGET_ANDROID
#else
# define ME_TARGET ME_TARGET_LINUX
#endif
#endif

#define ME_ARCH_32 0
#define ME_ARCH_64 1

#if defined(__x86_64__)     || defined(_M_X64)      || \
    defined(__powerpc64__)  || defined(__alpha__)   || \
    defined(__ia64__)       || defined(__s390__)    || \
    defined(__s390x__)
# define ME_ARCH ME_ARCH_64
xStaticAssert(sizeof(void *) == 8, VOID_IS_8);
#else
#define ME_ARCH ME_ARCH_32
xStaticAssert(sizeof(void *) == 4, VOID_IS_4);
#endif

#define BC_ENDIAN_UNKNOWN   0
#define ME_ENDIAN_LITTLE    1
#define ME_ENDIAN_BIG       2

//https://sourceforge.net/p/predef/wiki/Architectures/
//https://msdn.microsoft.com/en-us/library/b0084kay.aspx
#if defined(__sgi)      ||  defined (__sparc)        || \
    defined (__sparc__) ||  defined (__PPC__)        || \
    defined (__ppc__)   ||  defined (__BIG_ENDIAN__)
#elif defined(__arm__)  ||  defined(__i386) || \
      defined(__i386__) || defined(__ia64__)  || \
	  defined(_M_IX86 )
#define ME_ENDIAN ME_ENDIAN_LITTLE
#else
#define ME_ENDIAN ME_ENDIAN_UNKNOWN
#endif

#if ME_ENDIAN == ME_ENDIAN_BIG
#define  ME_PACK_ARRAY4(b) ((int)(b[0])<<24 | (int)(b[1])<<16 | (b[2])<<8 | (b[3]) )
# define ME_PACK_ARRAY2(b)   ( (b[0])<<8 | (b[1]) )
# define ME_PACK_BYTE4(b0,b1,b2,b3) ( (int)(b0)<<24 | (int)(b1)<<16 | (b2)<<8 | (b3) )
# define ME_PACK_BYTE2(b0,b1)   ( (b0)<<8 | (b1) )
#elif ME_ENDIAN == ME_ENDIAN_LITTLE
#define  ME_PACK_ARRAY4(b) ( (int)(b[3])<<24 | (int)(b[2])<<16 | (b[]1)<<8 | (b[0]) )
# define ME_PACK_ARRAY2(b)    ( (b[1])<<8 | (b[0]) )
# define ME_PACK_BYTE4(b0,b1,b2,b3) ( (int)(b3)<<24 | (int)(b2)<<16 | (b1)<<8 | (b0) )
# define ME_PACK_BYTE2(b0, b1)    ( (b1)<<8 | (b0) )
#else
#define  ME_PACK_ARRAY4(b)  ((bool)(*(unsigned short *)"\0\xff" < 0x100) ? ((int)(b[0])<<24 | (int)(b[1])<<16 | (b[2])<<8 |(b[3] ) : ( (int)(b[3])<<24 | (int)(b[2])<<16 | (b[]1)<<8 | (b[0]) ))
# define ME_PACK_ARRAY2(b)  ((bool)(*(unsigned short *)"\0\xff" < 0x100) ? ((b[0])<<8 | (b[1]) ) : ( (b[1])<<8 | (b[0]) ))
# define ME_PACK_BYTE4(b0,b1,b2,b3) ((bool)(*(unsigned short *)"\0\xff" < 0x100) ? ( (int)(b0)<<24 | (int)(b1)<<16 | (b2)<<8 | (b3) ) : ( (int)(b3)<<24 | (int)(b2)<<16 | (b1)<<8 | (b0) ))
# define ME_PACK_BYTE2(b0, b1)    ((bool)(*(unsigned short *)"\0\xff" < 0x100) ? ( (b0)<<8 | (b1) ) : ( (b1)<<8 | (b0) ))
#endif

//compiler def
#if (defined(__arm__) && !defined(__thumb__))
#endif

#if (defined(__arm__) && !defined(__thumb__)) || defined(SK_BUILD_FOR_WINCE) || (defined(SK_BUILD_FOR_SYMBIAN) && !defined(__MARM_THUMB__))
/* e.g. the ARM instructions have conditional execution, making tiny branches cheap */
#define ME_CPU_HAS_CONDITIONAL_INSTRUCTION
#endif

#endif
