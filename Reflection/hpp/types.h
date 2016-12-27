#ifndef ZHIHE_Types_GUARD_H__
#define ZHIHE_Types_GUARD_H__
#include "./Utils.h"
#include <typeinfo>
#include <stddef.h>
#include <stdlib.h>
namespace zhihe
{
	typedef signed int      sint;
	typedef unsigned int    uint;

	typedef signed char     s8;
	typedef unsigned char   u8;
	#ifdef __int16
	typedef __int16         s16;
	typedef unsigned __int16  u16;
	typedef __int32          s32;
	typedef unsigned __int32 u32;
	#else
	typedef signed short         s16;
	typedef unsigned short  u16;
	typedef int          s32;
	typedef unsigned int u32;
	#endif

#if ME_COMPILER == ME_COMPILER_GNU
	typedef long long          s64;
	typedef unsigned long long u64;
#else
	typedef __int64          s64;
	typedef unsigned __int64 u64;
#endif
	typedef u64             hash64;
	typedef double          f64;
	typedef float           f32;
	typedef s8              sbyte;
	typedef u8              ubyte;
	typedef s16             sword;
	typedef u16             uword;
	typedef s32             snumb;
	typedef u32             unumb;
	typedef long            slong;
	typedef unsigned long   ulong;
	typedef f32             realf;
	typedef f64             reald;
#ifndef size_t
	//typedef u32         size_t;
#endif
	typedef u32				b32;
	typedef wchar_t         wchar;
	typedef char            achar;
	typedef u32             result;
	typedef const achar     cachar;
	typedef const wchar     cwchar;
	typedef const achar*    castr;
	typedef const wchar*    cwstr;
	typedef u32             color;

	enum class TypeId {
		v, boolean,
		s8,  u8,
		s16, u16,
		s32, u32,
		s64, u64,
		f32,
		f64,
		astr,
		wstr,
		ptr,
		arr,
		ref,
		raw,
		obj,
		func,
		enu,
		cst,
		type,
		count
	};

#define vNull          (0)
#define vVoid
#define vTrue          (1)
#define vFalse         (0)

	typedef struct SafeBoolStruct {
		typedef void(*StaticFunctionPtr)(void);
		int a_data_pointer_to_this_is_0_on_buggy_compilers;
		StaticFunctionPtr m_nonzero;
	} UselessTypedef;
	typedef SafeBoolStruct::StaticFunctionPtr SafeBoolStruct::*SafeBool;
}



namespace zhihe
{
	struct Memory
	{
	public:
		static void dispalyInfo();
		static void setCheckMemory(b32 check = vTrue);
		static void checkMemory(b32 assert = vFalse);
	public:
		static void  copy(void* dst, const void* src, size_t size);
		static void  set(void* dst, int n, size_t size);
		static void  setZero(void* dst, size_t size);
		static void* clone(size_t size, const void* src);
		static b32 compare(const void* m1, const void* m2, size_t size);

		static void* Alloc(size_t size);
		static void  Free(const void* p);
		//static void* Realloc(void* p,size_t size);

		static void* Alloc(size_t size, int line, const char *func);
		static void* Alloc(size_t size, const char* fmt, ...);
		void* operator new(mem_size size) { return malloc(size); }
		//void* operator new(me_size size,void* p);
		void* operator new(mem_size size, int line, const char file[]) { return malloc(size); }
		void* operator new(mem_size size, int line, const char* file, const char* info) { return malloc(size); }
		//void* operator delete(me_size size,void* p);
		void  operator delete(void* p) { free(p); }
		void  operator delete(void* p, int line, const char *func) { free(p); }
		void  operator delete(void* p, int line, const char *func, const char* ext) {};
		//void  operator delete(void* p,const char* fmt,...){}
		void* operator new[](mem_size size);
		void  operator delete[](void* p);
	};



#ifdef TRACE_MEMORY
#define new_me         new (__LINE__,__FILE__)
#define del_me         delete
#else
#define new_me ::new
#define del_me ::delete
#endif

#if ME_COMPILER != ME_COMPILER_GNU
#ifndef offsetof
#define offsetof(s,m)   (size_t)&(((s *)0)->m)
#endif
#endif

	template<bool Cond, class T1 = void, class T2 = void> struct Type_Select { typedef T2 Result; };
	template<class T1, class T2> struct Type_Select<true, T1, T2> { typedef T1 Result; };
}
#include "./Rtti.h"
#endif

