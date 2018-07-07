#ifndef ZHIHE_TCLASS_GUARD_H__
#define ZHIHE_TCLASS_GUARD_H__
#include <type_traits>
#include "./tlstring.h"
#include "./rtti.h"
#include "./constvalue.h"
namespace zhihe
{
	template <typename TT>struct TypeOf;

	namespace internal
	{
		typedef zh_str2type("#")  Const;
		typedef zh_str2type("()") Function;
		typedef zh_str2type("*")  Pointer;
		typedef zh_str2type("&")  Refer;
		typedef zh_str2type("[]") Array;
	}

	template<typename T>
	struct TypeOf<T*> {
		typedef T* Type;
		typedef typename TypeOf<T>::raw_type raw_type;
		typedef typename TypeOf<T>::obj_type*  obj_type;
		DECL_TYPEDESC2(TypeOf<T>::TypeDesc, internal::typedesc1<internal::Pointer>);
		static zhihe::Type type()
		{
			return rtti;
		}
		static const TypeId TypeIndex = TypeId::ptr;
		static TypeNodes prop[2];
		static zhihe::Type::Rtti rtti;
	};

	template<typename T>
	struct TypeOf<T&> {
		typedef T& Type;
		typedef typename TypeOf<T>::raw_type raw_type;
		typedef typename TypeOf<T>::obj_type&  obj_type;
		DECL_TYPEDESC2(TypeOf<T>::TypeDesc, internal::typedesc1<internal::Refer>);
		static zhihe::Type type()
		{
			return rtti;
		}
		static const TypeId TypeIndex = TypeId::ref;
		static TypeNodes prop[2];
		static zhihe::Type::Rtti rtti;
	};

	template<typename T>
	struct TypeOf<const T> {
		typedef const T Type;
		typedef T dyna_type;
		typedef typename TypeOf<T>::raw_type raw_type;
		typedef T  obj_type;
		DECL_TYPEDESC2(internal::typedesc1<internal::Const>,TypeOf<T>::TypeDesc);
		static zhihe::Type type()
		{
			return rtti;
		}
		static const TypeId TypeIndex = TypeOf<T>::TypeIndex;
		static TypeNodes prop[2];
		static zhihe::Type::Rtti rtti;
	};

	template<typename T, int N>
	struct TypeOf<T[N]> {
		typedef T* Type;
		typedef typename TypeOf<T>::raw_type raw_type;
		typedef typename TypeOf<T>::obj_type*  obj_type;
		DECL_TYPEDESC2(TypeOf<T>::TypeDesc, internal::typedesc1<internal::Array>);
		static zhihe::Type type()
		{
			return rtti;
		}
		static const TypeId TypeIndex = TypeId::arr;
		static TypeNodes prop[2];
		static zhihe::Type::Rtti rtti;
	};

	template<typename T, int N>
	struct TypeOf<const T[N]> {
		typedef const T* Type;
		typedef typename TypeOf<T>::raw_type raw_type;
		typedef typename TypeOf<T>::obj_type*  obj_type;
		DECL_TYPEDESC2(TypeOf<T>::TypeDesc, internal::typedesc1<internal::Array>);
		static zhihe::Type type()
		{
			return rtti;
		}
		static const TypeId TypeIndex = TypeId::arr;
		static TypeNodes prop[2];
		static zhihe::Type::Rtti rtti;
	};

	template<typename T>
	struct TypeOf<T[]> {
		typedef T* Type;
		typedef typename TypeOf<T>::raw_type   raw_type;
		typedef typename TypeOf<T>::obj_type*  obj_type;
		DECL_TYPEDESC2(TypeOf<T>::TypeDesc, internal::typedesc1<internal::Array>);
		static zhihe::Type type()
		{
			return rtti;
		}
		static const TypeId TypeIndex = TypeId::arr;
		static TypeNodes prop[2];
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

		template <typename T>//enum
		class TStruct<T,true>
		{
		public:
			typedef decltype(T() << Memory()) SType;
			typedef typename SType::TypeDesc TypeDesc;
			static Type type() {
				return rtti;
			}
			static TypeNodes props[2];
			static Type::Rtti rtti;
			const static TypeId TypeIndex = TypeId::enu;
		};

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

	template <typename T>struct TypeOf : public internal::TTp<T, std::is_base_of<Object,T>::value>::Type
	{
		typedef typename  internal::TTp<T, std::is_base_of<Object,T>::value>::Type Type;
		typedef typename  internal::TTp<T, std::is_base_of<Object,T>::value>::raw_type raw_type;
		typedef typename  internal::TTp<T, std::is_base_of<Object,T>::value>::obj_type obj_type;
		typedef typename  Type_Select<has_TypeDesc<Type>::value, Type, UnknownMarker>::Result::TypeDesc TypeDesc;
		operator typename internal::TTp<T, std::is_base_of<Object,T>::value>::Type& () { return *this; }
		static zhihe::Type::Rtti rtti;
	};

	struct Struct;

	template<typename T>
	TypeNodes TypeOf<T[]>::prop[2] = { { &TypeOf<T*>::rtti,0 },TypeNodes::vNone };
	template<typename T>
	Type::Rtti TypeOf<T[]>::rtti = { prop,TypeOf<T[]>::TypeDesc::TypeName.Name, 0,TypeId::arr,&ImpStaticReflection<typename TypeOf<T>::raw_type> };

	template<typename T, int N>
	TypeNodes TypeOf<T[N]>::prop[2] = { { &TypeOf<T[]>::rtti,0 },TypeNodes::vNone };
	template<typename T, int N>
	Type::Rtti TypeOf<T[N]>::rtti = { prop, TypeOf<T[]>::TypeDesc::TypeName.Name, N, TypeId::arr, &ImpStaticReflection<typename TypeOf<T>::raw_type> };

	template<typename T, int N>
	TypeNodes TypeOf<const T[N]>::prop[2] = { { &TypeOf<T[]>::rtti,0 },TypeNodes::vNone };
	template<typename T, int N>
	Type::Rtti TypeOf<const T[N]>::rtti = { prop, TypeOf<T[]>::TypeDesc::TypeName.Name, N, TypeId::arr, &ImpStaticReflection<typename TypeOf<T>::raw_type> };

	template<typename T>
	TypeNodes TypeOf<const T>::prop[2] = { { &TypeOf<T>::rtti,0 },TypeNodes::vNone };
	template<typename T>
	Type::Rtti TypeOf<const T>::rtti = { prop,TypeOf<T>::TypeDesc::TypeName.Name, TypeOf<T>::TypeDesc::TypeName.Hash,TypeId::cst,&ImpStaticReflection<typename TypeOf<T>::raw_type> };
	template<typename T>

	TypeNodes TypeOf<T&>::prop[2] = { { &TypeOf<T>::rtti,0 },TypeNodes::vNone };
	template<typename T>
	Type::Rtti TypeOf<T&>::rtti = { prop,TypeOf<T&>::TypeDesc::TypeName.Name, TypeOf<T&>::TypeDesc::TypeName.Hash,TypeId::ref,&ImpStaticReflection<typename TypeOf<T>::raw_type> };
	template<typename T>

	TypeNodes TypeOf<T*>::prop[2] = { { &TypeOf<T>::rtti,0 },TypeNodes::vNone };
	template<typename T>
	Type::Rtti TypeOf<T*>::rtti = { prop,TypeOf<T*>::TypeDesc::TypeName.Name, TypeOf<T*>::TypeDesc::TypeName.Hash,TypeId::ptr,&ImpStaticReflection<typename TypeOf<T>::raw_type> };

	template <typename T>
	struct ImpReflect {
		static Propertys props;
	};
	template <typename T>
	Propertys ImpReflect<T>::props(TypeOf<T>::type);

	template <typename T>
	Propertys&  ImpStaticReflection() { return ImpReflect<T>::props; }
	template <typename T>
	zhihe::Type::Rtti TypeOf<T>::rtti = { &zhihe::TypeNodes::vNone,TypeOf<T>::TypeDesc::TypeName.Name,TypeOf<T>::TypeDesc::TypeName.Hash,TypeOf<T>::TypeIndex,&ImpStaticReflection<T> };
}
#include "./functraits.h"
namespace zhihe {
	struct ValuePointer : public AnyPointer {
	public:
		template <typename T>
		ValuePointer(const T* p) :AnyPointer(p, TypeOf<typename removeReff<T>::Type>::type) {}
		template <typename T>
		ValuePointer(T* p) : AnyPointer(p, TypeOf<typename removeReff<T>::Type>::type) {}
		virtual bool toValue(void* out, Type otype);
		virtual bool fromValue(void* in, Type itype);
	};
	
}
#include "./property.h"
namespace zhihe {

	Type::Rtti None::rtti = { &Type::TypeNodes::vNone,None::TypeDesc::TypeName.Name,None::TypeDesc::TypeName.Hash,TypeId::v,&ImpStaticReflection<None> };

	template <typename CN>
	class TRtti0 : public Memory
	{
	public:
		typedef typename CN::TypeDesc TypeDesc;
		static Type::TypeNodes _baseProperty[1];
		static Type::Rtti rtti;
	};
	template <typename CN>
	Type::TypeNodes TRtti0<CN>::_baseProperty[1] = { Type::TypeNodes::vNone };
	template <typename CN>
	Type::Rtti TRtti0<CN>::rtti = { TRtti0<CN>::_baseProperty,TRtti0<CN>::TypeDesc::TypeName.Name,TRtti0<CN>::TypeDesc::TypeName.Hash,CN::TypeIndex,(Propertys& (*)(void))&CN::GetStaticReflection,CN::NewStruct,CN::NewObject };

	template <typename CN, typename B1>
	class TRtti1 : public Memory
	{
	public:
		typedef typename CN::TypeDesc TypeDesc;
		static Type::TypeNodes _baseProperty[2];
		static Type::Rtti rtti;
	};
	template <typename CN, typename B1>
	Type::TypeNodes TRtti1<CN, B1>::_baseProperty[2] = { TYPE_OFFSET(CN,B1),Type::TypeNodes::vNone };
	template <typename CN, typename B1>
	Type::Rtti TRtti1<CN, B1>::rtti = { TRtti1<CN, B1>::_baseProperty,CN::TypeDesc::TypeName.Name,CN::TypeDesc::TypeName.Hash,CN::TypeIndex,&CN::GetStaticReflection,CN::NewStruct,CN::NewObject };

	template <typename CN, typename B1, typename B2>
	class TRtti2 : public Memory
	{
	public:
		typedef typename CN::TypeDesc TypeDesc;
		static Type::TypeNodes _baseProperty[3];
		static Type::Rtti rtti;
	};
	template <typename CN, typename B1, typename B2>
	Type::TypeNodes TRtti2<CN, B1, B2>::_baseProperty[3] = { TYPE_OFFSET(CN,B1),TYPE_OFFSET(CN,B2),Type::TypeNodes::vNone };
	template <typename CN, typename B1, typename B2>
	Type::Rtti TRtti2<CN, B1, B2>::rtti = { TRtti2<CN, B1,B2>::_baseProperty,CN::TypeDesc::TypeName.Name,CN::TypeDesc::TypeName.Hash,CN::TypeIndex,&CN::GetStaticReflection,CN::NewStruct,CN::NewObject };

	template <typename CN, typename B1, typename B2, typename B3>
	class TRtti3 : public Memory
	{
	public:
		typedef typename CN::TypeDesc TypeDesc;
		static Type::TypeNodes _baseProperty[4];
		static Type::Rtti rtti;
	};
	template <typename CN, typename B1, typename B2, typename B3>
	Type::TypeNodes TRtti3<CN, B1, B2, B3>::_baseProperty[4] = { TYPE_OFFSET(CN,B1),TYPE_OFFSET(CN,B2),TYPE_OFFSET(CN,B3),Type::TypeNodes::vNone };
	template <typename CN, typename B1, typename B2, typename B3>
	Type::Rtti TRtti3<CN, B1, B2, B3>::rtti = { TRtti3<CN, B1,B2,B3>::_baseProperty,CN::TypeDesc::TypeName.Name,CN::TypeDesc::TypeName.Hash,CN::TypeIndex,&CN::GetStaticReflection,CN::NewStruct,CN::NewObject };

	template <typename CN, typename B1, typename B2, typename B3, typename B4>
	class TRtti4 : public Memory
	{
	public:
		typedef typename CN::TypeDesc TypeDesc;
		static Type::TypeNodes _baseProperty[5];
		static Type::Rtti rtti;
	};
	template <typename CN, typename B1, typename B2, typename B3, typename B4>
	Type::TypeNodes TRtti4<CN, B1, B2, B3, B4>::_baseProperty[5] = { TYPE_OFFSET(CN,B1),TYPE_OFFSET(CN,B2),TYPE_OFFSET(CN,B3),TYPE_OFFSET(CN,B4),Type::TypeNodes::vNone };
	template <typename CN, typename B1, typename B2, typename B3, typename B4>
	Type::Rtti TRtti4<CN, B1, B2, B3, B4>::rtti = { TRtti4<CN, B1,B2,B3,B4>::_baseProperty,CN::TypeDesc::TypeName.Name,CN::TypeDesc::TypeName.Hash,CN::TypeIndex,&CN::GetStaticReflection,CN::NewStruct,CN::NewObject };

	struct Struct : public Memory
	{
		DECL_STRUCT(TPLT(Struct));
		public:  static Propertys& GetClassProperty(Propertys& prop) { return prop; }
	};
	bool ValuePointer::toValue(void* out, Type otype) {
		if (otype.getTypeId() == TypeId::raw) {
			if (type.getTypeId() == TypeId::obj) {
				*(Struct*)out = *(Struct*)(Object*)ptr;
				return true;
			}
		}
		return AnyPointer::toValue(out, otype);
	}
	bool ValuePointer::fromValue(void* in, Type itype) {
		if (itype.getTypeId() == TypeId::raw) {
			if (type.getTypeId() == TypeId::obj) {
				*(Struct*)(Object*)ptr = *(Struct*)in;
				return true;
			}
		}
		return AnyPointer::fromValue(in, itype);
	}
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
	template <>struct TypeOf<void>
	{
		typedef void Type;
		typedef void raw_type;
		typedef void obj_type;
		const static TypeId TypeIndex = TypeId::v;
		typedef zhihe::internal::typedesc1<zh_str2type("void")> TypeDesc;
		static zhihe::Type::Rtti rtti;
		static zhihe::Type type() { return rtti; };
	};
	zhihe::Type::Rtti TypeOf<void>::rtti = { &zhihe::TypeNodes::vNone,TypeOf<void>::TypeDesc::TypeName.Name,TypeOf<void>::TypeDesc::TypeName.Hash,TypeOf<void>::TypeIndex,&ImpStaticReflection<void>,0,0 };
    namespace internal{
		template <typename T>
		Type::Rtti TStruct<T, false>::rtti = { &TypeNodes::vNone, TStruct<T,false>::TypeDesc::TypeName.Name, TStruct<T,false>::TypeDesc::TypeName.Hash,TStruct<T,false>::TypeIndex };

        template <typename T>
		zhihe::TypeNodes TStruct<T, true>::props[2] = { {&TypeOf<u32>::rtti,0},zhihe::TypeNodes::vNone };
		template <typename T>
		Type::Rtti TStruct<T, true>::rtti = { TStruct<T, true>::props, TStruct<T,true>::TypeDesc::TypeName.Name, TStruct<T,true>::TypeDesc::TypeName.Hash,TStruct<T,true>::TypeIndex,&TStruct<T,true>::SType::GetStaticReflection };
    }

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
		if (prop.type != argtype){
			if (prop.type == Type::vNone) {
				LOG_E("Arg Error:Property is Null");
			}
			else {
				LOG_E("Func Args Error:%s !=> %s", prop.type.getName(), argtype.getName());
			}
		}
		DebugCode(
			if (!obj->isKindOf(prop.type)) {
				LOG_E("Class Type Error:%s is not a %s", obj->getTypeName(), prop.type.getName());
			});
		// if (prop.ret != TypeOf<typename removeConst<R>::Type>::type) {
		// 	LOG_E("Return Type %s != %s", prop.ret.getName(), Type(TypeOf<R>::type).getName());
		// }
		return (obj->*((typename F::RawMemberFunc)prop.dele.mf))(std::forward<Args>(args)...);
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

#include "./bitfield.h"
#endif
