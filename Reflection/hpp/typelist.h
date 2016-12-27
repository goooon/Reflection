#ifndef ZHIHE_TypeList_h__
#define ZHIHE_TypeList_h__

#include "./tlstring.h"
namespace zhihe
{
    struct None;
	template<typename... TList>
	struct typelist
	{
	};

	typedef typelist<> nulllist;

	//////////////////////////////////////////////////////////
	template<size_t N, typename... TList> struct typenames;

	template<size_t N, typename T, typename... TList>
	struct typenames< N, typelist<T, TList...> >
	{
		constexpr static auto TypeName = TClass<T>::TypeName + internal::str(",") + typenames< N - 1, typelist<TList...> >::TypeName;
	};

	template<typename T, typename... TList>
	struct typenames< 0, typelist<T, TList...> >
	{
		constexpr static auto TypeName = TClass<T>::TypeName;
	};

	template<>
	struct typenames< 0, nulllist >
	{
		constexpr static auto TypeName = internal::str("?");
	};
	template<>
	struct typenames< -1, nulllist >
	{
		constexpr static auto TypeName = internal::str("void");
	};
	/**
	A TypeList with actual values.
	*/
	template <typename List>
	struct TypeListValues
	{
		constexpr static auto toRearString()->decltype(internal::str(")"))
		{
			return internal::str(")");
		}
		constexpr static auto toString()->decltype(internal::str("void"))
		{
			return internal::str("void");
		}
		constexpr static auto TypeName = internal::str("void");
		static  const Type type()
		{
			const static Type::Rtti inst = { &Type::BaseTypes::vNone,TypeName.Name,TypeName.Hash,TypeId::v,0,0,0 };
			return inst;
		}
	};

	template <typename Head, typename Tail = None>
	struct TypeList
	{
		constexpr static auto toString()->decltype(internal::str("(") + TypeListValues<TypeList>::toString())
		{
			return internal::str("(") + TypeListValues<TypeList>::toString();
		}
		constexpr static auto STypeName = toString();
		typedef internal::typedesc1<zh_str2type(STypeName.Name)> TypeDesc;
		static  const Type type()
		{
			const static Type::Rtti inst = { &Type::BaseTypes::vNone,TypeDesc::TypeName.Name,TypeDesc::TypeName.Hash,TypeId::v,0,0,0 };
			return inst;
		}
	};

	/**
		TypeListValues recursive template definition.
	*/
	template <typename Head, typename Tail>
	struct TypeListValues <TypeList <Head, Tail> >
	{
		Head hd;
		TypeListValues <Tail> tl;

		TypeListValues(Head hd_, TypeListValues <Tail> const& tl_)
			: hd(hd_), tl(tl_)
		{
		}

		constexpr static auto toRearString()->decltype(internal::str(",") + TClass<Head>::TypeDesc::TypeName + TypeListValues <Tail>::toRearString())
		{
			return internal::str(",") + TClass<Head>::TypeDesc::TypeName + TypeListValues <Tail>::toRearString();
		}
		constexpr static auto toString()->decltype(TClass<Head>::TypeDesc::TypeName + TypeListValues <Tail>::toRearString())
		{
			return TClass<Head>::TypeDesc::TypeName + TypeListValues <Tail>::toRearString();
		}
		constexpr static auto TypeName = toString();
		static  const Type type()
		{
			const static Type::Rtti inst = { &Type::BaseTypes::vNone,TypeName.Name,TypeName.Hash,TypeId::v,0,0,0 };
			return inst;
		}
	};

	// Specializations of type/value list for head types that are references and
	// const-references.  We need to handle these specially since we can't count
	// on the referenced object hanging around for the lifetime of the list.

	template <typename Head, typename Tail>
	struct TypeListValues <TypeList <Head&, Tail> >
	{
		Head hd;
		TypeListValues <Tail> tl;

		TypeListValues(Head& hd_, TypeListValues <Tail> const& tl_)
			: hd(hd_), tl(tl_)
		{
		}

		constexpr static auto toRearString()->decltype(internal::str(",") + TClass<Head>::TypeName + internal::str("&") + TypeListValues <Tail>::toRearString())
		{
			return  internal::str(",") + TClass<Head>::TypeName + internal::str("&") + TypeListValues <Tail>::toRearString();
		}
		constexpr static auto toString()->decltype(TClass<Head>::TypeName + internal::str("&") + TypeListValues <Tail>::toRearString())
		{
			return TClass<Head>::TypeName + internal::str("&") + TypeListValues <Tail>::toRearString();
		}
		constexpr static auto TypeName = toString();
		static  const Type type()
		{
			const static Type::Rtti inst = { &Type::BaseTypes::vNone,TypeName.Name,TypeName.Hash,TypeId::v,0,0,0 };
			return inst;
		}
	};

	template <typename Head, typename Tail>
	struct TypeListValues <TypeList <Head const&, Tail> >
	{
		Head hd;
		TypeListValues <Tail> tl;

		TypeListValues(Head const& hd_, const TypeListValues <Tail>& tl_)
			: hd(hd_), tl(tl_)
		{
		}

		constexpr static auto toRearString()->decltype(internal::str(",") + TClass<Head>::TypeName + internal::str(" const&") + TypeListValues <Tail>::toRearString())
		{
			return internal::str(",") + TClass<Head>::TypeName + internal::str(" const&") + TypeListValues <Tail>::toRearString();
		}
		constexpr static auto toString()->decltype(TClass<Head>::TypeName + internal::str(" const&") + TypeListValues <Tail>::toRearString())
		{
			return TClass<Head>::TypeName + internal::str(" const&") + TypeListValues <Tail>::toRearString();
		}
		constexpr static auto TypeName = toString();
		static  const Type type()
		{
			const static Type::Rtti inst = { &Type::BaseTypes::vNone,TypeName.Name,TypeName.Hash,TypeId::v,0,0,0 };
			return inst;
		}
	};

	//==============================================================================
	/**
		Subclass of a TypeListValues constructable from the Lua stack.
	*/

	template <typename List, int Start = 1>
	struct ArgList
	{
	};

	template <int Start>
	struct ArgList <None, Start> : public TypeListValues <None>
	{
		ArgList()
		{
		}
	};

	template <typename Head, typename Tail, int Start>
	struct ArgList <TypeList <Head, Tail>, Start>
		: public TypeListValues <TypeList <Head, Tail> >
	{
		ArgList()
			: TypeListValues <TypeList <Head, Tail> >()
		{
		}
	};
}
#endif
