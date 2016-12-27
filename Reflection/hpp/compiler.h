#ifndef ZHIHE_Compiler_GUARD_H__
#define ZHIHE_Compiler_GUARD_H__

//////////////////////////////////////////////////////////////////////////
// DLL export and import definitions

#define ME_LIB

#include "./Arch.h"

#if  defined(DEBUG) ||  defined (_DEBUG)
#define ME_DEBUG
#else
#define ME_RELEASE
#endif
//////////////////////////////////////////////////////////////////////////

#if ME_TARGET == ME_TARGET_WIN

# if defined(__MINGW32__) || \
    defined(__CYGWIN__)  || \
    (defined (_MSC_VER) && _MSC_VER < 1300)
#  define ME_INLINE inline
# else
#  define ME_INLINE __forceinline
# endif
#else
#  define ME_INLINE    inline
#endif

#define ME_COMPILER_MSVC    0
#define ME_COMPILER_GNU     1

#if defined(_MSC_VER)
# define ME_COMPILER ME_COMPILER_MSVC
#pragma  warning(once:4458) 
#elif defined(__GNUC__)
# define ME_COMPILER ME_COMPILER_GNU
#else
# error unknown compiler
#endif

#if ME_COMPILER == ME_COMPILER_MSVC
// Function type macros.
#define ME_VARARGS            __cdecl                    /* Functions with variable arguments */
#define ME_CDECL              __cdecl                    /* Standard C function */
#define ME_STDCALL            __stdcall                /* Standard calling convention */
#define ME_FORCEINLINE        __forceinline            /* Force code to be inline */
#define ME_FORCENOINLINE      __declspec(noinline)    /* Force code to NOT be inline */

// Hints compiler that expression is true; generally restricted to comparisons against constants
#define ASSUME(expr)...       __assume(expr)


// Pragmas
#define MSVC_PRAGMA(Pragma) __pragma(Pragma)

#ifndef ME_LIB
#ifdef ME_DLL
#define ME_API __declspec(dllexport)
#else
#define ME_API __declspec(dllimport)
#endif
#else
#define ME_API  
#endif

// disable this now as it is annoying for generic platform implementations
#pragma warning(disable : 4100) // unreferenced formal parameter
#endif

#if ME_COMPILER == ME_COMPILER_MSVC
#define DECL_MSC_ALIGNED_CLASS(c,n) __declspec(align(n)) c
#define DECL_MSC_ALIGN(n) __declspec(align(n))
#define DECL_GNU_ALIGNED_CLASS(c,n) 
#define DECL_GNU_ALIGN(n) 
#define DECL_GNU_PACKED

#elif ME_COMPILER == ME_COMPILER_GNU
#define DECL_MSC_ALIGNED_CLASS(c,n) 
#define DECL_MSC_ALIGN(n) 
#define DECL_GNU_ALIGNED_CLASS(c,n) c __attribute__ ((packed,aligned (n)))	
#define DECL_GNU_ALIGN(n) __attribute__ ((packed,aligned (n)))
#define DECL_GNU_PACKED __attribute__ ((packed))
#else
#define DECL_MSC_ALIGNED_CLASS(c,n) 
#define DECL_MSC_ALIGN(n) 
#define DECL_GNU_ALIGNED_CLASS(c,n) 
#define DECL_GNU_ALIGN(n)
#endif

///region marker///////////////////////////////////////////////////////////////////////
/*
#if decl_region || your_code_block_desc
your code block
#endif
*/
#define decl_region 1

#endif
