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

	namespace internal{
		template<typename T, int _Index>
		struct IndexedTWrap
		{
			typedef T type;
			enum { Index = _Index };
		};

		struct _GetClass_TypeOrTHelper
		{
			template<typename T>
			static IndexedTWrap<typename T::TypeDesc, 1>     hasDefineType(IndexedTWrap<typename T::TypeDesc, 0>*);
			template<typename T>
			static IndexedTWrap<T, 0> hasDefineType(...);
		};

		template<typename T>
		struct GetClass_TypeOrT
		{
			typedef decltype(_GetClass_TypeOrTHelper::hasDefineType<T>(0)) wraptype;
			enum { value = wraptype::Index };
			typedef typename wraptype::type type;
		};
	}

	template <typename T>
	class has_TypeDesc
	{
		typedef char one;
		typedef long two;
		//typedef typename T::TypeDesc  Desc;
		//template <typename C> static one test(decltype(&T::rtti));
		//template <typename C> static two test(...);
	public:
		enum {
			value = internal::GetClass_TypeOrT<T>::value
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
	struct EnumDesc {};
	namespace internal
	{
		template <typename T,bool>
		class TStruct
		{
		public:
			typedef typename Type_Select<has_TypeDesc<T>::value, T, UnknownMarker>::Result::TypeDesc TypeDesc;
			static Type type(){
				return rtti;
			}
			static Type::Rtti rtti;
			const static TypeId TypeIndex = TypeId::raw;
		};
		//template <typename T,bool>
		//Type::Rtti TStruct<T,false>::rtti = { &BaseTypes::vNone, TStruct<T,false>::TypeDesc::TypeName.Name, TStruct<T,false>::TypeDesc::TypeName.Hash,TStruct<T,false>::TypeIndex };

		template <typename T>//not enum
		class TStruct<T, false>
		{
		public:
			typedef typename Type_Select<has_TypeDesc<T>::value, T, UnknownMarker>::Result::TypeDesc TypeDesc;
			static Type type() {
				return rtti;
			}
			static Type::Rtti rtti;
			const static TypeId TypeIndex = TypeId::raw;
		};
		template <typename T>
		Type::Rtti TStruct<T, false>::rtti = { &BaseTypes::vNone, TStruct<T,false>::TypeDesc::TypeName.Name, TStruct<T,false>::TypeDesc::TypeName.Hash,TStruct<T,false>::TypeIndex };

		template <typename T>//enum
		class TStruct<T,true>
		{
		public:
			typedef decltype(T() << Memory()) SType;
			typedef typename SType::TypeDesc TypeDesc;
			static Type type() {
				return rtti;
			}
			static BaseTypes props[2];
			static Type::Rtti rtti;
			const static TypeId TypeIndex = TypeId::enu;
		};
		template <typename T>
		zhihe::BaseTypes TStruct<T, true>::props[2] = { {&TClass<u32>::rtti,0},zhihe::BaseTypes::vNone };
		template <typename T>
		Type::Rtti TStruct<T, true>::rtti = { TStruct<T, true>::props, TStruct<T,true>::TypeDesc::TypeName.Name, TStruct<T,true>::TypeDesc::TypeName.Hash,TStruct<T,true>::TypeIndex,&TStruct<T,true>::SType::GetStaticReflection };

		template <typename T, bool> struct TTp {
			typedef typename Type_Select<std::is_base_of<Struct,T>::value, T, TStruct<T,std::is_enum<T>::value>>::Result Type;
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
		typedef typename  Type_Select<has_TypeDesc<Type>::value, Type, UnknownMarker>::Result::TypeDesc TypeDesc;
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
	template <typename T>
	zhihe::Type::Rtti TClass<T>::rtti = { &zhihe::BaseTypes::vNone,TClass<T>::TypeDesc::TypeName.Name,TClass<T>::TypeDesc::TypeName.Hash,TClass<T>::TypeIndex,&ImpStaticReflection<T> };
}
#include "./functraits.h"
#include "./property.h"
namespace zhihe {
	struct Struct;

	Type::Rtti None::rtti = { &Type::BaseTypes::vNone,None::TypeDesc::TypeName.Name,None::TypeDesc::TypeName.Hash,None::TypeIndex,&ImpStaticReflection<None> };

	template<typename T>
	BaseTypes TClass<T[]>::prop[2] = { { &TClass<T*>::rtti,0 },BaseTypes::vNone };
	template<typename T>
	Type::Rtti TClass<T[]>::rtti = { prop,TClass<T[]>::TypeDesc::TypeName.Name, 0,TypeId::arr,&ImpStaticReflection<TClass<T>::raw_type> };

	template<typename T, int N>
	BaseTypes TClass<T[N]>::prop[2] = { { &TClass<T[]>::rtti,0 },BaseTypes::vNone };
	template<typename T, int N>
	Type::Rtti TClass<T[N]>::rtti = { prop, TClass<T[]>::TypeDesc::TypeName.Name, N, TypeId::arr, &ImpStaticReflection<TClass<T>::raw_type> };

	template<typename T>
	BaseTypes TClass<const T>::prop[2] = { { &TClass<T>::rtti,0 },BaseTypes::vNone };
	template<typename T>
	Type::Rtti TClass<const T>::rtti = { prop,TClass<T>::TypeDesc::TypeName.Name, TClass<T>::TypeDesc::TypeName.Hash,TypeId::cst,&ImpStaticReflection<TClass<T>::raw_type> };
	template<typename T>

	BaseTypes TClass<T&>::prop[2] = { { &TClass<T>::rtti,0 },BaseTypes::vNone };
	template<typename T>
	Type::Rtti TClass<T&>::rtti = { prop,TClass<T&>::TypeDesc::TypeName.Name, TClass<T&>::TypeDesc::TypeName.Hash,TypeId::ref,&ImpStaticReflection<TClass<T>::raw_type> };
	template<typename T>

	BaseTypes TClass<T*>::prop[2] = { { &TClass<T>::rtti,0 },BaseTypes::vNone };
	template<typename T>
	Type::Rtti TClass<T*>::rtti = { prop,TClass<T*>::TypeDesc::TypeName.Name, TClass<T*>::TypeDesc::TypeName.Hash,TypeId::ptr,&ImpStaticReflection<TClass<T>::raw_type> };

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
//////////////////////////////////////////////////////////////////////////
#define PRIVITE_PROPERTY_OP(NAME, I, REC, RES) REC RES
#define PRIVITE_PROPERTY_VASSIGN(NAME, X, I) {&NAME::X,QUOTE(X)},
#define PRIVATE_PROPERTY0(...) P99_FOR(self, COUNT_ASSERT_VAR_ARGS(__VA_ARGS__), PRIVITE_PROPERTY_OP, PRIVITE_PROPERTY_VASSIGN, __VA_ARGS__)
#define PRIVATE_PROPERTY1(...) 
#define PRIVATE_PROPERTY_PASTE(N,...)  P99_PASTE2(PRIVATE_PROPERTY,N)(__VA_ARGS__)
#define DECL_METHODS(...) PRIVATE_PROPERTY_PASTE(P99_IS_EMPTY(__VA_ARGS__),__VA_ARGS__)
#define DECL_FIELDS(...)  PRIVATE_PROPERTY_PASTE(P99_IS_EMPTY(__VA_ARGS__),__VA_ARGS__)
#define DECL_PROPERTY(NAME, F, M) static zhihe::Propertys& GetClassProperty(zhihe::Propertys& prop) {typedef NAME self;const static zhihe::Fields f[] = { DECL_##F zhihe::Fields() };; const static zhihe::Methods m[] = { DECL_##M zhihe::Methods() };prop.setPropertys(type, f, m);return prop;}
//////////////////////////////////////////////////////////////////////////
#define PRIVITE_ENUM_RTTI_OP(NAME, I, REC, RES) REC,RES
#define PRIVITE_ENUM_RTTI_VASSIGN(NAME, X, I) {(u32)NAME::X,QUOTE(X)}

#define PRIVITE_ENUM_OP(NAME, I, REC, RES) REC,RES
#define PRIVITE_ENUM_VASSIGN(NAME, X, I) X

#define DECL_ENUM(NAME, ...)  \
	struct rtti_##NAME : public zhihe::Struct {  \
		enum class NAME { P99_FOR(NAME, COUNT_ASSERT_VAR_ARGS(__VA_ARGS__), PRIVITE_ENUM_OP, PRIVITE_ENUM_VASSIGN, __VA_ARGS__) };\
		struct FlagDesc : zhihe::Struct  \
		{   \
			typedef internal::typedesc1<zh_str2type(QUOTE(NAME))> TypeDesc;  \
			friend     Propertys& zhihe::ImpStaticReflection<NAME>();   \
		    public:    static Propertys& GetStaticReflection() { return GetClassProperty(zhihe::ImpStaticReflection<NAME>()); }   \
		    private:   static Propertys& GetClassProperty(Propertys& prop) {   \
			const static Methods fp[] = {   \
				{ &FlagDesc::GetEnums,"GetEnums" },Methods() };   \
				prop.setPropertys(prop.getClassType(), fp);   \
				return prop;   \
			}   \
			Enum GetEnums() {   \
				const static Enum::Item ei[] = { P99_FOR(NAME,COUNT_ASSERT_VAR_ARGS(__VA_ARGS__), PRIVITE_ENUM_RTTI_OP, PRIVITE_ENUM_RTTI_VASSIGN, __VA_ARGS__) }; \
				return{ COUNT_ASSERT_VAR_ARGS(__VA_ARGS__),&ei[0] }; \
			} \
		}; \
			friend FlagDesc operator<<(const NAME &o, const Memory &h) \
			{ \
					return FlagDesc(); \
			} \
		};	\
		typedef rtti_##NAME::NAME NAME; 
}
#endif
