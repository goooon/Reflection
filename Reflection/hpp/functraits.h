#ifndef ZHIHE_FunctionTraits_h__
#define ZHIHE_FunctionTraits_h__

#include "./TypeList.h"
#include "./TypeTraits.h"
/**
Since the throw specification is part of a function signature, the FuncTraits
family of templates needs to be specialized for both types. The
MEBRIDGE_THROWSPEC macro controls whether we use the 'throw ()' form, or
'noexcept' (if C++11 is available) to distinguish the functions.
*/
#if defined (__APPLE_CPP__) || defined(__APPLE_CC__) || defined(__clang__) || defined(__GNUC__) || \
    (defined (_MSC_VER) && (_MSC_VER >= 1700))
// Do not define MEBRIDGE_THROWSPEC since the Xcode and gcc  compilers do not
// distinguish the throw specification in the function signature.
# define MEBRIDGE_THROWSPEC
#else
// Visual Studio 10 and earlier pay too much mind to useless throw() spec.
//
# define MEBRIDGE_THROWSPEC throw()
#endif

namespace zhihe
{
	template <typename T>struct TClass;
	//==============================================================================
	template <typename T>struct TRaw{
		typedef T Type;
		typedef typename TClass<T>::TypeDesc TypeDesc;
		static  zhihe::Type  type() { return rtti; }
		static  zhihe::Type::Rtti rtti;
	};
	template <typename T>
	zhihe::Type::Rtti TRaw<T>::rtti = { &BaseTypes::vNone,TRaw<T>::TypeDesc::TypeName.Name,TRaw<T>::TypeDesc::TypeName.Hash,TClass<T>::TypeIndex,0,0,0 };

	template<typename T>
	struct TRaw<const T&> {
		typedef zh_str2type("&") ConstType;
		DECL_TYPEDESC2(TClass<T>::TypeDesc, internal::typedesc1<ConstType>);
		typedef T& Type;
		static  zhihe::Type  type() { return rtti; }
		static  zhihe::Type::Rtti rtti;
	};
	template<typename T>
	zhihe::Type::Rtti TRaw<const T&>::rtti = { &BaseTypes::vNone,TRaw<const T&>::TypeDesc::TypeName.Name,TRaw<const T&>::TypeDesc::TypeName.Hash,TClass<const T&>::TypeIndex,0,0,0 };

	template<typename T>
	struct TRaw<const T*> {
		//constexpr static auto TypeName = TClass<T>::TypeName + internal::str("*");
		typedef zh_str2type("*") StarType;
		DECL_TYPEDESC2(TClass<T>::TypeDesc, internal::typedesc1<StarType>);
		typedef T* Type;
		static  zhihe::Type  type() { return rtti; }
		static  zhihe::Type::Rtti rtti;
	};
	template<typename T>
	zhihe::Type::Rtti TRaw<const T*>::rtti = { &BaseTypes::vNone,TRaw<const T*>::TypeDesc::TypeName.Name,TRaw<const T&>::TypeDesc::TypeName.Hash,TClass<const T*>::TypeIndex,0,0,0 };

	template <typename T>struct TCls {
		typedef typename TClass<T>::TypeDesc TypeDesc;
		static  zhihe::Type  type() { return rtti; }
		static  zhihe::Type::Rtti rtti;
	};
	template<typename T>
	zhihe::Type::Rtti TCls<T>::rtti = { &BaseTypes::vNone,TCls<T>::TypeDesc::TypeName.Name,TCls<T>::TypeDesc::TypeName.Hash,TCls<T>::TypeIndex,0,0,0 };


	template <typename T, bool> struct TTp { typedef TClass<T> Type; };
	template <typename T> struct TTp<T, true> { typedef Object Type; };
	template <typename T> struct TObj : public TTp<T, std::is_base_of<Object,T>::value>::Type {};
	template <typename T> struct TObj<T*> : public TTp<T, std::is_base_of<Object, T>::value>::Type {};
	template <typename T> struct TObj<T&> : public TTp<T, std::is_base_of<Object, T>::value>::Type {};
	template <typename T> struct TObj<const T*> : public TTp<T, std::is_base_of<Object, T>::value>::Type {};
	template <typename T> struct TObj<const T&> : public TTp<T, std::is_base_of<Object, T>::value>::Type {};

	/**
	Traits for function pointers.

	There are three types of functions: global, non-const member, and const
	member. These templates determine the type of function, which class type it
	belongs to if it is a class member, the const-ness if it is a member
	function, and the type information for the return value and argument list.

	Expansions are provided for functions with up to 8 parameters. This can be
	manually extended, or expanded to an arbitrary amount using C++11 features.
	*/

    struct None
	{
		constexpr static auto toString()->decltype(internal::str("void"))
		{
			return internal::str("void");
		}
		//constexpr static auto TypeName = internal::str("void");
		typedef internal::typedesc1<zh_str2type("void")> TypeDesc;
		static Type::Rtti rtti;
		const static TypeId TypeIndex = TypeId::v;
		static Type type(){return rtti;}
	};

	template <class A, class D = A>struct ArgTraits {};

	//template <class A>
	//struct ArgTraits<void(*)(A)>
	//{
	//	typedef TypeList <A> Params;
	//	static BaseTypes  prop[2];
	//	static Type::Rtti rtti;
	//	static Type type(){return rtti;}
	//};
	//template <class A>
	//BaseTypes ArgTraits<void(*)(A)>::prop[2] = { {&TClass<A>::rtti,0 },BaseTypes::vNone };
	//template <class A>
	//Type::Rtti ArgTraits<void(*)(A)>::rtti = { ArgTraits<void(*)(A)>::prop,ArgTraits<void(*)(A)>::Params::TypeDesc::TypeName.Name,ArgTraits<void(*)(A)>::Params::TypeDesc::TypeName.Hash,TypeId::func,0,0,0 };
#define PRIVATE_ASSERT_VAR_ARGS_IMPL_COUNTER(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, N, ...) N
#define PRIVATE_ASSERT_VAR_ARGS_IMPLER(args)  PRIVATE_ASSERT_VAR_ARGS_IMPL_COUNTER args
#define PRIVATE_COUNT_ASSERT_VAR_ARGS(...)  PRIVATE_ASSERT_VAR_ARGS_IMPLER((__VA_ARGS__, 20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))
#define PRIVATE_INDEX_ASSERT_VAR_ARGS(...)  PRIVATE_ASSERT_VAR_ARGS_IMPLER((__VA_ARGS__,    19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))
#define PRIVATE_TRAITS_ARGS_GLUE(x, y) x y

#define DECL_TYPELIST_PARAMS1(A1) typedef TypeList <A1> Params;
#define DECL_TYPELIST_PARAMS2(A1,A2) typedef TypeList <A1, TypeList <A2>> Params;
#define DECL_TYPELIST_PARAMS3(A1,A2,A3) typedef TypeList <A1, TypeList <A2, TypeList <A3> > > Params;
#define DECL_TYPELIST_PARAMS4(A1,A2,A3,A4) typedef TypeList <A1, TypeList <A2, TypeList <A3, TypeList <A4>>>> Params;
#define DECL_TYPELIST_PARAMS5(A1,A2,A3,A4,A5) typedef TypeList <A1, TypeList <A2, TypeList <A3, TypeList <A4, TypeList <A5>>>>> Params;
#define DECL_TYPELIST_PARAMS6(A1,A2,A3,A4,A5,A6) typedef TypeList <A1, TypeList <A2, TypeList <A3, TypeList <A4, TypeList <A5, TypeList <A6>>>>>> Params;
#define DECL_TYPELIST_PARAMS7(A1,A2,A3,A4,A5,A6,A7) typedef TypeList <A1, TypeList <A2, TypeList <A3, TypeList <A4, TypeList <A5, TypeList <A6, TypeList <A7>>>>>>> Params;
#define DECL_TYPELIST_PARAMS8(A1,A2,A3,A4,A5,A6,A7,A8) typedef TypeList <A1, TypeList <A2, TypeList <A3, TypeList <A4, TypeList <A5, TypeList <A6, TypeList <A7, TypeList <A8>>>>>>>> Params;

#define PRIVATE_TYPELIST_CHOOSE_HELPER2(count)  DECL_TYPELIST_PARAMS##count
#define PRIVATE_TYPELIST_CHOOSE_HELPER1(count)  PRIVATE_TYPELIST_CHOOSE_HELPER2(count)
#define PRIVATE_TYPELIST_CHOOSE_HELPER(count)   PRIVATE_TYPELIST_CHOOSE_HELPER1(count)
#define DECL_TYPELIST_PARAMS(...) PRIVATE_TRAITS_ARGS_GLUE(PRIVATE_TYPELIST_CHOOSE_HELPER(PRIVATE_COUNT_ASSERT_VAR_ARGS(__VA_ARGS__)), (__VA_ARGS__))

#define DECL_ARGTRAITS_PROP_PARAMS1(A1)   { { &TClass<A1>::rtti,0 },BaseTypes::vNone };
#define DECL_ARGTRAITS_PROP_PARAMS2(A1,A2)  { {&TClass<A1>::rtti,0},{&TClass<A2>::rtti,0},BaseTypes::vNone};
#define DECL_ARGTRAITS_PROP_PARAMS3(A1,A2,A3)  { {&TClass<A1>::rtti,0},{&TClass<A2>::rtti,0},{&TClass<A3>::rtti,0},BaseTypes::vNone};
#define DECL_ARGTRAITS_PROP_PARAMS4(A1,A2,A3,A4)  { {&TClass<A1>::rtti,0},{&TClass<A2>::rtti,0},{&TClass<A3>::rtti,0},{&TClass<A4>::rtti,0},BaseTypes::vNone};
#define DECL_ARGTRAITS_PROP_PARAMS5(A1,A2,A3,A4,A5)  { {&TClass<A1>::rtti,0},{&TClass<A2>::rtti,0},{&TClass<A3>::rtti,0},{&TClass<A4>::rtti,0},{&TClass<A5>::rtti,0},BaseTypes::vNone};
#define DECL_ARGTRAITS_PROP_PARAMS6(A1,A2,A3,A4,A5,A6)  { {&TClass<A1>::rtti,0},{&TClass<A2>::rtti,0},{&TClass<A3>::rtti,0},{&TClass<A4>::rtti,0},{&TClass<A5>::rtti,0},{&TClass<A6>::rtti,0},BaseTypes::vNone};
#define DECL_ARGTRAITS_PROP_PARAMS7(A1,A2,A3,A4,A5,A6,A7)  { {&TClass<A1>::rtti,0},{&TClass<A2>::rtti,0},{&TClass<A3>::rtti,0},{&TClass<A4>::rtti,0},{&TClass<A5>::rtti,0},{&TClass<A6>::rtti,0},{&TClass<A7>::rtti,0},BaseTypes::vNone};
#define DECL_ARGTRAITS_PROP_PARAMS8(A1,A2,A3,A4,A5,A6,A7,A8) { {&TClass<A1>::rtti,0},{&TClass<A2>::rtti,0},{&TClass<A3>::rtti,0},{&TClass<A4>::rtti,0},{&TClass<A5>::rtti,0},{&TClass<A6>::rtti,0},{&TClass<A7>::rtti,0},{&TClass<A8>::rtti,0},BaseTypes::vNone};

#define PRIVATE_ARGTRAITS_PROP_CHOOSE_HELPER2(count)  DECL_ARGTRAITS_PROP_PARAMS##count
#define PRIVATE_ARGTRAITS_PROP_CHOOSE_HELPER1(count)  PRIVATE_ARGTRAITS_PROP_CHOOSE_HELPER2(count)
#define PRIVATE_ARGTRAITS_PROP_CHOOSE_HELPER(count)   PRIVATE_ARGTRAITS_PROP_CHOOSE_HELPER1(count)
#define DECL_ARGTRAITS_PROP_PARAMS(...)               PRIVATE_TRAITS_ARGS_GLUE(PRIVATE_ARGTRAITS_PROP_CHOOSE_HELPER(PRIVATE_COUNT_ASSERT_VAR_ARGS(__VA_ARGS__)), (__VA_ARGS__))

#define DECL_TEMPLATE_CLASS_PARAMS1(A1)  class A1
#define DECL_TEMPLATE_CLASS_PARAMS2(A1,A2) class A1, class A2
#define DECL_TEMPLATE_CLASS_PARAMS3(A1,A2,A3) class A1, class A2, class A3
#define DECL_TEMPLATE_CLASS_PARAMS4(A1,A2,A3,A4) class A1, class A2, class A3,class A4
#define DECL_TEMPLATE_CLASS_PARAMS5(A1,A2,A3,A4,A5) class A1, class A2, class A3,class A4, class A5
#define DECL_TEMPLATE_CLASS_PARAMS6(A1,A2,A3,A4,A5,A6) class A1, class A2, class A3,class A4, class A5, class A6
#define DECL_TEMPLATE_CLASS_PARAMS7(A1,A2,A3,A4,A5,A6,A7) class A1, class A2, class A3,class A4, class A5, class A6, class A7
#define DECL_TEMPLATE_CLASS_PARAMS8(A1,A2,A3,A4,A5,A6,A7,A8) class A1, class A2, class A3,class A4, class A5, class A6, class A7, class A8

#define PRIVATE_TYPENAME_CLASS_CHOOSE_HELPER2(count)  DECL_TEMPLATE_CLASS_PARAMS##count
#define PRIVATE_TYPENAME_CLASS_CHOOSE_HELPER1(count)  PRIVATE_TYPENAME_CLASS_CHOOSE_HELPER2(count)
#define PRIVATE_TYPENAME_CLASS_CHOOSE_HELPER(count)   PRIVATE_TYPENAME_CLASS_CHOOSE_HELPER1(count)
#define DECL_TEMPLATE_CLASS_PARAMS(...) PRIVATE_TRAITS_ARGS_GLUE(PRIVATE_TYPENAME_CLASS_CHOOSE_HELPER(PRIVATE_COUNT_ASSERT_VAR_ARGS(__VA_ARGS__)), (__VA_ARGS__))


#define DECL_ARG_TRAITS(...)			\
	template <DECL_TEMPLATE_CLASS_PARAMS(__VA_ARGS__)>		\
	struct ArgTraits<void(*)(__VA_ARGS__)>			\
	{										        \
		DECL_TYPELIST_PARAMS(__VA_ARGS__);	    \
		static BaseTypes  prop[PRIVATE_COUNT_ASSERT_VAR_ARGS(__VA_ARGS__) + 1];		\
		static Type::Rtti rtti;			    \
		static Type type() { return rtti; }	\
	};												                            \
	template <DECL_TEMPLATE_CLASS_PARAMS(__VA_ARGS__)>	                \
	BaseTypes ArgTraits<void(*)(__VA_ARGS__)>::prop[PRIVATE_COUNT_ASSERT_VAR_ARGS(__VA_ARGS__) + 1] = DECL_ARGTRAITS_PROP_PARAMS(__VA_ARGS__);           \
	template <DECL_TEMPLATE_CLASS_PARAMS(__VA_ARGS__)>						    \
	Type::Rtti ArgTraits<void(*)(__VA_ARGS__)>::rtti = { ArgTraits<void(*)(__VA_ARGS__)>::prop,ArgTraits<void(*)(__VA_ARGS__)>::Params::TypeDesc::TypeName.Name,ArgTraits<void(*)(__VA_ARGS__)>::Params::TypeDesc::TypeName.Hash,TypeId::func,0,0,0 };

	DECL_ARG_TRAITS(A1);
	DECL_ARG_TRAITS(A1,A2);
	DECL_ARG_TRAITS(A1, A2, A3);
	DECL_ARG_TRAITS(A1, A2, A3, A4);
	DECL_ARG_TRAITS(A1, A2, A3, A4, A5);
	DECL_ARG_TRAITS(A1, A2, A3, A4, A5, A6);
	DECL_ARG_TRAITS(A1, A2, A3, A4, A5, A6, A7);
	DECL_ARG_TRAITS(A1, A2, A3, A4, A5, A6, A7, A8);

	template <class F>
	struct FuncRtti {
		static BaseTypes prop[4];
		static Type::Rtti rtti;
	};
	template <class F>
	BaseTypes FuncRtti<F>::prop[4] = { { &F::TID::TArgsFuncRtti::rtti,0 },{ &F::TID::TArgsRawFuncRtti::rtti,0 },{ &F::TID::TArgsObjFuncRtti::rtti,0 },BaseTypes::vNone };
	template <class F>
	Type::Rtti FuncRtti<F>::rtti = { FuncRtti<F>::prop,F::TypeName.Name,F::TypeName.Hash,TypeId::func,0,0,0 };


	template <class MemFn, class D = MemFn>
	struct FuncTraits{};

	/* Ordinary function pointers. */
	//template <typename FN,typename RT,typename Params, typename R>
	//class TArgs0 : public Memory
	//{
	//public:
	//	DECL_TYPEDESC3(TClass<RT>::TypeDesc, Params::TypeDesc, typedesc1(zh_str2type("*")));
	//	static Type::BaseTypes prop[2];
	//	static Type::Rtti rtti;
	//};
	//template <typename FN, typename RT, typename Params, typename R>
	//Type::BaseTypes TArgs0<FN,RT,Params,R>::prop[2] = { { &TClass<R>::rtti,0 },Type::BaseTypes::vNone };
	//template <typename FN, typename RT, typename Params, typename R>
	//Type::Rtti TArgs0<FN,RT,Params,R>::rtti = { TArgs0<FN,RT,Params,R>::prop,TArgs0<FN,RT,Params,R>::TypeDesc::TypeName.Name,TArgs0<FN,RT,Params,R>::TypeDesc::TypeName.Hash,FN::_typeIndex,0,0,0 };
#define DECL_TARGS_N(TArg,FN,RT,Params,...)  \
	template <typename FN, typename RT, typename Params, DECL_TEMPLATE_CLASS_PARAMS(__VA_ARGS__)> \
	class TArg : public Memory  \
	{ \
	public: \
		DECL_TYPEDESC3(TClass<RT>::TypeDesc, Params::TypeDesc, internal::typedesc1<internal::Pointer>); \
		static zhihe::Type::BaseTypes prop[PRIVATE_COUNT_ASSERT_VAR_ARGS(__VA_ARGS__) + 1]; \
		static zhihe::Type::Rtti rtti; \
	}; \
	template <typename FN, typename RT, typename Params, DECL_TEMPLATE_CLASS_PARAMS(__VA_ARGS__)> \
	Type::BaseTypes TArg<FN, RT, Params, __VA_ARGS__>::prop[PRIVATE_COUNT_ASSERT_VAR_ARGS(__VA_ARGS__) + 1] = DECL_ARGTRAITS_PROP_PARAMS(__VA_ARGS__); \
	template <typename FN, typename RT, typename Params, DECL_TEMPLATE_CLASS_PARAMS(__VA_ARGS__)> \
	Type::Rtti TArg<FN, RT, Params, __VA_ARGS__>::rtti = { TArg<FN,RT,Params,__VA_ARGS__>::prop,TArg<FN,RT,Params,__VA_ARGS__>::TypeDesc::TypeName.Name,TArg<FN,RT,Params,__VA_ARGS__>::TypeDesc::TypeName.Hash,TypeId::func,0,0,0 };

	DECL_TARGS_N(TArgs0, FN, RT, Params, R);
	DECL_TARGS_N(TArgs1, FN, RT, Params, R, P1);
	DECL_TARGS_N(TArgs2, FN, RT, Params, R, P1,P2);
	DECL_TARGS_N(TArgs3, FN, RT, Params, R, P1,P2,P3);
	DECL_TARGS_N(TArgs4, FN, RT, Params, R, P1,P2,P3,P4);

	template <class R, class D>
	struct FuncTraits <R(*) () MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = false;
		const static TypeId TypeIndex = TypeId::func;

		typedef D DeclType;
		typedef R ReturnType;

		typedef TypeList<None> Params;
		typedef TypeList<None> RawParams;
		typedef TypeList<None> ObjParams;

		typedef ArgTraits<void(*)(None)> Traits;
		typedef ArgTraits<void(*)(None)> ObjTraits;
		typedef ArgTraits<void(*)(None)> RawTraits;

		typedef typename convertConstRef<R>::Type TR;
		typedef typename TClass<R>::obj_type OR;

		typedef R(*Func)(void);
		typedef TR(*RawFunc)(void);
		typedef OR(*ObjFunc)(void);

		typedef FuncTraits TID;
		typedef FuncRtti<FuncTraits> Rtti;
		typedef typename TClass<Func>::TypeDesc TypeDesc;

		typedef TArgs0<FuncTraits,R,  Params, TCls<R>> TArgsFuncRtti;
		typedef TArgs0<FuncTraits,TR, RawParams, TRaw<R>>  TArgsRawFuncRtti;
		typedef TArgs0<FuncTraits,OR, ObjParams,TClass<OR>> TArgsObjFuncRtti;

		static  Type type()
		{
			return &Rtti::rtti;
		}
		static R call(D fp, TypeListValues <Params> const&)
		{
			return fp();
		}
		static R raw_call(D fp, TypeListValues <RawParams> const&)
		{
			return fp();
		}
	};

	template <class R, class P1, class D>
	struct FuncTraits <R(*) (P1) MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = false;
		const static TypeId TypeIndex = TypeId::func;

		typedef D DeclType;
		typedef R ReturnType;

//		typedef typename removeConst<R>::Type RT;

		typedef typename convertConstRef<R>::Type  TR;
		typedef typename convertConstRef<P1>::Type T1;

		typedef typename TClass<R>::obj_type  OR;
		typedef typename TClass<T1>::obj_type O1;

		typedef TypeList <P1> Params;
		typedef TypeList <T1> RawParams;
		typedef TypeList <O1> ObjParams;

		typedef R(*Func)(P1);
		typedef TR(*RawFunc)(T1);
		typedef OR(*ObjFunc)(O1);

		typedef typename TClass<Func>::TypeDesc TypeDesc;
		typedef FuncTraits TID;
		typedef FuncRtti<FuncTraits> Rtti;

		typedef TArgs1<FuncTraits, R,  Params,    TCls<R>,P1> TArgsFuncRtti;
		typedef TArgs1<FuncTraits, TR, RawParams, TRaw<R>,T1>  TArgsRawFuncRtti;
		typedef TArgs1<FuncTraits, OR, ObjParams, TClass<OR>,T1> TArgsObjFuncRtti;

		static  Type type()
		{
			return &Rtti::rtti;
		}
		static R call(D fp, TypeListValues <Params> tvl)
		{
			return fp(tvl.hd);
		}
		static R raw_call(D fp, TypeListValues <RawParams> tvl)
		{
			return fp(tvl.hd);
		}
	};

	template <class R, class P1, class P2, class D>
	struct FuncTraits <R(*) (P1, P2) MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = false;
		typedef D DeclType;
		typedef R ReturnType;

		typedef typename removeConst<R>::Type      TR;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<P2>::Type T2;

		typedef typename TClass<R>::obj_type  OR;
		typedef typename TClass<T1>::obj_type O1;
		typedef typename TClass<T2>::obj_type O2;

		typedef TypeList <P1, TypeList <P2> > Params;
		typedef TypeList <T1, TypeList <T2> > RawParams;
		typedef TypeList <O1, TypeList <O2> > ObjParams;

		typedef R(*Func)(P1,P2);
		typedef TR(*RawFunc)(T1,T2);
		typedef OR(*ObjFunc)(O1,O2);

		typedef typename TClass<Func>::TypeDesc TypeDesc;
		typedef FuncTraits TID;
		typedef FuncRtti<FuncTraits> Rtti;

		typedef TArgs1<FuncTraits, R, Params, TCls<R>, P1> TArgsFuncRtti;
		typedef TArgs1<FuncTraits, TR, RawParams, TRaw<R>, T1>  TArgsRawFuncRtti;
		typedef TArgs1<FuncTraits, OR, ObjParams, TClass<OR>, T1> TArgsObjFuncRtti;

		static  Type type()
		{
			return &Rtti::rtti;
		}
		static R call(D fp, TypeListValues <Params> tvl)
		{
			return fp(tvl.hd, tvl.tl.hd);
		}
		static R raw_call(D fp, TypeListValues <RawParams> tvl)
		{
			return fp(tvl.hd, tvl.tl.hd);
		}
	};

	template <class R, class P1, class P2, class P3, class D>
	struct FuncTraits <R(*) (P1, P2, P3) MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = false;
		typedef D DeclType;
		typedef R ReturnType;

		typedef typename removeConst<R>::Type      TR;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<P2>::Type T2;
		typedef typename convertConstRef<P3>::Type T3;

		typedef typename TClass<R>::obj_type  OR;
		typedef typename TClass<T1>::obj_type O1;
		typedef typename TClass<T2>::obj_type O2;
		typedef typename TClass<T3>::obj_type O3;

		typedef TypeList <P1, TypeList <P2, TypeList <P3> > > Params;
		typedef TypeList <T1, TypeList <T2, TypeList <T3> > > RawParams;
		typedef TypeList <O1, TypeList <O2, TypeList <O3> > > ObjParams;

		typedef R(*Func)(P1, P2, P3);
		typedef TR(*RawFunc)(T1, T2, T3);
		typedef OR(*ObjFunc)(O1, O2, O3);

		typedef FuncTraits TID;
		typedef FuncRtti<FuncTraits> Rtti;
		typedef typename TClass<Func>::TypeDesc TypeDesc;

		typedef TArgs0<FuncTraits, R, Params, TCls<R>> TArgsFuncRtti;
		typedef TArgs0<FuncTraits, TR, RawParams, TRaw<R>>  TArgsRawFuncRtti;
		typedef TArgs0<FuncTraits, OR, ObjParams, TClass<OR>> TArgsObjFuncRtti;

		static  Type type()
		{
			return &Rtti::rtti;
		}

		static R call(D fp, TypeListValues <Params> tvl)
		{
			return fp(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd);
		}
		static R raw_call(D fp, TypeListValues <RawParams> tvl)
		{
			return fp(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd);
		}
	};

	template <class R, class P1, class P2, class P3, class P4, class D>
	struct FuncTraits <R(*) (P1, P2, P3, P4) MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = false;
		typedef D DeclType;
		typedef R ReturnType;

		typedef typename removeConst<R>::Type  TR;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<P2>::Type T2;
		typedef typename convertConstRef<P3>::Type T3;
		typedef typename convertConstRef<P4>::Type T4;

		typedef typename TClass<R>::obj_type  OR;
		typedef typename TClass<T1>::obj_type O1;
		typedef typename TClass<T2>::obj_type O2;
		typedef typename TClass<T3>::obj_type O3;
		typedef typename TClass<T4>::obj_type O4;

		typedef TypeList <P1, TypeList <P2, TypeList <P3, TypeList <P4> > > > Params;
		typedef TypeList <T1, TypeList <T2, TypeList <T3, TypeList <T4> > > > RawParams;
		typedef TypeList <O1, TypeList <O2, TypeList <O3, TypeList <O4> > > > ObjParams;

		typedef R(*Func)(P1, P2, P3, P4);
		typedef TR(*RawFunc)(T1, T2, T3, T4);
		typedef OR(*ObjFunc)(O1, O2, O3,O4);

		typedef FuncTraits TID;
		typedef FuncRtti<FuncTraits> Rtti;
		typedef typename TClass<Func>::TypeDesc TypeDesc;

		typedef TArgs0<FuncTraits, R, Params, TCls<R>> TArgsFuncRtti;
		typedef TArgs0<FuncTraits, TR, RawParams, TRaw<R>>  TArgsRawFuncRtti;
		typedef TArgs0<FuncTraits, OR, ObjParams, TClass<OR>> TArgsObjFuncRtti;

		static  Type type()
		{
			return &Rtti::rtti;
		}
		static R call(D fp, TypeListValues <Params> tvl)
		{
			return fp(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd);
		}
		static R raw_call(D fp, TypeListValues <RawParams> tvl)
		{
			return fp(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd);
		}
	};

	template <class R, class P1, class P2, class P3, class P4, class P5, class D>
	struct FuncTraits <R(*) (P1, P2, P3, P4, P5) MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = false;
		typedef D DeclType;
		typedef R ReturnType;
		typedef typename removeConst<R>::Type  TR;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<P2>::Type T2;
		typedef typename convertConstRef<P3>::Type T3;
		typedef typename convertConstRef<P4>::Type T4;
		typedef typename convertConstRef<P5>::Type T5;

		typedef typename TClass<R>::obj_type  OR;
		typedef typename TClass<T1>::obj_type O1;
		typedef typename TClass<T2>::obj_type O2;
		typedef typename TClass<T3>::obj_type O3;
		typedef typename TClass<T4>::obj_type O4;
		typedef typename TClass<T5>::obj_type O5;

		typedef TypeList <P1, TypeList <P2, TypeList <P3, TypeList <P4, TypeList <P5> > > > > Params;
		typedef TypeList <T1, TypeList <T2, TypeList <T3, TypeList <T4, TypeList <T5> > > > > RawParams;
		typedef TypeList <O1, TypeList <O2, TypeList <O3, TypeList <O4, TypeList <O5> > > > > ObjParams;

		typedef R(*Func)(P1, P2, P3, P4, P5);
		typedef TR(*RawFunc)(T1, T2, T3, T4, T5);
		typedef OR(*ObjFunc)(O1, O2, O3, O4,O5);

		typedef FuncTraits TID;
		typedef FuncRtti<FuncTraits> Rtti;
		typedef typename TClass<Func>::TypeDesc TypeDesc;

		typedef TArgs0<FuncTraits, R, Params, TCls<R>> TArgsFuncRtti;
		typedef TArgs0<FuncTraits, TR, RawParams, TRaw<R>>  TArgsRawFuncRtti;
		typedef TArgs0<FuncTraits, OR, ObjParams, TClass<OR>> TArgsObjFuncRtti;

		static  Type type()
		{
			return &Rtti::rtti;
		}
		static R call(D fp, TypeListValues <Params> tvl)
		{
			return fp(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd);
		}
		static R raw_call(D fp, TypeListValues <RawParams> tvl)
		{
			return fp(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd);
		}
	};

	template <class R, class P1, class P2, class P3, class P4, class P5, class P6, class D>
	struct FuncTraits <R(*) (P1, P2, P3, P4, P5, P6) MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = false;
		typedef D DeclType;
		typedef R ReturnType;
		typedef typename removeConst<R>::Type  TR;
		typedef typename  convertConstRef<P1>::Type T1;
		typedef typename  convertConstRef<P2>::Type T2;
		typedef typename  convertConstRef<P3>::Type T3;
		typedef typename  convertConstRef<P4>::Type T4;
		typedef typename  convertConstRef<P5>::Type T5;
		typedef typename  convertConstRef<P5>::Type T6;

		typedef typename TClass<R>::obj_type OR;
		typedef typename TClass<T1>::obj_type O1;
		typedef typename TClass<T2>::obj_type O2;
		typedef typename TClass<T3>::obj_type O3;
		typedef typename TClass<T4>::obj_type O4;
		typedef typename TClass<T5>::obj_type O5;
		typedef typename TClass<T6>::obj_type O6;

		typedef TypeList <P1, TypeList <P2, TypeList <P3, TypeList <P4, TypeList <P5, TypeList <P6> > > > > > Params;
		typedef TypeList <T1, TypeList <T2, TypeList <T3, TypeList <T4, TypeList <T5, TypeList <T6> > > > > > RawParams;
		typedef TypeList <O1, TypeList <O2, TypeList <O3, TypeList <O4, TypeList <O5, TypeList <O6> > > > > > ObjParams;

		typedef R(*Func)(P1, P2, P3, P4, P5, P6);
		typedef TR(*RawFunc)(T1, T2, T3, T4, T5, T6);
		typedef OR(*ObjFunc)(O1, O2, O3, O4, O5,O6);

		typedef FuncTraits TID;
		typedef FuncRtti<FuncTraits> Rtti;
		typedef typename TClass<Func>::TypeDesc TypeDesc;

		typedef TArgs0<FuncTraits, R, Params, TCls<R>> TArgsFuncRtti;
		typedef TArgs0<FuncTraits, TR, RawParams, TRaw<R>>  TArgsRawFuncRtti;
		typedef TArgs0<FuncTraits, OR, ObjParams, TClass<OR>> TArgsObjFuncRtti;

		static  Type type()
		{
			return &Rtti::rtti;
		}

		static R call(D fp, TypeListValues <Params> tvl)
		{
			return fp(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.hd);
		}
		static R raw_call(D fp, TypeListValues <RawParams> tvl)
		{
			return fp(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.hd);
		}
	};

	template <class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class D>
	struct FuncTraits <R(*) (P1, P2, P3, P4, P5, P6, P7) MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = false;
		typedef D DeclType;
		typedef R ReturnType;
		typedef typename removeConst<R>::Type  TR;
		typedef typename  convertConstRef<P1>::Type T1;
		typedef typename  convertConstRef<P2>::Type T2;
		typedef typename  convertConstRef<P3>::Type T3;
		typedef typename  convertConstRef<P4>::Type T4;
		typedef typename  convertConstRef<P5>::Type T5;
		typedef typename  convertConstRef<P5>::Type T6;
		typedef typename  convertConstRef<P7>::Type T7;

		typedef typename TClass<R>::obj_type OR;
		typedef typename TClass<T1>::obj_type O1;
		typedef typename TClass<T2>::obj_type O2;
		typedef typename TClass<T3>::obj_type O3;
		typedef typename TClass<T4>::obj_type O4;
		typedef typename TClass<T5>::obj_type O5;
		typedef typename TClass<T6>::obj_type O6;
		typedef typename TClass<T7>::obj_type O7;

		typedef TypeList <P1, TypeList <P2, TypeList <P3, TypeList <P4, TypeList <P5, TypeList <P6, TypeList <P7> > > > > > > Params;
		typedef TypeList <T1, TypeList <T2, TypeList <T3, TypeList <T4, TypeList <T5, TypeList <T6, TypeList <T7> > > > > > > RawParams;
		typedef TypeList <O1, TypeList <O2, TypeList <O3, TypeList <O4, TypeList <O5, TypeList <O6, TypeList <O7 > > > > > > > ObjParams;

		typedef R(*Func)(P1, P2, P3, P4, P5, P6, P7);
		typedef TR(*RawFunc)(T1, T2, T3, T4, T5, T6, T7);
		typedef OR(*ObjFunc)(O1, O2, O3, O4, O5, O6,O7);

		typedef FuncTraits TID;
		typedef FuncRtti<FuncTraits> Rtti;
		typedef typename TClass<Func>::TypeDesc TypeDesc;

		typedef TArgs0<FuncTraits, R, Params, TCls<R>> TArgsFuncRtti;
		typedef TArgs0<FuncTraits, TR, RawParams, TRaw<R>>  TArgsRawFuncRtti;
		typedef TArgs0<FuncTraits, OR, ObjParams, TClass<OR>> TArgsObjFuncRtti;

		static  Type type()
		{
			return &Rtti::rtti;
		}
		static R call(D fp, TypeListValues <Params> tvl)
		{
			return fp(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.tl.hd);
		}
		static R raw_call(D fp, TypeListValues <RawParams> tvl)
		{
			return fp(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.tl.hd);
		}
	};

	template <class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class D>
	struct FuncTraits <R(*) (P1, P2, P3, P4, P5, P6, P7, P8) MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = false;
		typedef D DeclType;
		typedef R ReturnType;
		typedef typename removeConst<R>::Type TR;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<P2>::Type T2;
		typedef typename convertConstRef<P3>::Type T3;
		typedef typename convertConstRef<P4>::Type T4;
		typedef typename convertConstRef<P5>::Type T5;
		typedef typename convertConstRef<P5>::Type T6;
		typedef typename convertConstRef<P7>::Type T7;
		typedef typename convertConstRef<P8>::Type T8;

		typedef typename TClass<R>::obj_type OR;
		typedef typename TClass<T1>::obj_type O1;
		typedef typename TClass<T2>::obj_type O2;
		typedef typename TClass<T3>::obj_type O3;
		typedef typename TClass<T4>::obj_type O4;
		typedef typename TClass<T5>::obj_type O5;
		typedef typename TClass<T6>::obj_type O6;
		typedef typename TClass<T7>::obj_type O7;
		typedef typename TClass<T8>::obj_type O8;

		typedef TypeList <P1, TypeList <P2, TypeList <P3, TypeList <P4, TypeList <P5, TypeList <P6, TypeList <P7, TypeList <P8> > > > > > > > Params;
		typedef TypeList <T1, TypeList <T2, TypeList <T3, TypeList <T4, TypeList <T5, TypeList <T6, TypeList <T7, TypeList <T8> > > > > > > > RawParams;
		typedef TypeList <O1, TypeList <O2, TypeList <O3, TypeList <O4, TypeList <O5, TypeList <O6, TypeList <O7, TypeList <O8> > > > > > > > ObjParams;

		typedef R(*Func)(P1, P2, P3,P4,P5,P6,P7,P8);
		typedef TR(*RawFunc)(T1, T2, T3, T4, T5, T6, T7, T8);
		typedef OR(*ObjFunc)(O1, O2, O3, O4, O5, O6, O7,O8);

		typedef FuncTraits TID;
		typedef FuncRtti<FuncTraits> Rtti;
		typedef typename TClass<Func>::TypeDesc TypeDesc;

		typedef TArgs0<FuncTraits, R, Params, TCls<R>> TArgsFuncRtti;
		typedef TArgs0<FuncTraits, TR, RawParams, TRaw<R>>  TArgsRawFuncRtti;
		typedef TArgs0<FuncTraits, OR, ObjParams, TClass<OR>> TArgsObjFuncRtti;

		static  Type type()
		{
			return &Rtti::rtti;
		}
		static R call(D fp, TypeListValues <Params> tvl)
		{
			return fp(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.tl.tl.hd);
		}
		static R raw_call(D fp, TypeListValues <RawParams> tvl)
		{
			return fp(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.tl.tl.hd);
		}
	};

	/* Non-const member function pointers with THROWSPEC. */

	template <class T, class R, class D>
	struct FuncTraits <R(T::*) () MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = true;
		static bool const isConstMemberFunction = false;
		typedef D DeclType;
		typedef T ClassType;
		typedef R ReturnType;

		typedef typename convertConstRef<R>::Type TR;

		typedef R(*Func)(void);
		typedef TR(*RawFunc)(void);
		typedef R(T::*MemberFunc)(void);
		typedef TR(T::*RawMemberFunc)(void);

		typedef FuncTraits<Func> CFuncTraits;
		typedef FuncTraits<RawFunc> RFuncTraits;
		typedef typename FuncTraits<Func>::Params Params;
		typedef typename FuncTraits<Func>::RawParams RawParams;
		typedef typename FuncTraits<Func>::ObjParams ObjParams;

		typedef FuncTraits<Func> TID;
		typedef typename TClass<RawMemberFunc>::TypeDesc TypeDesc;

		static Type type()
		{
			return &FuncRtti<FuncTraits>::rtti;
		}
		static R call(T* obj, D fp, TypeListValues <Params> const&)
		{
			return (obj->*fp)();
		}
		static R raw_call(T* obj, D fp, TypeListValues <RawParams> const&)
		{
			return (obj->*fp)();
		}
	};

	template <class T, class R, class P1, class D>
	struct FuncTraits <R(T::*) (P1) MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = true;
		static bool const isConstMemberFunction = false;
		typedef D DeclType;
		typedef T ClassType;
		typedef R ReturnType;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<R>::Type TR;

		typedef R(*Func)(P1);
		typedef TR(*RawFunc)(T1);
		typedef R(T::*MemberFunc)(P1);
		typedef TR(T::*RawMemberFunc)(T1);

		typedef FuncTraits<Func> CFuncTraits;
		typedef FuncTraits<RawFunc> RFuncTraits;

		typedef typename FuncTraits<Func>::Params Params;
		typedef typename FuncTraits<Func>::RawParams RawParams;
		typedef typename FuncTraits<Func>::ObjParams ObjParams;

		typedef typename TClass<RawMemberFunc>::TypeDesc TypeDesc;
		typedef FuncTraits<Func> TID;

		static  Type type()
		{
			return FuncRtti<FuncTraits>::rtti;
		}
		static R call(T* obj, D fp, TypeListValues <Params> tvl)
		{
			return (obj->*fp)(tvl.hd);
		}
		static R raw_call(T* obj, D fp, TypeListValues <RawParams> tvl)
		{
			return (obj->*fp)(tvl.hd);
		}
	};

	template <class T, class R, class P1, class P2, class D>
	struct FuncTraits <R(T::*) (P1, P2) MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = true;
		static bool const isConstMemberFunction = false;
		typedef D DeclType;
		typedef T ClassType;
		typedef R ReturnType;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<P2>::Type T2;
		typedef typename convertConstRef<R>::Type  TR;

		typedef R(*Func)(P1, P2);
		typedef TR(*RawFunc)(T1, T2);
		typedef R(T::*MemberFunc)(P1,P2);
		typedef TR(T::*RawMemberFunc)(T1,T2);

		typedef FuncTraits<Func> CFuncTraits;
		typedef FuncTraits<RawFunc> RFuncTraits;
		typedef typename FuncTraits<Func>::Params Params;
		typedef typename FuncTraits<Func>::RawParams RawParams;
		typedef typename FuncTraits<Func>::ObjParams ObjParams;

		typedef FuncTraits<Func> TID;
		typedef typename TClass<RawMemberFunc>::TypeDesc TypeDesc;

		static Type type()
		{
			return &FuncRtti<FuncTraits>::rtti;
		}
		static R call(T* obj, D fp, TypeListValues <Params> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd);
		}
		static R raw_call(T* obj, D fp, TypeListValues <RawParams> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd);
		}
	};

	template <class T, class R, class P1, class P2, class P3, class D>
	struct FuncTraits <R(T::*) (P1, P2, P3) MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = true;
		static bool const isConstMemberFunction = false;
		typedef D DeclType;
		typedef T ClassType;
		typedef R ReturnType;

		typedef typename convertConstRef<R>::Type TR;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<P2>::Type T2;
		typedef typename convertConstRef<P3>::Type T3;

		typedef R(*Func)(P1, P2, P3);
		typedef TR(*RawFunc)(T1, T2, T3);
		typedef R(T::*MemberFunc)(P1, P2, P3);
		typedef TR(T::*RawMemberFunc)(T1, T2,T3);

		typedef FuncTraits<Func> CFuncTraits;
		typedef FuncTraits<RawFunc> RFuncTraits;
		typedef typename FuncTraits<Func>::Params Params;
		typedef typename FuncTraits<Func>::RawParams RawParams;
		typedef typename FuncTraits<Func>::ObjParams ObjParams;

		typedef FuncTraits<Func> TID;
		typedef typename TClass<RawMemberFunc>::TypeDesc TypeDesc;

		static Type type()
		{
			return &FuncRtti<FuncTraits>::rtti;
		}
		static R call(T* obj, D fp, TypeListValues <Params> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd);
		}
		static R raw_call(T* obj, D fp, TypeListValues <RawParams> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd);
		}
	};

	template <class T, class R, class P1, class P2, class P3, class P4, class D>
	struct FuncTraits <R(T::*) (P1, P2, P3, P4) MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = true;
		static bool const isConstMemberFunction = false;
		typedef D DeclType;
		typedef T ClassType;
		typedef R ReturnType;

		typedef typename convertConstRef<R>::Type TR;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<P2>::Type T2;
		typedef typename convertConstRef<P3>::Type T3;
		typedef typename convertConstRef<P4>::Type T4;

		typedef R(*Func)(P1, P2, P3, P4);
		typedef TR(*RawFunc)(T1, T2, T3, T4);
		typedef R(T::*MemberFunc)(P1, P2, P3, P4);
		typedef TR(T::*RawMemberFunc)(T1, T2, T3, T4);

		typedef FuncTraits<Func> CFuncTraits;
		typedef FuncTraits<RawFunc> RFuncTraits;
		typedef typename FuncTraits<Func>::Params Params;
		typedef typename FuncTraits<Func>::RawParams RawParams;
		typedef typename FuncTraits<Func>::ObjParams ObjParams;

		typedef FuncTraits<Func> TID;
		typedef typename TClass<RawMemberFunc>::TypeDesc TypeDesc;

		static Type type()
		{
			return &FuncRtti<FuncTraits>::rtti;
		}

		static R call(T* obj, D fp, TypeListValues <Params> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd);
		}
		static R raw_call(T* obj, D fp, TypeListValues <RawParams> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd);
		}
	};

	template <class T, class R, class P1, class P2, class P3, class P4, class P5, class D>
	struct FuncTraits <R(T::*) (P1, P2, P3, P4, P5) MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = true;
		static bool const isConstMemberFunction = false;
		typedef D DeclType;
		typedef T ClassType;
		typedef R ReturnType;
		typedef typename convertConstRef<R>::Type TR;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<P2>::Type T2;
		typedef typename convertConstRef<P3>::Type T3;
		typedef typename convertConstRef<P4>::Type T4;
		typedef typename convertConstRef<P5>::Type T5;

		typedef R(*Func)(P1, P2, P3, P4, P5);
		typedef TR(*RawFunc)(T1, T2, T3, T4, T5);
		typedef R(T::*MemberFunc)(P1, P2, P3, P4, P5);
		typedef TR(T::*RawMemberFunc)(T1, T2, T3, T4,T5);

		typedef FuncTraits<Func> CFuncTraits;
		typedef FuncTraits<RawFunc> RFuncTraits;
		typedef typename FuncTraits<Func>::Params Params;
		typedef typename FuncTraits<Func>::RawParams RawParams;
		typedef typename FuncTraits<Func>::ObjParams ObjParams;

		typedef FuncTraits<Func> TID;
		typedef typename TClass<RawMemberFunc>::TypeDesc TypeDesc;

		static Type type()
		{
			return &FuncRtti<FuncTraits>::rtti;
		}

		static R call(T* obj, D fp, TypeListValues <Params> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd);
		}
		static R raw_call(T* obj, D fp, TypeListValues <RawParams> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd);
		}
	};

	template <class T, class R, class P1, class P2, class P3, class P4, class P5, class P6, class D>
	struct FuncTraits <R(T::*) (P1, P2, P3, P4, P5, P6) MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = true;
		static bool const isConstMemberFunction = false;
		typedef D DeclType;
		typedef T ClassType;
		typedef R ReturnType;
		typedef typename convertConstRef<R>::Type TR;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<P2>::Type T2;
		typedef typename convertConstRef<P3>::Type T3;
		typedef typename convertConstRef<P4>::Type T4;
		typedef typename convertConstRef<P5>::Type T5;
		typedef typename convertConstRef<P5>::Type T6;

		typedef R(*Func)(P1, P2, P3, P4, P5, P6);
		typedef TR(*RawFunc)(T1, T2, T3, T4, T5, T6);
		typedef R(T::*MemberFunc)(P1, P2, P3, P4, P5, P6);
		typedef TR(T::*RawMemberFunc)(T1, T2, T3, T4, T5,T6);

		typedef FuncTraits<Func> CFuncTraits;
		typedef FuncTraits<RawFunc> RFuncTraits;
		typedef typename FuncTraits<Func>::Params Params;
		typedef typename FuncTraits<Func>::RawParams RawParams;
		typedef typename FuncTraits<Func>::ObjParams ObjParams;

		typedef FuncTraits<Func> TID;
		typedef typename TClass<RawMemberFunc>::TypeDesc TypeDesc;

		static Type type()
		{
			return &FuncRtti<FuncTraits>::rtti;
		}
		static R call(T* obj, D fp, TypeListValues <Params> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.hd);
		}
		static R raw_call(T* obj, D fp, TypeListValues <RawParams> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.hd);
		}
	};

	template <class T, class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class D>
	struct FuncTraits <R(T::*) (P1, P2, P3, P4, P5, P6, P7) MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = true;
		static bool const isConstMemberFunction = false;
		typedef D DeclType;
		typedef T ClassType;
		typedef R ReturnType;
		typedef typename convertConstRef<P1>::Type TR;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<P2>::Type T2;
		typedef typename convertConstRef<P3>::Type T3;
		typedef typename convertConstRef<P4>::Type T4;
		typedef typename convertConstRef<P5>::Type T5;
		typedef typename convertConstRef<P5>::Type T6;
		typedef typename convertConstRef<P7>::Type T7;

		typedef R(*Func)(P1, P2, P3, P4, P5, P6, P7);
		typedef TR(*RawFunc)(T1, T2, T3, T4, T5, T6, T7);
		typedef R(T::*MemberFunc)(P1, P2, P3, P4, P5, P6,P7);
		typedef TR(T::*RawMemberFunc)(T1, T2, T3, T4, T5, T6,T7);

		typedef FuncTraits<Func> CFuncTraits;
		typedef FuncTraits<RawFunc> RFuncTraits;
		typedef typename FuncTraits<Func>::Params Params;
		typedef typename FuncTraits<Func>::RawParams RawParams;
		typedef typename FuncTraits<Func>::ObjParams ObjParams;

		typedef FuncTraits<Func> TID;
		typedef typename TClass<RawMemberFunc>::TypeDesc TypeDesc;

		static Type type()
		{
			return &FuncRtti<FuncTraits>::rtti;
		}
		static R call(T* obj, D fp, TypeListValues <Params> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.tl.hd);
		}
		static R raw_call(T* obj, D fp, TypeListValues <RawParams> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.tl.hd);
		}
	};

	template <class T, class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class D>
	struct FuncTraits <R(T::*) (P1, P2, P3, P4, P5, P6, P7, P8) MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = true;
		static bool const isConstMemberFunction = false;
		typedef D DeclType;
		typedef T ClassType;
		typedef R ReturnType;
		typedef typename convertConstRef<R>::Type TR;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<P2>::Type T2;
		typedef typename convertConstRef<P3>::Type T3;
		typedef typename convertConstRef<P4>::Type T4;
		typedef typename convertConstRef<P5>::Type T5;
		typedef typename convertConstRef<P5>::Type T6;
		typedef typename convertConstRef<P7>::Type T7;
		typedef typename convertConstRef<P8>::Type T8;

		typedef R(*Func)(P1, P2, P3, P4, P5, P6, P7, P8);
		typedef TR(*RawFunc)(T1, T2, T3, T4, T5, T6, T7, T8);
		typedef R(T::*MemberFunc)(P1, P2, P3, P4, P5, P6, P7,P8);
		typedef TR(T::*RawMemberFunc)(T1, T2, T3, T4, T5, T6, T7,T8);

		typedef FuncTraits<Func> CFuncTraits;
		typedef FuncTraits<RawFunc> RFuncTraits;
		typedef typename FuncTraits<Func>::Params Params;
		typedef typename FuncTraits<Func>::RawParams RawParams;
		typedef typename FuncTraits<Func>::ObjParams ObjParams;

		typedef FuncTraits<Func> TID;
		typedef typename TClass<RawMemberFunc>::TypeDesc TypeDesc;

		static Type type()
		{
			return &FuncRtti<FuncTraits>::rtti;
		}
		static R call(T* obj, D fp, TypeListValues <Params> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.tl.tl.hd);
		}
		static R raw_call(T* obj, D fp, TypeListValues <RawParams> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.tl.tl.hd);
		}
	};

	/* Const member function pointers with THROWSPEC. */

	template <class T, class R, class D>
	struct FuncTraits <R(T::*) () const MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = true;
		static bool const isConstMemberFunction = true;
		typedef D DeclType;
		typedef T ClassType;
		typedef R ReturnType;

		typedef typename convertConstRef<R>::Type TR;

		typedef R(*Func)(void);
		typedef TR(*RawFunc)(void);
		typedef R(T::*MemberFunc)(void)const;
		typedef TR(T::*RawMemberFunc)(void)const;

		typedef typename zhihe::FuncTraits<Func> CFuncTraits;
		typedef typename zhihe::FuncTraits<RawFunc> RFuncTraits;
		typedef typename zhihe::FuncTraits<Func>::Params Params;
		typedef typename zhihe::FuncTraits<Func>::RawParams RawParams;
		typedef typename zhihe::FuncTraits<Func>::ObjParams ObjParams;

		typedef typename TClass<RawMemberFunc>::TypeDesc TypeDesc;
		typedef FuncTraits<Func> TID;

		static  Type type()
		{
			return &FuncRtti<FuncTraits>::rtti;
		}
		static R call(T const* obj, D fp, TypeListValues <Params>)
		{
			return (obj->*fp)();
		}
		static R raw_call(T const* obj, D fp, TypeListValues <RawParams>)
		{
			return (obj->*fp)();
		}
	};

	template <class T, class R, class P1, class D>
	struct FuncTraits <R(T::*) (P1) const MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = true;
		static bool const isConstMemberFunction = true;
		typedef D DeclType;
		typedef T ClassType;
		typedef R ReturnType;
		typedef typename convertConstRef<R>::Type TR;
		typedef typename convertConstRef<P1>::Type T1;

		typedef R(*Func)(P1);
		typedef TR(*RawFunc)(T1);
		typedef R(T::*MemberFunc)(P1)const;
		typedef TR(T::*RawMemberFunc)(T1)const;

		typedef typename zhihe::FuncTraits<Func> CFuncTraits;
		typedef typename zhihe::FuncTraits <Func>::Params Params;
		typedef typename zhihe::FuncTraits <Func>::RawParams RawParams;
		typedef typename zhihe::FuncTraits <Func>::ObjParams ObjParams;
		typedef typename TClass<RawMemberFunc>::TypeDesc TypeDesc;
		typedef FuncTraits<Func> TID;

		static  const Type type()
		{
			return &FuncRtti<FuncTraits>::rtti;
		}
		static R call(T const* obj, D fp, TypeListValues <Params> tvl)
		{
			return (obj->*fp)(tvl.hd);
		}
		static R raw_call(T const* obj, D fp, TypeListValues <RawParams> tvl)
		{
			return (obj->*fp)(tvl.hd);
		}
	};

	template <class T, class R, class P1, class P2, class D>
	struct FuncTraits <R(T::*) (P1, P2) const MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = true;
		static bool const isConstMemberFunction = true;
		typedef D DeclType;
		typedef T ClassType;
		typedef R ReturnType;
		typedef typename convertConstRef<R>::Type TR;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<P2>::Type T2;

		typedef R(*Func)(P1, P2);
		typedef TR(*RawFunc)(T1, T2);
		typedef R(T::*MemberFunc)(P1,P2)const;
		typedef TR(T::*RawMemberFunc)(T1,T2)const;

		typedef typename zhihe::FuncTraits<Func> CFuncTraits;
		typedef typename zhihe::FuncTraits <Func>::Params Params;
		typedef typename zhihe::FuncTraits <Func>::RawParams RawParams;
		typedef typename zhihe::FuncTraits <Func>::ObjParams ObjParams;
		typedef typename TClass<RawMemberFunc>::TypeDesc TypeDesc;
		typedef FuncTraits<Func> TID;

		static  const Type type()
		{
			return &FuncRtti<FuncTraits>::rtti;
		}
		static R call(T const* obj, D fp, TypeListValues <Params> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd);
		}
		static R raw_call(T const* obj, D fp, TypeListValues <RawParams> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd);
		}
	};

	template <class T, class R, class P1, class P2, class P3, class D>
	struct FuncTraits <R(T::*) (P1, P2, P3) const MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = true;
		static bool const isConstMemberFunction = true;
		typedef D DeclType;
		typedef T ClassType;
		typedef R ReturnType;
		typedef typename convertConstRef<R>::Type TR;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<P2>::Type T2;
		typedef typename convertConstRef<P3>::Type T3;
		typedef R(*Func)(P1, P2, P3);
		typedef TR(*RawFunc)(T1, T2, T3);
		typedef R(T::*MemberFunc)(P1,P2, P3)const;
		typedef TR(T::*RawMemberFunc)(T1, T2, T3)const;

		typedef typename zhihe::FuncTraits<Func> CFuncTraits;
		typedef typename zhihe::FuncTraits <Func>::Params Params;
		typedef typename zhihe::FuncTraits <Func>::RawParams RawParams;
		typedef typename zhihe::FuncTraits <Func>::ObjParams ObjParams;
		typedef typename TClass<RawMemberFunc>::TypeDesc TypeDesc;
		typedef FuncTraits<Func> TID;

		static  const Type type()
		{
			return &FuncRtti<FuncTraits>::rtti;
		}
		static R call(T const* obj, D fp, TypeListValues <Params> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd);
		}
		static R raw_call(T const* obj, D fp, TypeListValues <RawParams> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd);
		}
	};

	template <class T, class R, class P1, class P2, class P3, class P4, class D>
	struct FuncTraits <R(T::*) (P1, P2, P3, P4) const MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = true;
		static bool const isConstMemberFunction = true;
		typedef D DeclType;
		typedef T ClassType;
		typedef R ReturnType;
		typedef typename convertConstRef<R>::Type TR;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<P2>::Type T2;
		typedef typename convertConstRef<P3>::Type T3;
		typedef typename convertConstRef<P4>::Type T4;

		typedef R(*Func)(P1, P2, P3, P4);
		typedef TR(*RawFunc)(T1, T2, T3, T4);
		typedef R(T::*MemberFunc)(P1, P2, P3, P3,P4)const;
		typedef TR(T::*RawMemberFunc)(T1, T2, T3, T4)const;

		typedef typename zhihe::FuncTraits<Func> CFuncTraits;
		typedef typename zhihe::FuncTraits <Func>::Params Params;
		typedef typename zhihe::FuncTraits <Func>::RawParams RawParams;
		typedef typename zhihe::FuncTraits <Func>::ObjParams ObjParams;
		typedef typename TClass<RawMemberFunc>::TypeDesc TypeDesc;
		typedef FuncTraits<Func> TID;

		static  const Type type()
		{
			return &FuncRtti<FuncTraits>::rtti;
		}
		static R call(T const* obj, D fp, TypeListValues <Params> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd);
		}
		static R raw_call(T const* obj, D fp, TypeListValues <RawParams> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd);
		}
	};

	template <class T, class R, class P1, class P2, class P3, class P4, class P5, class D>
	struct FuncTraits <R(T::*) (P1, P2, P3, P4, P5) const MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = true;
		static bool const isConstMemberFunction = true;
		typedef D DeclType;
		typedef T ClassType;
		typedef R ReturnType;
		typedef typename convertConstRef<R>::Type TR;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<P2>::Type T2;
		typedef typename convertConstRef<P3>::Type T3;
		typedef typename convertConstRef<P4>::Type T4;
		typedef typename convertConstRef<P5>::Type T5;
		typedef R(*Func)(P1, P2, P3, P4, P5);
		typedef TR(*RawFunc)(T1, T2, T3, T4, T5);
		typedef R(T::*MemberFunc)(P1, P2, P3, P4, P5)const;
		typedef TR(T::*RawMemberFunc)(T1, T2, T3, T4, T5)const;

		typedef typename zhihe::FuncTraits<Func> CFuncTraits;
		typedef typename zhihe::FuncTraits <Func>::Params Params;
		typedef typename zhihe::FuncTraits <Func>::RawParams RawParams;
		typedef typename zhihe::FuncTraits <Func>::ObjParams ObjParams;
		typedef typename TClass<RawMemberFunc>::TypeDesc TypeDesc;
		typedef FuncTraits<Func> TID;

		static  const Type type()
		{
			return &FuncRtti<FuncTraits>::rtti;
		}
		static R call(T const* obj, D fp, TypeListValues <Params> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd,
				tvl.tl.tl.tl.tl.hd);
		}
		static R raw_call(T const* obj, D fp, TypeListValues <RawParams> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd,
				tvl.tl.tl.tl.tl.hd);
		}
	};

	template <class T, class R, class P1, class P2, class P3, class P4, class P5, class P6, class D>
	struct FuncTraits <R(T::*) (P1, P2, P3, P4, P5, P6) const MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = true;
		static bool const isConstMemberFunction = true;
		typedef D DeclType;
		typedef T ClassType;
		typedef R ReturnType;
		typedef typename convertConstRef<R>::Type TR;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<P2>::Type T2;
		typedef typename convertConstRef<P3>::Type T3;
		typedef typename convertConstRef<P4>::Type T4;
		typedef typename convertConstRef<P5>::Type T5;
		typedef typename convertConstRef<P5>::Type T6;
		typedef R(*Func)(P1, P2, P3, P4, P5, P6);
		typedef TR(*RawFunc)(T1, T2, T3, T4, T5, T6);
		typedef R(T::*MemberFunc)(P1, P2, P3, P4, P5,P6)const;
		typedef TR(T::*RawMemberFunc)(T1, T2, T3, T4, T5,T6)const;

		typedef typename zhihe::FuncTraits<Func> CFuncTraits;
		typedef typename zhihe::FuncTraits <Func>::Params Params;
		typedef typename zhihe::FuncTraits <Func>::RawParams RawParams;
		typedef typename zhihe::FuncTraits <Func>::ObjParams ObjParams;
		typedef typename TClass<RawMemberFunc>::TypeDesc TypeDesc;
		typedef FuncTraits<Func> TID;

		static  const Type type()
		{
			return &FuncRtti<FuncTraits>::rtti;
		}
		static R call(T const* obj, D fp, TypeListValues <Params> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.hd);
		}
		static R raw_call(T const* obj, D fp, TypeListValues <RawParams> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.hd);
		}
	};

	template <class T, class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class D>
	struct FuncTraits <R(T::*) (P1, P2, P3, P4, P5, P6, P7) const MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = true;
		static bool const isConstMemberFunction = true;
		typedef D DeclType;
		typedef T ClassType;
		typedef R ReturnType;
		typedef typename convertConstRef<R>::Type TR;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<P2>::Type T2;
		typedef typename convertConstRef<P3>::Type T3;
		typedef typename convertConstRef<P4>::Type T4;
		typedef typename convertConstRef<P5>::Type T5;
		typedef typename convertConstRef<P5>::Type T6;
		typedef typename convertConstRef<P7>::Type T7;
		typedef R(*Func)(P1, P2, P3, P4, P5, P6, P7);
		typedef TR(*RawFunc)(T1, T2, T3, T4, T5, T6, T7);
		typedef R(T::*MemberFunc)(P1, P2, P3, P4, P5, P6,P7)const;
		typedef TR(T::*RawMemberFunc)(T1, T2, T3, T4, T5, T6,T7)const;

		typedef typename zhihe::FuncTraits<Func> CFuncTraits;
		typedef typename zhihe::FuncTraits <Func>::Params Params;
		typedef typename zhihe::FuncTraits <Func>::RawParams RawParams;
		typedef typename zhihe::FuncTraits <Func>::ObjParams ObjParams;
		typedef typename TClass<RawMemberFunc>::TypeDesc TypeDesc;
		typedef FuncTraits<Func> TID;

		static  const Type type()
		{
			return &FuncRtti<FuncTraits>::rtti;
		}
		static R call(T const* obj, D fp, TypeListValues <Params> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.tl.hd);
		}
		static R raw_call(T const* obj, D fp, TypeListValues <RawParams> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.tl.hd);
		}
	};

	template <class T, class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class D>
	struct FuncTraits <R(T::*) (P1, P2, P3, P4, P5, P6, P7, P8) const MEBRIDGE_THROWSPEC, D>
	{
		static bool const isMemberFunction = true;
		static bool const isConstMemberFunction = true;
		typedef D DeclType;
		typedef T ClassType;
		typedef R ReturnType;
		typedef typename convertConstRef<R>::Type TR;
		typedef typename convertConstRef<P1>::Type T1;
		typedef typename convertConstRef<P2>::Type T2;
		typedef typename convertConstRef<P3>::Type T3;
		typedef typename convertConstRef<P4>::Type T4;
		typedef typename convertConstRef<P5>::Type T5;
		typedef typename convertConstRef<P5>::Type T6;
		typedef typename convertConstRef<P7>::Type T7;
		typedef typename convertConstRef<P8>::Type T8;

		typedef R(*Func)(P1, P2, P3, P4, P5, P6, P7, P8);
		typedef TR(*RawFunc)(T1, T2, T3, T4, T5, T6, T7, T8);
		typedef R(T::*MemberFunc)(P1, P2, P3, P4, P5, P6, P7,P8)const;
		typedef TR(T::*RawMemberFunc)(T1, T2, T3, T4, T5, T6, T7,T8)const;

		typedef typename zhihe::FuncTraits<Func> CFuncTraits;
		typedef typename zhihe::FuncTraits <Func>::Params Params;
		typedef typename zhihe::FuncTraits <Func>::RawParams RawParams;
		typedef typename zhihe::FuncTraits <Func>::ObjParams ObjParams;
		typedef typename TClass<RawMemberFunc>::TypeDesc TypeDesc;
		typedef FuncTraits<Func> TID;

		static  const Type type()
		{
			return &FuncRtti<FuncTraits>::rtti;
		}
		static R call(T const* obj, D fp, TypeListValues <Params> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.tl.tl.hd);
		}
		static R raw_call(T const* obj, D fp, TypeListValues <RawParams> tvl)
		{
			return (obj->*fp)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.tl.hd, tvl.tl.tl.tl.tl.tl.tl.tl.hd);
		}
	};
}
#endif // ZHIHE_FunctionTraits_h__
