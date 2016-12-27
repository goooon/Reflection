#ifndef ZHIHE_TypeArray_GUARD_H___
#define ZHIHE_TypeArray_GUARD_H___
#include "./Types.h"
namespace zhihe
{
	struct ArrayDesc
	{
		b32 isReadOnly()const;
		b32 isRefferenced()const;
		b32 isSameBuffer()const;
		u32 getReffCount()const;
		void inc()const;
		b32 dec()const;
		inline b32 operator == (const ArrayDesc& r)const
		{
			return this == &r;
		}
		inline b32 operator != (const ArrayDesc& r)const
		{
			return this != &r;
		}
		void assign(achar* data, u32 len, u32 capacity);
		static ArrayDesc* createConstReff(const achar* data, s32 count);
		static ArrayDesc* createStaticReff(achar* data, s32 capacity, s32 dataLen = 0);
		static ArrayDesc* createDynamicReff(u32 size, s32 capacity, s32 dataLen = 0);
		achar*   _pdata;
		uint     _dataLen;
		uint     _capacity; //
		mutable uint     _reff;//
	private:
		void operator = (const ArrayDesc&);
	};
	namespace internal{
		template<typename T, T... C>
		struct ConstArray final {
		public:
			static constexpr T const raw_array[sizeof...(C)] = { C... };
			static constexpr unsigned int raw_length = sizeof...(C);
			static ArrayDesc value;
			typedef T Type;
		public:
			static constexpr T const * data() noexcept
			{
				return &raw_array[0];
			}
			static constexpr unsigned int size() noexcept
			{
				return raw_length;
			};
			static constexpr T const * cbegin() noexcept
			{
				return &raw_array[0];
			}
			static constexpr T const * cend() noexcept
			{
				return &raw_array[raw_length];
			}
		};
		template <class A, class B, class C, class D>struct Combinder;
		template <typename T, T... A, T... B, T... C, T... D>
		struct Combinder<ConstArray<T, A...>, ConstArray<T, B...>, ConstArray<T, C...>, ConstArray<T, D...>>
		{
			typedef ConstArray<T, A..., B..., C..., D...> Array;
		};

		template<typename T, T... C>
		constexpr T const ConstArray<T, C...>::raw_array[sizeof...(C)];
		template<typename T, T... C>
		zhihe::ArrayDesc ConstArray<T, C...>::value = { (achar*)ConstArray<T, C...>::raw_array, ConstArray<T, C...>::raw_length, 0, 0 };
	}

	template<
		typename TT, TT... ArrayArg,
		typename A = internal::ConstArray < TT >,
		typename B = internal::ConstArray < TT >,
		typename C = internal::ConstArray < TT >>
		using TFixedArray = internal::Combinder<internal::ConstArray<TT, ArrayArg...>, A, B, C>;

	template<
		int... ArrayArg,
		typename A = internal::ConstArray<int >,
		typename B = internal::ConstArray<int >,
		typename C = internal::ConstArray<int >>
		using IntFixedArray = TFixedArray<int, ArrayArg..., A, B, C>;
	/*
	typedef IntFixedArray<1, 2>::ArrayList PropArray;
	typedef IntFixedArray<3, 4, 5>::ArrayList PropArray2;
	typedef IntFixedArray<6, 7, PropArray, PropArray2>::Array PropArrayo;
	*/
	//AtomDesc(IntFixedArray<1,2,3>::Array)
#define AtomDesc(arr) *(zhihe::Array<arr::Type>::Desc*)(&arr::value)
	//AtomArray(int,1,2,3,4)
#define AtomArray(a,...) Array<decltype(a)>(*(Array<decltype(a)>::Desc*)(&TFixedArray<decltype(a),a,__VA_ARGS__>::Array::value))
}
#endif
