#ifndef ZHIHE_ConstValue_h__
#define ZHIHE_ConstValue_h__

#include "./Types.h"
#include <type_traits>
namespace zhihe
{
	namespace const_expr
	{
		constexpr hash64 prime = 0x100000001B3ull;
		constexpr hash64 basis = 0xCBF29CE484222325ull;
	}

	hash64 make_hash_dynamic(char const* str);
	
	constexpr hash64 make_hash_static(char const* str)
	{
		return (*str) ? (*(str + 1)) ? (((*str) * const_expr::prime + const_expr::basis) ^ make_hash_static(str + 1)) : ((*str) * const_expr::prime + const_expr::basis) : 0;
	}

	constexpr hash64 operator "" _hash(char const* p, size_t)
	{
		return make_hash_static(p);
	}

	namespace mtl {
		template<char>using charDummy = char;
		template <int N>
		constexpr char at(const char* a) { return a[N]; }
		template<int... dummy>
		struct F
		{
			const char Name[sizeof...(dummy)+1];
			const hash64  Hash;
			const int Length;
			const int Size;

			constexpr F(const char* a) : Name{ at<dummy>(a)..., 0 }, Length(sizeof...(dummy)), Size(sizeof...(dummy)+1), Hash(a[0] * const_expr::prime + const_expr::basis){}
			constexpr F(hash64 h, charDummy<dummy>... a) : Name{ a..., 0 }, Length(sizeof...(dummy)), Size(sizeof...(dummy)+1), Hash(h){}
			constexpr F(const F& a) : Name{ a.Name[dummy]..., 0 }, Length(a.Length), Size(a.Size), Hash(a.Hash){}

			template<int... dummyB>
			constexpr F<dummy..., sizeof...(dummy)+dummyB...> operator + (F<dummyB...> b)const
			{
				return{ this->Hash ^ b.Hash,this->Name[dummy]..., b.Name[dummyB]... };
			}
			operator const char*()const { return Name; }
		};

		template<int I>
		struct get_string
		{
			constexpr static auto g(const char* a) -> decltype(get_string<I - 1>::g(a) + F<0>(a + I))
			{
				return get_string<I - 1>::g(a) + F<0>(a + I);
			}
		};

		template<>
		struct get_string<0>
		{
			constexpr static F<0> g(const char* a)
			{
				return{ a };
			}
		};

		template<int I>
		constexpr auto str(const char(&a)[I]) -> decltype(get_string<I - 2>::g(a))
		{
			return get_string<I - 2>::g(a);
		}

		template <typename T>
		constexpr auto make_template() -> decltype(str("<") + T::TypeName + str(">"))
		{
			return str("<") + T::TypeName + str(">");
		}

		template <typename T1, typename T2>
		constexpr auto make_template() -> decltype(str("<") + T1::TypeName + str(",") + T2::TypeName + str(">"))
		{
			return str("<") + T1::TypeName + str(",") + T2::TypeName + str(">");
		}

		template <typename T1, typename T2, typename T3>
		constexpr auto make_template() -> decltype(str("<") + T1::TypeName + str(",") + T2::TypeName + str(",") + T3::a + str(">"))
		{
			return str("<") + T1::a + str(",") + T2::TypeName + str(",") + T3::TypeName + str(">");
		}

		template <typename T1, typename T2, typename T3, typename T4>
		constexpr auto make_template() -> decltype(str("<") + T1::TypeName + str(",") + T2::TypeName + str(",") + T3::TypeName + str(",") + T4::TypeName + str(">"))
		{
			return str("<") + T1::a + str(",") + T2::TypeName + str(",") + T3::TypeName + str(",") + T4::TypeName + str(">");
		}
	}
}
#endif // ConstValue_h__
