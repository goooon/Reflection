#ifndef ZHIHE_Rtti_GUARD_H___
#define ZHIHE_Rtti_GUARD_H___
#include <typeinfo>
#include "./types.h"
#include "./tlString.h"
#include "./trace.h"

#if ME_COMPILER == ME_COMPILER_GNU
#define __STDC_NO_COMPLEX__
#define VS_HLPER( attr ) attr
#define PRIVATE_ARGS_GLUE(x, y) x y
#define PRIVATE_PRECLEAR(...) n,##__VA_ARGS__

#include "./p99_gcc/p99_for.h"

#define PRIVATE_ASSERT_VAR_ARGS_IMPL_COUNT(  _0, \
		_1, _2, _3, _4, _5, _6, _7, _8, \
		_9, _10, _11, _12, _13, _14, _15, _16,  \
		_17, _18, _19, _20, _21, _22, _23, _24, \
		_25, _26, _27, _28, _29, _30, _31, _32, \
		_33, _34, _35, _36, _37, _38, _39, _40, \
		_41, _42, _43, _44, _45, _46, _47, _48, \
		_49, _50, _51, _52, _53, _54, _55, _56, \
		_57, _58, _59, _60, _61, _62, _63, _64, \
		_65, _66, _67, _68, _69, _70, _71, _72, \
		_73, _74, _75, _76, _77, _78, _79, _80, \
		_81, _82, _83, _84, _85, _86, _87, _88, \
		_89, _90, _91, _92, _93, _94, _95, _96, \
		_97, _98, _99, _100, _101, _102, _103, _104, \
		_105, _106, _107, _108, _109, _110, _111, _112, \
		_113, _114, _115, _116, _117, _118, _119, _120, \
		_121, _122, _123, _124, N, \
		...) N
#define PRIVATE_ASSERT_VAR_ARGS_IMPL(args)  PRIVATE_ASSERT_VAR_ARGS_IMPL_COUNT args

#define COUNT_ASSERT_VAR_ARGS(...)  P99_NARG(__VA_ARGS__)


#define INDEX_ASSERT_VAR_ARGS(...)  PRIVATE_ASSERT_VAR_ARGS_IMPL((PRIVATE_PRECLEAR(__VA_ARGS__),    123, 122, 121, 120,      \
 119, 118, 117, 116, 115, 114, 113, 112,                                         \
 111, 110, 109, 108, 107, 106, 105, 104,                                         \
 103, 102, 101, 100, 99, 98, 97, 96,                                             \
 95, 94, 93, 92, 91, 90, 89, 88,                                                 \
 87, 86, 85, 84, 83, 82, 81, 80,                                                 \
 79, 78, 77, 76, 75, 74, 73, 72,                                                 \
 71, 70, 69, 68, 67, 66, 65, 64,                                                 \
 63, 62, 61, 60, 59, 58, 57, 56,                                                 \
 55, 54, 53, 52, 51, 50, 49, 48,                                                 \
 47, 46, 45, 44, 43, 42, 41, 40,                                                 \
 39, 38, 37, 36, 35, 34, 33, 32,                                                 \
 31, 30, 29, 28, 27, 26, 25, 24,                                                 \
 23, 22, 21, 20, 19, 18, 17, 16,                                                 \
 15, 14, 13, 12, 11, 10, 9, 8,                                                   \
 7, 6, 5, 4, 3, 2, 1, 0, 0))
#else
#define __STDC_NO_COMPLEX__

#define VS_HLPER( attr ) attr
#define PRIVATE_ARGS_GLUE(x, y) x y
#define PRIVATE_PRECLEAR(...) n,##__VA_ARGS__

#include "./p99_vs/p99_for.h"

#define PRIVATE_ASSERT_VAR_ARGS_IMPL_COUNT(  _0,\
		_1, _2, _3, _4, _5, _6, _7, _8, \
		_9, _10, _11, _12, _13, _14, _15, _16, \
		_17, _18, _19, _20, _21, _22, _23, _24, \
		_25, _26, _27, _28, _29, _30, _31, _32, \
		_33, _34, _35, _36, _37, _38, _39, _40, \
		_41, _42, _43, _44, _45, _46, _47, _48, \
		_49, _50, _51, _52, _53, _54, _55, _56, \
		_57, _58, _59, _60, _61, _62, _63, _64, \
		_65, _66, _67, _68, _69, _70, _71, _72, \
		_73, _74, _75, _76, _77, _78, _79, _80, \
		_81, _82, _83, _84, _85, _86, _87, _88, \
		_89, _90, _91, _92, _93, _94, _95, _96, \
		_97, _98, _99, _100, _101, _102, _103, _104, \
		_105, _106, _107, _108, _109, _110, _111, _112, \
		_113, _114, _115, _116, _117, _118, _119, _120, \
		_121, _122, _123, _124, N, \
		...) N
#define PRIVATE_ASSERT_VAR_ARGS_IMPL(args)  PRIVATE_ASSERT_VAR_ARGS_IMPL_COUNT args

#define COUNT_ASSERT_VAR_ARGS(...)  PRIVATE_ASSERT_VAR_ARGS_IMPL((PRIVATE_PRECLEAR(__VA_ARGS__),  124, 123, 122, 121, 120,      \
 119, 118, 117, 116, 115, 114, 113, 112,                                         \
 111, 110, 109, 108, 107, 106, 105, 104,                                         \
 103, 102, 101, 100, 99, 98, 97, 96,                                             \
 95, 94, 93, 92, 91, 90, 89, 88,                                                 \
 87, 86, 85, 84, 83, 82, 81, 80,                                                 \
 79, 78, 77, 76, 75, 74, 73, 72,                                                 \
 71, 70, 69, 68, 67, 66, 65, 64,                                                 \
 63, 62, 61, 60, 59, 58, 57, 56,                                                 \
 55, 54, 53, 52, 51, 50, 49, 48,                                                 \
 47, 46, 45, 44, 43, 42, 41, 40,                                                 \
 39, 38, 37, 36, 35, 34, 33, 32,                                                 \
 31, 30, 29, 28, 27, 26, 25, 24,                                                 \
 23, 22, 21, 20, 19, 18, 17, 16,                                                 \
 15, 14, 13, 12, 11, 10, 9, 8,                                                   \
 7, 6, 5, 4, 3, 2, 1, 0))


#define INDEX_ASSERT_VAR_ARGS(...)  PRIVATE_ASSERT_VAR_ARGS_IMPL((PRIVATE_PRECLEAR(__VA_ARGS__),    123, 122, 121, 120,      \
 119, 118, 117, 116, 115, 114, 113, 112,                                         \
 111, 110, 109, 108, 107, 106, 105, 104,                                         \
 103, 102, 101, 100, 99, 98, 97, 96,                                             \
 95, 94, 93, 92, 91, 90, 89, 88,                                                 \
 87, 86, 85, 84, 83, 82, 81, 80,                                                 \
 79, 78, 77, 76, 75, 74, 73, 72,                                                 \
 71, 70, 69, 68, 67, 66, 65, 64,                                                 \
 63, 62, 61, 60, 59, 58, 57, 56,                                                 \
 55, 54, 53, 52, 51, 50, 49, 48,                                                 \
 47, 46, 45, 44, 43, 42, 41, 40,                                                 \
 39, 38, 37, 36, 35, 34, 33, 32,                                                 \
 31, 30, 29, 28, 27, 26, 25, 24,                                                 \
 23, 22, 21, 20, 19, 18, 17, 16,                                                 \
 15, 14, 13, 12, 11, 10, 9, 8,                                                   \
 7, 6, 5, 4, 3, 2, 1, 0, 0))
#endif

namespace zhihe
{
	template <class D, class B>
	struct ConversionHelper
	{
		struct Host
		{
			operator B() const;
			operator D();
		};
		typedef char(&yes)[1];
		typedef char(&no)[2];
		template <typename T>
		static yes Test(D, T);
		static no Test(B, int);
	};

	template <class D, class B>
	struct Conversion
	{
		typedef ConversionHelper<D, B> H;
		typedef D DD;
		typedef typename ConversionHelper<DD, B>::Host Host;
		enum { exists = sizeof(typename H::yes) == sizeof(ConversionHelper<DD, B>::Test(Host(), int())) };
		enum { exists2Way = ((int)exists) && ((int)Conversion<B, DD>::exists) };
		enum { sameType = false };
	};

	template <class D>
	struct Conversion<D, D>
	{
		enum { exists = 1, exists2Way = 1, sameType = 1 };
	};

	template <class D>
	struct Conversion<void, D>
	{
		enum { exists = 0, exists2Way = 0, sameType = 0 };
	};

	template <class D>
	struct Conversion<D, void>
	{
		enum { exists = 0, exists2Way = 0, sameType = 0 };
	};

	template <class D>
	struct Conversion<void*, D*>
	{
		enum { exists = 1, exists2Way = 0, sameType = 0 };
	};

	template <class D>
	struct Conversion<D*, void*>
	{
		enum { exists = 1, exists2Way = 0, sameType = 0 };
	};

	template <>
	struct Conversion<void, void>
	{
	public:
		enum { exists = 1, exists2Way = 1, sameType = 1 };
	};

#define IS_D_FROM_B(D, B) \
    (zhihe::Conversion<const D*, const B*>::exists && !zhihe::Conversion<const B*, void>::sameType)

#define IS_D_FROM_B_STRICT(D, B)  \
    (IS_D_FROM_B(D, B) &&!zhihe::Conversion<const D*, const B*>::sameType)

#define CAN_R_CONV_TO_L(L,R) \
    (zhihe::Conversion<R, L>::exists && !zhihe::Conversion<const L, void>::sameType)

#define CAN_R_CONV_TO_L_STRICT(L,R)  \
    (CAN_R_CONV_TO_L(L,R) &&!zhihe::Conversion<R, L>::sameType)
	template <typename L, typename R>
	struct Can_R_Conv_To_L
	{
		const static bool value = (zhihe::Conversion<R, L>::exists && !zhihe::Conversion<const L, void>::sameType);
	};
	template <typename L,typename R>
	struct Can_R_Conv_To_L_Strict
	{
		const static bool value = Can_R_Conv_To_L<L, R>::value && !zhihe::Conversion<R, L>::sameType;
	};

	template<typename D, typename B>
	struct is_D_extend_B {
		enum {
			result = (zhihe::Conversion<const D*, const B*>::exists && !zhihe::Conversion<const B*, const void>::sameType)
		};
	};

	template<typename D, typename B>
	struct is_D_extend_B_strict {
		enum {
			result = is_D_extend_B<D, B>::result &&!zhihe::Conversion<const D*, const B*>::sameType
		};
	};

	template <typename L, typename R>
	struct can_R_cast_to_L
	{
		enum {
			result = zhihe::Conversion<const R, const L>::exists && !zhihe::Conversion<const L, const void>::sameType
		};
	};
	//////////////////////////////////////////////////////////////////////////

#ifdef TRACE_MEMORY
#define TRACE_MEMORY_ARGS const char* func, u32 line
#define TRACE_MEMORY_ARGS_IN fun,line
#define ObjectNew(D) static zhihe::Object* NewObject(const char* file,zhihe::u32 line){return new (line,file,TypeName.Name) D();} \
                     static zhihe::Struct* NewStruct(const char* file,zhihe::u32 line){return (zhihe::Struct*)(D::RootType*)new (line,file,TypeName.Name) D();}
#define StructNew(D) static zhihe::Struct* NewStruct(const char* file,zhihe::u32 line){return new (line,file,TypeName.Name) D();} \
					 static zhihe::Object* NewObject(const char* file,zhihe::u32 line){return 0;}
#else
#define TRACE_MEMORY_ARGS
#define TRACE_MEMORY_ARGS_IN
#define ObjectNew(D) static zhihe::Object* NewObject(){return new_me D;};static zhihe::Struct* NewStruct(){return (D::RootType*)new_me D();;}
#define StructNew(D) static zhihe::Struct* NewStruct(){return new_me D;};static zhihe::Object* NewObject(){return (Object*)(new_me D());}
#endif

#define DECL_TYPE(ClassType)     \
    friend class zhihe::Type;            \
    public:  static const zhihe::achar* GetTypeName(){return ClassType::TypeDesc::TypeName.Name;}

#define DECL_RAWTYPE(ClassType)     \
	StructNew(ClassType);			\
    friend   struct zhihe::Type;                                          \
	public:const    static TypeId TypeIndex = TypeId::raw;						  \
	friend   Propertys& zhihe::ImpStaticReflection<self>();				  \
	public:  static Propertys& GetStaticReflection(){return GetClassProperty(zhihe::ImpStaticReflection<self>());} \
	public:  static const zhihe::Type getType(){return type;}

#define DECL_RTTI_CORE(ClassType)						\
    public:    ObjectNew(ClassType);                                    \
    public:    virtual zhihe::Type  getType()const{return type;}        \
	friend     Propertys& zhihe::ImpStaticReflection<self>();			\
	public:    static Propertys& GetStaticReflection(){return GetClassProperty(zhihe::ImpStaticReflection<self>());} \
    public:    const static TypeId TypeIndex = TypeId::obj;

#define DECL_DERIVED(D)                                             \
    static D* New( zhihe::cachar* objType )                         \
    {                                                               \
        zhihe::Type tp = zhihe::Object::GetType(objType);           \
        if(!tp)														\
        {                                                           \
            LOG_W("%s is not registered",objType);                  \
            return vNull;                                           \
        }                                                           \
        if(tp.isKindOf(D::type))                                    \
        {                                                           \
            return (D*)(new_inst(tp));                              \
        }                                                           \
        return vNull;                                               \
    }
    #define TYPE_OFFSET(D,B) {&zhihe::TClass<B>::RunTime::rtti,static_cast<s32>((u8*)(zhihe::Struct*)(typename B::RootType*)(B*)(D*)(void*)1 - (u8*)(zhihe::Struct*)(typename D::RootType*)(D*)(void*)1)}

	template <int N>
	struct NType
	{
		typedef NType<N> TypeDesc;
		constexpr static const decltype(zhihe::internal::str(zh_numb2str(N))) TypeName = zhihe::internal::str(zh_numb2str(N));
	};
	template <int N>
	constexpr decltype(zhihe::internal::str(zh_numb2str(N))) NType<N>::TypeName;

#define DECL_TEMPLATE0(C) \
		protected: typedef C self; \
		public: typedef zhihe::internal::typedesc1<zh_str2type(#C)> TypeDesc;
#define DECL_TEMPLATE1(C,T)  \
		protected: typedef C self; \
		public: typedef zhihe::internal::typedesc4<zh_str2type(#C), zh_str2type("<"), zh_str2type(zhihe::TClass<T>::TypeDesc::TypeName.Name),zh_str2type(">")> TypeDesc;
#define DECL_TEMPLATE2(C,T1,T2)  \
		protected: typedef C self; \
		public: typedef zhihe::internal::typedesc6<zh_str2type(#C), zh_str2type("<"), zh_str2type(zhihe::TClass<T1>::TypeDesc::TypeName.Name), zh_str2type(","), zh_str2type(zhihe::TClass<T2>::TypeDesc::TypeName.Name),zh_str2type(">")> TypeDesc;

#define DECL_OBJECT5(B1,B2,B3,B4,B5)    \
    public:    typedef B1 base;                    \
    xStaticAssert(IS_D_FROM_B_STRICT(self,B1),class_not_derived_from_##B1); \
    xStaticAssert(IS_D_FROM_B_STRICT(self,B2),class_not_derived_from_##B2); \
    xStaticAssert(IS_D_FROM_B_STRICT(self,B3),class_not_derived_from_##B3); \
    xStaticAssert(IS_D_FROM_B_STRICT(self,B4),class_not_derived_from_##B4); \
    xStaticAssert(IS_D_FROM_B_STRICT(self,B5),class_not_derived_from_##B5); \
    DECL_RTTI_CORE(self,TypeName.Name,TypeName.Hash,B1,B2,B3,B4,B5,0);    \
    DECL_DERIVED(self);

#define DECL_RAW_TYPE(T,s,e)	 \
	template <>struct TClass<T>  \
	{  \
		typedef T Type;  \
		typedef T raw_type;    \
		typedef T obj_type;   \
        const static TypeId TypeIndex = e; \
		typedef zhihe::internal::typedesc1<zh_str2type(s)> TypeDesc; \
		static zhihe::Type::Rtti rtti; \
		static zhihe::Type type() { return rtti; };\
	}; \
	zhihe::Type::Rtti TClass<T>::rtti = {&zhihe::BaseTypes::vNone,TClass<T>::TypeDesc::TypeName.Name,TClass<T>::TypeDesc::TypeName.Hash,TClass<T>::TypeIndex,&ImpStaticReflection<T>,&Wrapper<T>::newStruct,0};

#define DECL_STRUCT0()				\
	public:    typedef self base;								          \
    public:    typedef self RootType;                                     \
    public:    DECL_RAWTYPE(self)										  \
	public:    typedef zhihe::TRtti0<self> RunTime;						  \
	public:    static  zhihe::Type type(){return RunTime::rtti;}

#define DECL_INTERFACE(D)       \
    protected: typedef D RootType; \
    DECL_TEMPLATE0(D); \
	public:     typedef zhihe::TRtti0<self> RunTime;				    \
    public:     static zhihe::Type type(){return RunTime::rtti;}

#define DECL_OBJECT0()                                                  \
	public:    typedef self base;                                       \
    public:    typedef self RootType;                                   \
	public:    typedef zhihe::TRtti0<self> RunTime;					    \
    public:    DECL_RTTI_CORE(self);									\
	public:    static zhihe::Type type(){return RunTime::rtti;}


#define DECL_STRUCT1(B1)			\
    public:    typedef B1::RootType RootType;                       \
    public:    typedef B1 base;                                     \
	public:    DECL_RAWTYPE(self)									\
	public:    typedef zhihe::TRtti1<self,B1> RunTime;			\
	public:    static  zhihe::Type type(){return RunTime::rtti;}

#define DECL_OBJECT1(B1)                           \
    public:    typedef B1 base;                    \
    public:    typedef typename B1::RootType RootType;					\
	public:    typedef zhihe::TRtti1<self,B1> RunTime;				\
	public:    DECL_RTTI_CORE(self);									\
	public:    static  zhihe::Type type(){return RunTime::rtti;} \
    xStaticAssert(IS_D_FROM_B_STRICT(self,B1),class_not_derived_from_##B1);

#define DECL_OBJECT2(B1,B2)                            \
    public:    typedef B1 base;                        \
    public:    typedef typename B1::RootType RootType;          \
	public:    typedef zhihe::TRtti2<self,B1,B2> RunTime;		\
    DECL_RTTI_CORE(self);     \
	public:    static  zhihe::Type type() { return RunTime::rtti; } \
    xStaticAssert(IS_D_FROM_B_STRICT(self,B1),class_not_derived_from_##B1); \
    xStaticAssert(IS_D_FROM_B_STRICT(self,B2),class_not_derived_from_##B2);

#define DECL_OBJECT3(B1,B2,B3)         \
    public:    typedef B1 base;                    \
    public:    typedef B1::RootType RootType;          \
	public:    typedef zhihe::TRtti3<self,B1,B2,B3> RunTime;			  \
	public:    static  zhihe::Type type() { return RunTime::rtti; }       \
    DECL_RTTI_CORE(self);      \
    xStaticAssert(IS_D_FROM_B_STRICT(self,B1),class_not_derived_from_##B1); \
    xStaticAssert(IS_D_FROM_B_STRICT(self,B2),class_not_derived_from_##B2); \
    xStaticAssert(IS_D_FROM_B_STRICT(self,B3),class_not_derived_from_##B3);

#define DECL_OBJECT4(B1,B2,B3,B4)     \
    public:    typedef B1 base;                    \
	public:    typedef B1::RootType RootType;          \
	public:    typedef zhihe::TRtti4<self,B1,B2,B3,B4> RunTime;			  \
	public:    static  zhihe::Type type() { return RunTime::rtti; }       \
    DECL_RTTI_CORE(self);      \
    xStaticAssert(IS_D_FROM_B_STRICT(self,B1),class_not_derived_from_##B1); \
    xStaticAssert(IS_D_FROM_B_STRICT(self,B2),class_not_derived_from_##B2); \
    xStaticAssert(IS_D_FROM_B_STRICT(self,B3),class_not_derived_from_##B3); \
    xStaticAssert(IS_D_FROM_B_STRICT(self,B4),class_not_derived_from_##B4);

#define DECL_REGISTER(D)    \
    public:                 \
    static void registerToFactory(const D*)  \
    {                 zhihe::internal::ClassFactory<D>::_index;       \
    }

#define DECL_MESSAGE(H,D,B)    public:    \
    typedef MsgStatus (H::*EventId)(myMsgMgr*,Msg*);                             \
    D(EventId eid,Object* sender = vNull,Object* message = vNull):               \
    B((B::EventId)eid,sender,message)                                            \
    {                                                                            \
    xStaticAssert(sizeof(B::EventId) == sizeof(EventId),should_be_same_size);    \
    }

#define PRIVATE_TPL_HELPER1(t) DECL_TEMPLATE0(t)
#define PRIVATE_TPL_HELPER2(t,t1) DECL_TEMPLATE1(t, t1)
#define PRIVATE_TPL_HELPER3(t,t1,t2) DECL_TEMPLATE2(t, t1,t2)

	/* Pick the right helper macro to invoke. */
#define PRIVATE_TPL_CHOOSE_HELPER2(count)  DECL_TEMPLATE##count
#define PRIVATE_TPL_CHOOSE_HELPER1(count)  PRIVATE_TPL_CHOOSE_HELPER2(count)
#define PRIVATE_TPL_CHOOSE_HELPER(count)   PRIVATE_TPL_CHOOSE_HELPER1(count)
	/* The actual macro. */
#if ME_COMPILER == ME_COMPILER_GNU
#define DECL_TPLT(...) PRIVATE_TPL_CHOOSE_HELPER(INDEX_ASSERT_VAR_ARGS(__VA_ARGS__))(__VA_ARGS__)
#elif ME_COMPILER == ME_COMPILER_MSVC
#define DECL_TPLT(...) PRIVATE_ARGS_GLUE(PRIVATE_TPL_CHOOSE_HELPER(INDEX_ASSERT_VAR_ARGS(__VA_ARGS__)),(__VA_ARGS__))
#else
#endif

#define PRIVATE_RTTI_HELPER1(t) DECL_##t; DECL_OBJECT0()
#define PRIVATE_RTTI_HELPER2(t, t1) DECL_##t;DECL_OBJECT1(t1)
#define PRIVATE_RTTI_HELPER3(t, t1,t2) DECL_##t;DECL_OBJECT2(t1,t2)
#define PRIVATE_RTTI_HELPER4(t, t1,t2,t3) DECL_##t;DECL_OBJECT3(t1,t2,t3)

#define PRIVATE_RTTI_CHOOSE_HELPER2(count)  PRIVATE_RTTI_HELPER##count
#define PRIVATE_RTTI_CHOOSE_HELPER1(count)  PRIVATE_RTTI_CHOOSE_HELPER2(count)
#define PRIVATE_RTTI_CHOOSE_HELPER(count)   PRIVATE_RTTI_CHOOSE_HELPER1(count)

#define DECL_OBJECT_TPLT(...) PRIVATE_ARGS_GLUE(PRIVATE_RTTI_CHOOSE_HELPER(COUNT_ASSERT_VAR_ARGS(__VA_ARGS__)), (__VA_ARGS__))
#define DECL_OBJECT(...)      DECL_OBJECT_TPLT(__VA_ARGS__)

	///Struct///////////////////////////////////////////////////////////////////////

#define PRIVATE_STRUCT_HELPER1(t) DECL_##t; DECL_STRUCT0()
#define PRIVATE_STRUCT_HELPER2(t, t1) DECL_##t;DECL_STRUCT1(t1)
#define PRIVATE_STRUCT_HELPER3(t, t1,t2) DECL_##t;DECL_STRUCT2(t1,t2)
#define PRIVATE_STRUCT_HELPER4(t, t1,t2,t3) DECL_##t;DECL_STRUCT3(t1,t2,t3)

#define PRIVATE_STRUCT_CHOOSE_HELPER2(count)  PRIVATE_STRUCT_HELPER##count
#define PRIVATE_STRUCT_CHOOSE_HELPER1(count)  PRIVATE_STRUCT_CHOOSE_HELPER2(count)
#define PRIVATE_STRUCT_CHOOSE_HELPER(count)   PRIVATE_STRUCT_CHOOSE_HELPER1(count)

#define DECL_STRUCT(...)      PRIVATE_ARGS_GLUE(PRIVATE_STRUCT_CHOOSE_HELPER(COUNT_ASSERT_VAR_ARGS(__VA_ARGS__)), (__VA_ARGS__))
	struct Struct;
	class  Object;
	class  Propertys;
	struct Enum : public Memory {
		struct Item {
			u32     flag;
			cachar* name;
		};
		Enum():count(0),items(nullptr){}
		Enum(u32 count,const Item* items):count(count),items(items){}
		u32   getLength() { return count; }
		const Item& operator[](u32 i) { return items[i]; }
	private:
		u32   count;
		const Item* items;
	};
	struct Type : public Memory
	{
	public:
		struct Rtti;
		struct BaseTypes
		{
			friend struct Type;
			Rtti* rtti;
			s32   off;
		public:
			static BaseTypes vNone;
			Struct* fromDerived(Struct* raw)const
			{
				return (Struct*)((const u8*)raw + off);
			}
		};
		struct Rtti
		{
			DECL_TPLT(Rtti);
		public:
			typedef Type (*ID)(void);
		public:
			const BaseTypes* _baseTypes;
			cachar* _name;
			hash64  _hash;
			TypeId  _index;
			Propertys& (*_funcGetPropertys)(void);
			Struct* (*_funcStruct)(TRACE_MEMORY_ARGS);
			Object* (*_funcObject)(TRACE_MEMORY_ARGS);
		public:
			const achar* getName()const { return _name; }
			hash64     getHash()const { return _hash; }
			Type	   getType()const { return *this; }
			Object*    NewObject(TRACE_MEMORY_ARGS)const { return _funcObject(TRACE_MEMORY_ARGS_IN); }
			Struct*    NewStruct(TRACE_MEMORY_ARGS)const { return _funcStruct(TRACE_MEMORY_ARGS_IN); }
			const BaseTypes* getBaseTypes()const { return _baseTypes; }
			Propertys& getPropertys()const {
				return _funcGetPropertys();
			}
			TypeId     getTypeId()const { return _index; }
			b32 isExactKindOf(const Type& type) const { return type == *this; }
			b32 isKindOf(const Type& baseClass) const
			{
				if (this == baseClass.rtti)
				{
					return vTrue;
				}
				for (const BaseTypes* pid = _baseTypes; pid->rtti; pid++)
				{
					if (pid->rtti->isKindOf(baseClass))
					{
						return vTrue;
					}
				}
				return vFalse;
			}
			void* downCast(void* data, Type inType)const
			{
				if (_baseTypes == inType.getBaseTypes())
				{
					return data;
				}
				u8* indata = (u8*)data;
				void* outData;
				for (const BaseTypes* pid = _baseTypes; pid->rtti; pid++)
				{
					outData = pid->rtti->downCast(indata - pid->off, inType);
					if (outData != nullptr)return outData;
				}
				return nullptr;
			}
			void* upCast(void* data, Type inType)const
			{
				if (_baseTypes == inType.getBaseTypes())
				{
					return data;
				}
				u8* indata = (u8*)data;
				void* outData;
				for (const BaseTypes* pid = _baseTypes; pid->rtti ; pid++)
				{
					outData = upCast(indata + pid->off, *pid->rtti);
					if (outData != nullptr)return outData;
				}
				return nullptr;
			}
		};

	public:
		Type(){};
		Type(const Rtti& rtti):rtti(&rtti) {}
		Type(const Type& type):rtti(type.rtti){}
		Type(Type(*type)(void)):rtti(type().rtti) {}

		b32 operator == (Type type)const { return rtti == type.rtti; }
		b32 operator != (Type type)const { return rtti != type.rtti; }
		operator bool()const {return rtti != nullptr;};
		cachar* getName()const { return rtti->getName(); }
		hash64  getHash()const { return rtti->getHash(); }
		TypeId  getTypeId()const { return rtti->getTypeId(); }
		u32     getLength()const {return rtti->getTypeId() == TypeId::arr ? (u32)rtti->getHash() : 1;}

		Object*  newObject(TRACE_MEMORY_ARGS)const { return rtti->NewObject(TRACE_MEMORY_ARGS_IN); }
		Struct*  newStruct(TRACE_MEMORY_ARGS)const { return rtti->NewStruct(TRACE_MEMORY_ARGS_IN); }

		b32 isKindOf(Type type)const { return rtti->isKindOf(type); }
		b32 isExactKindOf(Type type)const { return rtti->isExactKindOf(type); }
		void*  downCast(void* indata, Type type)const { return rtti->downCast(indata, type); }
		void*  upCast(void* indata, Type type)const { return rtti->upCast(indata, type); }
		Propertys& getPropertys()const { return rtti->getPropertys(); }
		const BaseTypes* getBaseTypes()const { return rtti->getBaseTypes(); }
	private:
		const Rtti* rtti;
	public:
		const static Type vNone;
	};
	typedef const Type::BaseTypes BaseTypes;
	Type::BaseTypes Type::BaseTypes::vNone = { 0 };

	const Type Type::vNone;
	template <typename T>
	Propertys& ImpStaticReflection();

	template <typename CN,typename TN>
	class RawRtti0 : public Memory
	{
	public:
		typedef TN TypeDesc;
		static Type::Rtti rtti;
		static Struct* NewStruct() { return new_me CN(); }
	};
	template <typename CN, typename TN>
	Type::Rtti RawRtti0<CN,TN>::rtti = { &zhihe::BaseTypes::vNone,RawRtti0<CN,TN>::TypeDesc::TypeName.Name,RawRtti0<CN,TN>::TypeDesc::TypeName.Hash,zhihe::TypeId::raw,&ImpStaticReflection<CN>,RawRtti0<CN,TN>::NewStruct,0 };

#define DECL_REFLECT(T,N) \
	template <>struct TClass<T> \
	{ \
		typedef internal::typedesc1<zh_str2type(N)> TypeDesc; \
		typedef zhihe::RawRtti0<T,TypeDesc> RunTime; \
		const static zhihe::TypeId TypeIndex = zhihe::TypeId::raw; \
		static zhihe::Type type() {\
			return RunTime::rtti; \
		} \
	};
}
#endif
