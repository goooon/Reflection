#ifndef ZHIHE_Types_GUARD_H__
#define ZHIHE_Types_GUARD_H__
#include "./utils.h"
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


	//typedef bool(*ConvFunc)(void* in, void* out);
	//bool fail_all(void*, void*) { return false; }
	//bool b8_b8(void* in,void* out) { *(u8*)out = *(u8*)in; return true; }
	//bool b8_b16(void* in, void* out) { *(u16*)out = *(u8*)in; return true; }
	//bool b8_b32(void* in, void* out) { *(u32*)out = *(u8*)in; return true; }
	//bool b8_b64(void* in, void* out) { *(u64*)out = *(u8*)in; return true; }
	//bool b8_f32(void* in, void* out) { *(f32*)out = *(u8*)in; return true; }
	//bool b8_f64(void* in, void* out) { *(f64*)out = *(u8*)in; return true; }

	//bool b16_b8(void* in, void* out) { *(u8*)out = *(u16*)in; return true; }
	//bool b16_b16(void* in, void* out) { *(u16*)out = *(u16*)in; return true; }
	//bool b16_b32(void* in, void* out) { *(u32*)out = *(u16*)in; return true; }
	//bool b16_b64(void* in, void* out) { *(u64*)out = *(u16*)in; return true; }
	//bool b16_f32(void* in, void* out) { *(f32*)out = *(u16*)in; return true; }
	//bool b16_f64(void* in, void* out) { *(f64*)out = *(u16*)in; return true; }
	//
	//bool b32_b8(void* in, void* out) { *(u8*)out = *(u32*)in; return true; }
	//bool b32_b16(void* in, void* out) { *(u16*)out = *(u32*)in; return true; }
	//bool b32_b32(void* in, void* out) { *(u32*)out = *(u32*)in; return true; }
	//bool b32_b64(void* in, void* out) { *(u64*)out = *(u32*)in; return true; }
	//bool b32_f32(void* in, void* out) { *(f32*)out = *(u32*)in; return true; }
	//bool b32_f64(void* in, void* out) { *(f64*)out = *(u32*)in; return true; }

	//bool b64_b8(void* in, void* out) { *(u8*)out = *(u64*)in; return true; }
	//bool b64_b16(void* in, void* out) { *(u16*)out = *(u64*)in; return true; }
	//bool b64_b32(void* in, void* out) { *(u32*)out = *(u64*)in; return true; }
	//bool b64_b64(void* in, void* out) { *(u64*)out = *(u64*)in; return true; }
	//bool b64_f32(void* in, void* out) { *(f32*)out = *(u64*)in; return true; }
	//bool b64_f64(void* in, void* out) { *(f64*)out = *(u64*)in; return true; }

	//bool f32_b8(void* in, void* out) { *(u8*)out = *(f32*)in; return true; }
	//bool f32_u16(void* in, void* out) { *(u16*)out = *(f32*)in; return true; }
	//bool f32_u32(void* in, void* out) { *(u32*)out = *(f32*)in; return true; }
	//bool f32_u64(void* in, void* out) { *(u64*)out = *(f32*)in; return true; }
	//bool f32_f32(void* in, void* out) { *(f32*)out = *(f32*)in; return true; }
	//bool f32_f64(void* in, void* out) { *(f64*)out = *(f32*)in; return true; }

	//bool f64_b8(void* in, void* out) { *(u8*)out = *(f64*)in; return true; }
	//bool f64_b16(void* in, void* out) { *(u16*)out = *(f64*)in; return true; }
	//bool f64_b32(void* in, void* out) { *(u32*)out = *(f64*)in; return true; }
	//bool f64_b64(void* in, void* out) { *(u64*)out = *(f64*)in; return true; }
	//bool f64_f32(void* in, void* out) { *(f32*)out = *(f64*)in; return true; }
	//bool f64_f64(void* in, void* out) { *(f64*)out = *(f64*)in; return true; }
	////7 x 7
	//ConvFunc convs[7][7] = { 
	//	{ fail_all ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all },
	//	{ fail_all ,b8_b8,	  b8_b16,	b8_b32,	  b8_b64,	b8_f32,   b8_f64},
	//	{ fail_all ,b16_b8,	  b16_b16,	b16_b32,  b16_b64,	b16_f32,  b16_f64 },
	//	{ fail_all ,b32_b8,	  b32_b16,	b32_b32,  b32_b64,	b32_f32,  b32_f64 },
	//	{ fail_all ,b64_b8,	  b64_b16,	b64_b32,  b64_b64,	b64_f32,  b64_f64 },
	//	{ fail_all ,f32_b8,	  f32_b16,	f32_b32,  f32_b64,	f32_f32,  f32_f64 },
	//	{ fail_all ,f64_b8,	  f64_b16,	f64_b32,  f64_b64,	f64_f32,  f64_f64 },
	//};


	struct TypeIdMask
	{
		enum  ET{};
		
		

		const static u8 None  = 0;
		const static u8 Bool = 1;
		const static u8 Number =  2;
		const static u8 Struct =  3;
		const static u8 Object =  4;
		const static u8 Pointer = 5;
		const static u8 Other = 6;


		const static u32 TYPEID_CONV_MASK = 0x00FF0000;
		//const static u32 NUMBER_MASK = 0xFF << 28;
		enum Cate {
			Cate0 = 0, CateN8, CateN16, CateN32, CateN64, CateF32, CateF64, CateArr, CateRaw, CateObj, CateCst, CateType,CateCount
		};
		const static u8 PTR_SIZE = sizeof(void*);
		const static u8 PTR_TYPE = PTR_SIZE == 8 ? CateN64 : CateN32;
		const static u8 ENU_SIZE = sizeof(ET);
		const static u8 ENU_TYPE = ENU_SIZE == 8 ? CateN64 : CateN32;
		enum class TypeId {
#define TYPE_MASK(idx,subIdx,conv,size,signMask)	idx << 28 | subIdx<<24 | conv<<16 | size<<8 | signMask
			//type       conv mask    size    ...
			v = TYPE_MASK(None,0, Cate0, 0, 0),
			boolean = TYPE_MASK(Bool,0, CateN8, 1, 0),
			s8  = TYPE_MASK(Number,0, CateN8, 1, 7),
			u8  = TYPE_MASK(Number, 1, CateN8, 1, 0),
			s16 = TYPE_MASK(Number, 2, CateN16, 2, 15),
			u16 = TYPE_MASK(Number, 3, CateN16, 2, 0),
			s32 = TYPE_MASK(Number, 4, CateN32, 4, 31),
			u32 = TYPE_MASK(Number, 5, CateN32, 4, 0),
			s64 = TYPE_MASK(Number, 6, CateN64, 8, 63),
			u64 = TYPE_MASK(Number, 7, CateN64, 8, 0),
			f32 = TYPE_MASK(Number, 8, CateF32, 4, 31),
			f64 = TYPE_MASK(Number, 9, CateF64, 8, 63),
			enu = TYPE_MASK(Number, 10, ENU_TYPE, ENU_SIZE, 0),
			ref = TYPE_MASK(Pointer, 0, PTR_TYPE, PTR_SIZE, 0),
			ptr = TYPE_MASK(Pointer, 1, PTR_TYPE, PTR_SIZE, 0),
			func = TYPE_MASK(Pointer,2, PTR_TYPE, PTR_SIZE, 0),
			arr  = TYPE_MASK(Pointer,3, PTR_TYPE, 251, 0),
			astr = TYPE_MASK(Pointer,4, PTR_TYPE, PTR_SIZE, 0),
			wstr = TYPE_MASK(Pointer,5, PTR_TYPE, PTR_SIZE, 0),
			
			raw = TYPE_MASK(Struct,0, CateRaw, 252, 0),
			obj = TYPE_MASK(Object,0, CateObj, 253, 0),
			cst = TYPE_MASK(Other, 0, CateCst, 254, 0),
			type = TYPE_MASK(Other,1, CateType, 255, 0),
			count = 23
#undef TYPE_MASK
		};
		
		TypeIdMask(TypeId id) :id(id) {}
		u32  getSign() { return 1 & (u32)id; }
		bool isNumber() { return ((u32)id >> 28) == Number; }
		u8   getSize() { return ((u32)id) >> 8; }
		Cate getCate() { return (Cate)(u8)(((u32)id) >> 16); }
		u8   getIndex() { return ((u32)id) >> 24; }
		TypeId getTypeId() { return id; }
		void setTypeId(TypeId idx) {id = idx; }
	private:
		TypeId id;
	};

	typedef TypeIdMask::TypeId TypeId;

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
#include "./rtti.h"

#endif

