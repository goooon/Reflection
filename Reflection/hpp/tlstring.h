#ifndef zhihe_tlString_h__
#define zhihe_tlString_h__

#include <type_traits>
namespace zhihe
{
	namespace internal{
		template< std::size_t N, std::size_t M >
		constexpr char string_at(const char(&c)[M]) noexcept
		{
			static_assert(M <= 101, "String longer than 100 (excluding terminating \\0)!");
			return (N < M) ? c[N] : 0;
		}

		template< char ... Cs > struct string;

		template<> struct string<> {};

		template< char ... Cs >
		struct string
		{
			static constexpr char const value[sizeof...(Cs)+1] = { Cs...,'\0' };
		};
		template<char... C>
		constexpr char const string<C...>::value[sizeof...(C)+1];
	}
	template< char ... Cs > struct string : internal::string< Cs ... > {};

	namespace internal
	{
		template< typename, char ... >
		struct number_string_builder;

		template< typename T >
		struct number_string_builder< T > { using type = T; };
		template< template< char ... > class S, char ... Hs, char C, char ... Cs >
		struct number_string_builder< S< Hs ... >, C, Cs ... >
			: std::conditional< C == 'a',
			number_string_builder< S< Hs ... > >,
			number_string_builder< S< C, Hs ...>, Cs ... > >::type { };

		template< typename, char ... >
		struct string_builder;
		template< typename T >
		struct string_builder< T > { using type = T; };
		template< template< char ... > class S, char ... Hs, char C, char ... Cs >
		struct string_builder< S< Hs ... >, C, Cs ... >
			: std::conditional< C == '\0',
			string_builder< S< Hs ... > >,
			string_builder< S< Hs ..., C >, Cs ... > >::type
		{ };

		typedef unsigned long long hash64;
		namespace const_expr
		{
			constexpr hash64 prime = 0x100000001B3ull;
			constexpr hash64 basis = 0xCBF29CE484222325ull;
		}

		struct function {
			hash64 make_hash_dynamic(char const* str)
			{
				hash64 ret{ 0 };
				while (*str) {
					ret ^= *str * const_expr::prime + const_expr::basis;
					str++;
				}
				return ret;
			}
		};

		constexpr hash64 make_hash_static(char const* str)
		{
			return (*str) ? (*(str + 1)) ? (((*str) * const_expr::prime + const_expr::basis) ^ make_hash_static(str + 1)) : ((*str) * const_expr::prime + const_expr::basis) : 0;
		}

		constexpr hash64 operator "" _hash(char const* p)
		{
			return make_hash_static(p);
		}
			template<char>using charDummy = char;
			template <int N>
			constexpr char at(const char* a) { return a[N]; }
			template<int... dummy>
			struct F
			{
				const hash64  Hash;
				const int     Length;
				const int     Size;
				const char    Name[sizeof...(dummy)+1];

				static constexpr char SName[sizeof...(dummy)+1] = { dummy..., 0 };

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
			template <typename T>
			struct typedesc1
			{
				typedef decltype(str(T::value)) NameType;
				constexpr static NameType TypeName = str(T::value);
			};
			template<typename T>
			constexpr typename typedesc1<T>::NameType typedesc1<T>::TypeName;

			template <typename T1, typename T2>
			struct typedesc2
			{
				typedef decltype(str(T1::value) + str(T2::value)) NameType;
				constexpr static NameType TypeName = str(T1::value) + str(T2::value);
			};
			template<typename T1, typename T2>
			constexpr typename typedesc2<T1, T2>::NameType typedesc2<T1, T2>::TypeName;

			template <typename T1, typename T2, typename T3>
			struct typedesc3
			{
				typedef decltype(str(T1::value) + str(T2::value) + str(T3::value)) NameType;
				constexpr static NameType TypeName = str(T1::value) + str(T2::value) + str(T3::value);
			};
			template<typename T1, typename T2, typename T3>
			constexpr typename typedesc3<T1, T2, T3>::NameType typedesc3<T1, T2, T3>::TypeName;

			template <typename T1, typename T2, typename T3, typename T4>
			struct typedesc4
			{
				typedef decltype(str(T1::value) + str(T2::value) + str(T3::value) + str(T4::value)) NameType;
				constexpr static NameType TypeName = str(T1::value) + str(T2::value) + str(T3::value) + str(T4::value);
			};
			template<typename T1, typename T2, typename T3, typename T4>
			constexpr typename typedesc4<T1, T2, T3, T4>::NameType typedesc4<T1, T2, T3, T4>::TypeName;

			template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
			struct typedesc6
			{
				typedef decltype(str(T1::value) + str(T2::value) + str(T3::value) + str(T4::value) + str(T5::value) + str(T6::value)) NameType;
				constexpr static NameType TypeName = str(T1::value) + str(T2::value) + str(T3::value) + str(T4::value) + str(T5::value) + str(T6::value);
			};
			template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
			constexpr typename typedesc6<T1, T2, T3, T4, T5, T6>::NameType typedesc6<T1, T2, T3, T4, T5, T6>::TypeName;
	}
#define zh_numb2str(n) \
		zhihe::internal::number_string_builder< zhihe::internal::string<>, '0' + n%10, \
					n/10 == 0 ? 'a' : '0' + (n/10)%10, \
					n/100 == 0 ? 'a' : '0' + (n/100)%10, \
					n/1000 == 0 ? 'a' : '0' + (n/1000)%10, \
					n/10000 == 0 ? 'a' : '0' + (n/10000)%10, \
					n/100000 == 0 ? 'a' : '0' + (n/100000)%10, \
					n/1000000 == 0 ? 'a' : '0' + (n/1000000)%10, \
					n/10000000 == 0 ? 'a' : '0' + (n/10000000)%10, \
					n/100000000 == 0 ? 'a' : '0' + (n/100000000)%10, \
					n/1000000000 == 0 ? 'a' : '0' + (n/1000000000)%10, \
					n/10000000000 == 0 ? 'a' : '0' + (n/10000000000)%10 >::type::value

#define zh_numb2type(n) \
typename zhihe::internal::number_string_builder< zhihe::internal::string<>, '0' + n%10, \
					n/10 == 0 ? 'a' : '0' + (n/10)%10, \
					n/100 == 0 ? 'a' : '0' + (n/100)%10, \
					n/1000 == 0 ? 'a' : '0' + (n/1000)%10, \
					n/10000 == 0 ? 'a' : '0' + (n/10000)%10, \
					n/100000 == 0 ? 'a' : '0' + (n/100000)%10, \
					n/1000000 == 0 ? 'a' : '0' + (n/1000000)%10, \
					n/10000000 == 0 ? 'a' : '0' + (n/10000000)%10, \
					n/100000000 == 0 ? 'a' : '0' + (n/100000000)%10, \
					n/1000000000 == 0 ? 'a' : '0' + (n/1000000000)%10, \
					n/10000000000 == 0 ? 'a' : '0' + (n/10000000000)%10 >::type

#define MTL_INTERNAL_STRING_10(n,x)             \
    n##0<sizeof(x) ? x[n##0] : 0, \
	n##1<sizeof(x) ? x[n##1] : 0, \
	n##2<sizeof(x) ? x[n##2] : 0, \
	n##3<sizeof(x) ? x[n##3] : 0, \
	n##4<sizeof(x) ? x[n##4] : 0, \
	n##5<sizeof(x) ? x[n##5] : 0, \
	n##6<sizeof(x) ? x[n##6] : 0, \
	n##7<sizeof(x) ? x[n##7] : 0, \
	n##8<sizeof(x) ? x[n##8] : 0, \
	n##9<sizeof(x) ? x[n##9] : 0 

	
	/*zhihe::internal::string_at< n##0 >( x ),     \
   zhihe::internal::string_at< n##1 >( x ),     \
   zhihe::internal::string_at< n##2 >( x ),     \
   zhihe::internal::string_at< n##3 >( x ),     \
   zhihe::internal::string_at< n##4 >( x ),     \
   zhihe::internal::string_at< n##5 >( x ),     \
   zhihe::internal::string_at< n##6 >( x ),     \
   zhihe::internal::string_at< n##7 >( x ),     \
   zhihe::internal::string_at< n##8 >( x ),     \
   zhihe::internal::string_at< n##9 >( x )*/

#define zh_str2type(x) \
   typename zhihe::internal::string_builder< zhihe::internal::string<>, \
									   MTL_INTERNAL_STRING_10(,x),                \
									   MTL_INTERNAL_STRING_10(1,x),               \
									   MTL_INTERNAL_STRING_10(2,x),               \
									   MTL_INTERNAL_STRING_10(3,x),               \
									   MTL_INTERNAL_STRING_10(4,x),               \
									   MTL_INTERNAL_STRING_10(5,x),               \
									   MTL_INTERNAL_STRING_10(6,x),               \
									   MTL_INTERNAL_STRING_10(7,x),               \
									   MTL_INTERNAL_STRING_10(8,x),               \
									   MTL_INTERNAL_STRING_10(9,x) >::type
}

#define DECL_TYPEDESC1(TypeDesc) \
		public: typedef zhihe::internal::typedesc1<zh_str2type(TypeDesc::TypeName.Name)> TypeDesc;

#define DECL_TYPEDESC2(TypeDesc1,TypeDesc2) \
		public: typedef zhihe::internal::typedesc2<zh_str2type(TypeDesc1::TypeName.Name), zh_str2type(TypeDesc2::TypeName.Name)> TypeDesc;

#define DECL_TYPEDESC3(TypeDesc1,TypeDesc2,TypeDesc3) \
		public: typedef zhihe::internal::typedesc3<zh_str2type(TypeDesc1::TypeName.Name), zh_str2type(TypeDesc2::TypeName.Name), zh_str2type(TypeDesc3::TypeName.Name)> TypeDesc;

#endif