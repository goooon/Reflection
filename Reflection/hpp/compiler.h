#ifndef ZHIHE_Compiler_GUARD_H__
#define ZHIHE_Compiler_GUARD_H__

//////////////////////////////////////////////////////////////////////////
// DLL export and import definitions

#define ME_LIB

#include "./arch.h"

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

//////////////////////////////////////////////////////////////////////////
// Export declaration to make symbols visible for dll/so
#ifdef LIBASYNC_STATIC
# define LIBASYNC_EXPORT
# define LIBASYNC_EXPORT_EXCEPTION
#else
# ifdef _WIN32
#  ifdef LIBASYNC_BUILD
#   define LIBASYNC_EXPORT __declspec(dllexport)
#  else
#   define LIBASYNC_EXPORT __declspec(dllimport)
#  endif
#  define LIBASYNC_EXPORT_EXCEPTION
# else
#  define LIBASYNC_EXPORT __attribute__((visibility("default")))
#  define LIBASYNC_EXPORT_EXCEPTION __attribute__((visibility("default")))
# endif
#endif

// Support compiling without exceptions
#ifndef LIBASYNC_NO_EXCEPTIONS
# ifdef __clang__
#  if !defined(__EXCEPTIONS) || !__has_feature(cxx_exceptions)
#   define LIBASYNC_NO_EXCEPTIONS
#  endif
# elif defined(__GNUC__) && !defined(__EXCEPTIONS)
#  define LIBASYNC_NO_EXCEPTIONS
# elif defined(_MSC_VER) && defined(_HAS_EXCEPTIONS) && !_HAS_EXCEPTIONS
#  define LIBASYNC_NO_EXCEPTIONS
# endif
#endif
#ifdef LIBASYNC_NO_EXCEPTIONS
# define LIBASYNC_THROW(...) std::abort()
# define LIBASYNC_RETHROW() do {} while (false)
# define LIBASYNC_RETHROW_EXCEPTION(except) std::terminate()
# define LIBASYNC_TRY if (true)
# define LIBASYNC_CATCH(...) else if (false)
#else
# define LIBASYNC_THROW(...) throw __VA_ARGS__
# define LIBASYNC_RETHROW() throw
# define LIBASYNC_RETHROW_EXCEPTION(except) std::rethrow_exception(except)
# define LIBASYNC_TRY try
# define LIBASYNC_CATCH(...) catch (__VA_ARGS__)
#endif

// Optional debug assertions. If exceptions are enabled then use those, but
// otherwise fall back to an assert message.
#ifndef NDEBUG
# ifndef LIBASYNC_NO_EXCEPTIONS
#  define LIBASYNC_ASSERT(pred, except, message) ((pred) ? ((void)0) : throw except(message))
# else
#  define LIBASYNC_ASSERT(pred, except, message) ((pred) ? ((void)0) : assert(message))
# endif
#else
# define LIBASYNC_ASSERT(pred, except, message) ((void)0)
#endif

// Annotate move constructors and move assignment with noexcept to allow objects
// to be moved if they are in containers. Compilers which don't support noexcept
// will usually move regardless.
#if defined(__GNUC__) || _MSC_VER >= 1900
# define LIBASYNC_NOEXCEPT noexcept
#else
# define LIBASYNC_NOEXCEPT throw()
#endif

// Cacheline alignment to avoid false sharing between different threads
#define LIBASYNC_CACHELINE_SIZE 64
#ifdef __GNUC__
# define LIBASYNC_CACHELINE_ALIGN __attribute__((aligned(LIBASYNC_CACHELINE_SIZE)))
#elif defined(_MSC_VER)
# define LIBASYNC_CACHELINE_ALIGN __declspec(align(LIBASYNC_CACHELINE_SIZE))
#else
# define LIBASYNC_CACHELINE_ALIGN alignas(LIBASYNC_CACHELINE_SIZE)
#endif

// Force symbol visibility to hidden unless explicity exported
#if defined(__GNUC__) && !defined(_WIN32)
# pragma GCC visibility push(hidden)
#endif
#endif
