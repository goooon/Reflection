#ifndef ZHIHE_TCLASS_GUARD_H__
#define ZHIHE_TCLASS_GUARD_H__
#include <type_traits>
#include "./tlstring.h"
#include "./rtti.h"
#include "./ConstValue.h"
namespace zhihe
{
	template <typename TT>struct TClass;

	namespace internal
	{
		typedef zh_str2type("#")  Const;
		typedef zh_str2type("()") Function;
		typedef zh_str2type("*")  Pointer;
		typedef zh_str2type("&")  Refer;
		typedef zh_str2type("[]") Array;
	}

	template<typename T>
	struct TClass<T*> {
		typedef T* Type;
		typedef typename TClass<T>::raw_type raw_type;
		typedef typename TClass<T>::obj_type*  obj_type;
		DECL_TYPEDESC2(TClass<T>::TypeDesc, internal::typedesc1<internal::Pointer>);
		static zhihe::Type type()
		{
			return rtti;
		}
		static const TypeId TypeIndex = TypeId::ptr;
		static BaseTypes prop[2];
		static zhihe::Type::Rtti rtti;
	};


	template<typename T>
	struct TClass<T&> {
		typedef T& Type;
		typedef typename TClass<T>::raw_type raw_type;
		typedef typename TClass<T>::obj_type&  obj_type;
		DECL_TYPEDESC2(TClass<T>::TypeDesc, internal::typedesc1<internal::Refer>);
		static zhihe::Type type()
		{
			return rtti;
		}
		static const TypeId TypeIndex = TypeId::ref;
		static BaseTypes prop[2];
		static zhihe::Type::Rtti rtti;
	};


	template<typename T>
	struct TClass<const T> {
		typedef const T Type;
		typedef T dyna_type;
		typedef typename TClass<T>::raw_type raw_type;
		typedef T  obj_type;
		DECL_TYPEDESC2(internal::typedesc1<internal::Const>,TClass<T>::TypeDesc);
		static zhihe::Type type()
		{
			return rtti;
		}
		static const TypeId TypeIndex = TClass<T>::TypeIndex;
		static BaseTypes prop[2];
		static zhihe::Type::Rtti rtti;
	};


	template<typename T, int N>
	struct TClass<T[N]> {
		typedef T* Type;
		typedef typename TClass<T>::raw_type raw_type;
		typedef typename TClass<T>::obj_type*  obj_type;
		DECL_TYPEDESC2(TClass<T>::TypeDesc, internal::typedesc1<internal::Array>);
		static zhihe::Type type()
		{
			return rtti;
		}
		static const TypeId TypeIndex = TypeId::arr;
		static BaseTypes prop[2];
		static zhihe::Type::Rtti rtti;
	};

	template<typename T>
	struct TClass<T[]> {
		typedef T* Type;
		typedef typename TClass<T>::raw_type   raw_type;
		typedef typename TClass<T>::obj_type*  obj_type;
		DECL_TYPEDESC2(TClass<T>::TypeDesc, internal::typedesc1<internal::Array>);
		static zhihe::Type type()
		{
			return rtti;
		}
		static const TypeId TypeIndex = TypeId::arr;
		static BaseTypes prop[2];
		static zhihe::Type::Rtti rtti;
	};

	//template <typename T>
	//class has_TypeName
	//{
	//	typedef char one;
	//	typedef long two;
 //       //typedef typename T::TypeDesc  Desc;
	//	template <typename C> static two test(...);
	//	template <typename C> static one test(typename T::TypeDesc);
	//public:
	//	enum { value = sizeof(test<T>(0)) == sizeof(char) };
	//};

	template<typename T, int _Index>
	struct IndexedTWrap
	{
		typedef T type;
		//static T gettype();
		enum { Index = _Index };
	};

	struct _GetClass_TypeOrTHelper
	{
		template<typename T>
		static IndexedTWrap<typename T::TypeDesc, 1>     _hasDefineType(IndexedTWrap<typename T::TypeDesc, 0>*);
		template<typename T>
		static IndexedTWrap<T, 0> _hasDefineType(...);
	};

	template<typename T>
	struct GetClass_TypeOrT  //获取T::type类型
	{
		typedef decltype(_GetClass_TypeOrTHelper::_hasDefineType<T>(0)) wraptype;
		enum { value = wraptype::Index };
		typedef typename wraptype::type type;
		int view = value;
	};

	template <typename T>
	class has_TypeName
	{
		typedef char one;
		typedef long two;
		//typedef typename T::TypeDesc  Desc;
		//template <typename C> static one test(decltype(&T::rtti));
		//template <typename C> static two test(...);

	public:
		enum {
			value = GetClass_TypeOrT<T>::value
		};
	};


	struct StarMarker
	{
		typedef internal::typedesc1<zh_str2type("*")> TypeDesc;
	};

	struct UnknownMarker
	{
		typedef internal::typedesc1<zh_str2type("?")> TypeDesc;
	};

	namespace internal
	{

		template <typename T>
		class TStruct
		{
		public:
			typedef typename Type_Select<has_TypeName<T>::value, T, UnknownMarker>::Result::TypeDesc TypeDesc;
			static Type type()
			{
				return rtti;
			}
			static Type::Rtti rtti;
			const static TypeId TypeIndex = TypeId::raw;
		};
		template <typename T>
		Type::Rtti TStruct<T>::rtti = { &BaseTypes::vNone, TStruct<T>::TypeDesc::TypeName.Name, TStruct<T>::TypeDesc::TypeName.Hash,TStruct<T>::TypeIndex };

		template <typename T, bool> struct TTp {
			typedef typename Type_Select<std::is_base_of<Struct,T>::value, T, TStruct<T>>::Result Type;
			typedef T raw_type;
			typedef T obj_type;
		};
		template <typename T> struct TTp<T, true> {
			typedef T Type;
			typedef T raw_type;
			typedef Object obj_type;
		};
	}

	template <typename T>struct TClass : public internal::TTp<T, std::is_base_of<Object,T>::value>::Type
	{
		typedef typename  internal::TTp<T, std::is_base_of<Object,T>::value>::Type Type;
		typedef typename  internal::TTp<T, std::is_base_of<Object,T>::value>::raw_type raw_type;
		typedef typename  internal::TTp<T, std::is_base_of<Object,T>::value>::obj_type obj_type;
		typedef typename  Type_Select<has_TypeName<T>::value, T, UnknownMarker>::Result::TypeDesc TypeDesc;
		operator typename internal::TTp<T, std::is_base_of<Object,T>::value>::Type& () { return *this; }
		static zhihe::Type::Rtti rtti;
	};
	template <typename T>
	struct ImpReflect {
		static Propertys props;
	};
	template <typename T>
	Propertys ImpReflect<T>::props(TClass<T>::type);

	template <typename T>
	Propertys&  ImpStaticReflection() { return ImpReflect<T>::props; }

	//template <typename T>
	//Propertys& GetStaticReflection()
	//{
	//	return ImpStaticReflection<T>();
	//}
	template <typename T>
	zhihe::Type::Rtti TClass<T>::rtti = { &zhihe::BaseTypes::vNone,TClass<T>::TypeDesc::TypeName.Name,TClass<T>::TypeDesc::TypeName.Hash,TClass<T>::TypeIndex,&ImpStaticReflection<T> };
}
#include "./functraits.h"
#include "./property.h"
namespace zhihe {
	struct Struct;
	//struct Reflective : public Memory
	//{
	//public:
	//	static Propertys reflection;
	//	static Propertys& GetStaticReflection() { return reflection; }
	//};
	//Propertys Reflective::reflection(Type::vNone);

	Type::Rtti None::rtti = { &Type::BaseTypes::vNone,None::TypeDesc::TypeName.Name,None::TypeDesc::TypeName.Hash,None::TypeIndex,&ImpStaticReflection<None> };

	template<typename T>
	BaseTypes TClass<T[]>::prop[2] = { { &TClass<T*>::rtti,0 },BaseTypes::vNone };
	template<typename T>
	Type::Rtti TClass<T[]>::rtti = { prop,TClass<T[]>::TypeDesc::TypeName.Name, 0,TypeId::arr,&ImpStaticReflection<T> };

	template<typename T, int N>
	BaseTypes TClass<T[N]>::prop[2] = { { &TClass<T[]>::rtti,0 },BaseTypes::vNone };
	template<typename T, int N>
	Type::Rtti TClass<T[N]>::rtti = { prop, TClass<T[]>::TypeDesc::TypeName.Name, N, TypeId::arr, &ImpStaticReflection<T> };

	template<typename T>
	BaseTypes TClass<const T>::prop[2] = { { &TClass<T>::rtti,0 },BaseTypes::vNone };
	template<typename T>
	Type::Rtti TClass<const T>::rtti = { prop,TClass<T>::TypeDesc::TypeName.Name, TClass<T>::TypeDesc::TypeName.Hash,TypeId::cst,&ImpStaticReflection<T> };
	template<typename T>

	BaseTypes TClass<T&>::prop[2] = { { &TClass<T>::rtti,0 },BaseTypes::vNone };
	template<typename T>
	Type::Rtti TClass<T&>::rtti = { prop,TClass<T&>::TypeDesc::TypeName.Name, TClass<T&>::TypeDesc::TypeName.Hash,TypeId::ptr,&ImpStaticReflection<T> };
	template<typename T>

	BaseTypes TClass<T*>::prop[2] = { { &TClass<T>::rtti,0 },BaseTypes::vNone };
	template<typename T>
	Type::Rtti TClass<T*>::rtti = { prop,TClass<T*>::TypeDesc::TypeName.Name, TClass<T*>::TypeDesc::TypeName.Hash,TypeId::ptr,&ImpStaticReflection<T> };

	template <typename CN>
	class TRtti0 : public Memory
	{
	public:
		typedef typename CN::TypeDesc TypeDesc;
		static Type::BaseTypes _baseProperty[1];
		static Type::Rtti rtti;
	};
	template <typename CN>
	Type::BaseTypes TRtti0<CN>::_baseProperty[1] = { Type::BaseTypes::vNone };
	template <typename CN>
	Type::Rtti TRtti0<CN>::rtti = { TRtti0<CN>::_baseProperty,TRtti0<CN>::TypeDesc::TypeName.Name,TRtti0<CN>::TypeDesc::TypeName.Hash,CN::TypeIndex,(Propertys& (*)(void))&CN::GetStaticReflection,CN::NewStruct,CN::NewObject };

	template <typename CN, typename B1>
	class TRtti1 : public Memory
	{
	public:
		typedef typename CN::TypeDesc TypeDesc;
		static Type::BaseTypes _baseProperty[2];
		static Type::Rtti rtti;
	};
	template <typename CN, typename B1>
	Type::BaseTypes TRtti1<CN, B1>::_baseProperty[2] = { TYPE_OFFSET(CN,B1),Type::BaseTypes::vNone };
	template <typename CN, typename B1>
	Type::Rtti TRtti1<CN, B1>::rtti = { TRtti1<CN, B1>::_baseProperty,CN::TypeDesc::TypeName.Name,CN::TypeDesc::TypeName.Hash,CN::TypeIndex,&CN::GetStaticReflection,CN::NewStruct,CN::NewObject };

	template <typename CN, typename B1, typename B2>
	class TRtti2 : public Memory
	{
	public:
		//constexpr static auto TypeName = CN::TypeName;
		typedef typename CN::TypeDesc TypeDesc;
		static Type::BaseTypes _baseProperty[3];
		static Type::Rtti rtti;
	};
	template <typename CN, typename B1, typename B2>
	Type::BaseTypes TRtti2<CN, B1, B2>::_baseProperty[3] = { TYPE_OFFSET(CN,B1),TYPE_OFFSET(CN,B2),Type::BaseTypes::vNone };
	template <typename CN, typename B1, typename B2>
	Type::Rtti TRtti2<CN, B1, B2>::rtti = { TRtti2<CN, B1,B2>::_baseProperty,CN::TypeDesc::TypeName.Name,CN::TypeDesc::TypeName.Hash,CN::TypeIndex,&CN::GetStaticReflection,CN::NewStruct,CN::NewObject };

	template <typename CN, typename B1, typename B2, typename B3>
	class TRtti3 : public Memory
	{
	public:
		typedef typename CN::TypeDesc TypeDesc;
		static Type::BaseTypes _baseProperty[4];
		static Type::Rtti rtti;
	};
	template <typename CN, typename B1, typename B2, typename B3>
	Type::BaseTypes TRtti3<CN, B1, B2, B3>::_baseProperty[4] = { TYPE_OFFSET(CN,B1),TYPE_OFFSET(CN,B2),TYPE_OFFSET(CN,B3),Type::BaseTypes::vNone };
	template <typename CN, typename B1, typename B2, typename B3>
	Type::Rtti TRtti3<CN, B1, B2, B3>::rtti = { TRtti3<CN, B1,B2,B3>::_baseProperty,CN::TypeDesc::TypeName.Name,CN::TypeDesc::TypeName.Hash,CN::TypeIndex,&CN::GetStaticReflection,CN::NewStruct,CN::NewObject };

	template <typename CN, typename B1, typename B2, typename B3, typename B4>
	class TRtti4 : public Memory
	{
	public:
		typedef typename CN::TypeDesc TypeDesc;
		static Type::BaseTypes _baseProperty[5];
		static Type::Rtti rtti;
	};
	template <typename CN, typename B1, typename B2, typename B3, typename B4>
	Type::BaseTypes TRtti4<CN, B1, B2, B3, B4>::_baseProperty[5] = { TYPE_OFFSET(CN,B1),TYPE_OFFSET(CN,B2),TYPE_OFFSET(CN,B3),TYPE_OFFSET(CN,B4),Type::BaseTypes::vNone };
	template <typename CN, typename B1, typename B2, typename B3, typename B4>
	Type::Rtti TRtti4<CN, B1, B2, B3, B4>::rtti = { TRtti4<CN, B1,B2,B3,B4>::_baseProperty,CN::TypeDesc::TypeName.Name,CN::TypeDesc::TypeName.Hash,CN::TypeIndex,&CN::GetStaticReflection,CN::NewStruct,CN::NewObject };

	struct Struct : public Memory
	{
		DECL_STRUCT(TPLT(Struct));
		public:  static Propertys& GetClassProperty(Propertys& prop) { return prop; }
	};
	template <typename T>
	struct Wrapper{
        T t;
		static Struct* newStruct(TRACE_MEMORY_ARGS) { T* w = new_me T();return (Struct*)w;}
	}DECL_GNU_PACKED;

	DECL_RAW_TYPE(char, "char", TypeId::u8);
	DECL_RAW_TYPE(wchar_t, "wchar", TypeId::u16);
	DECL_RAW_TYPE(char*, "char*", TypeId::astr);
	DECL_RAW_TYPE(wchar_t*, "wchar*", TypeId::wstr);
	DECL_RAW_TYPE(u8, "u8", TypeId::u8);
	DECL_RAW_TYPE(s8, "s8", TypeId::s8);
	DECL_RAW_TYPE(u16, "u16", TypeId::u16);
	DECL_RAW_TYPE(s16, "s16", TypeId::s16);
	DECL_RAW_TYPE(u32, "u32", TypeId::u32);
	DECL_RAW_TYPE(s32, "s32", TypeId::s32);
	DECL_RAW_TYPE(u64, "u64", TypeId::u64);
	DECL_RAW_TYPE(s64, "s64", TypeId::s64);
	DECL_RAW_TYPE(f32, "f32", TypeId::f32);
	DECL_RAW_TYPE(f64, "f64", TypeId::f64);
	DECL_RAW_TYPE(bool, "bool", TypeId::u8);
	DECL_RAW_TYPE(zhihe::Type, "Type", TypeId::type);
	//DECL_RAW_TYPE(void, "void", TypeId::v,0);
	template <>struct TClass<void>
	{
		typedef void Type;
		typedef void raw_type;
		typedef void obj_type;
		const static TypeId TypeIndex = TypeId::v;
		typedef zhihe::internal::typedesc1<zh_str2type("void")> TypeDesc;
		static zhihe::Type::Rtti rtti;
		static zhihe::Type type() { return rtti; };
	};
	zhihe::Type::Rtti TClass<void>::rtti = { &zhihe::BaseTypes::vNone,TClass<void>::TypeDesc::TypeName.Name,TClass<void>::TypeDesc::TypeName.Hash,TClass<void>::TypeIndex,&ImpStaticReflection<void>,0,0 };

	class Object : public Struct
	{
		DECL_OBJECT(TPLT(Object));
	public:
		b32        isKindOf(Type type) const { return getType().isKindOf(type); }
		b32        isExactKindOf(Type type) const { return getType().isExactKindOf(type); }
		cachar*	   getTypeName()const { return getType().getName(); }
		Propertys& getProps() { static Propertys props(Object::type); return props; }
	public:
		virtual ~Object() {}
	};

	template<typename R, typename ...Args>
	R Methods::invoke_internalObject(const Methods& prop, Object* obj, Args&&... args)
	{
		typedef typename zhihe::FuncTraits<R(Object::*)(Args...)> F;
		typedef typename F::RFuncTraits RFuncTraits;

		Type argtype = RFuncTraits::TArgsRawFuncRtti::rtti;
		if (prop.type != argtype)
		{
			if (prop.type == Type::vNone) {
				LOG_E("Arg Error:Property is Null");
			}
			else {
				LOG_E("Func Args Error:%s !=> %s", prop.type.getName(), argtype.getName());
			}
		}
		DebugCode(
			if (!obj->isKindOf(prop.cls)) {
				LOG_E("Class Type Error:%s is not a %s", obj->getTypeName(), prop.cls.getName());
			});
		if (prop.ret != TClass<typename removeConst<R>::Type>::type) {
			LOG_E("Return Type %s != %s", prop.ret.getName(), Type(TClass<R>::type).getName());
		}
		return (obj->*((typename F::RawMemberFunc)prop.func))(std::forward<Args>(args)...);
	}
}
#endif
