#ifndef GUARD_BitField_h__
#define GUARD_BitField_h__
#include "reflection.h"
namespace zhihe
{
	namespace internal{
		template <size_t LastBit>
		struct MinimumTypeHelper {
			typedef
				typename std::conditional<LastBit == 0,  void,
				typename std::conditional<LastBit <= 8,  u8,
				typename std::conditional<LastBit <= 16, u16,
				typename std::conditional<LastBit <= 32, u32,
				typename std::conditional<LastBit <= 64, u64,
				void>::type>::type>::type>::type>::type type;
		};
	}
	template <size_t Index, size_t EndIndex = Index>
	class BitField : Struct {
	private:
		static_assert(EndIndex >= Index, "Index Not Right");
		const static int Bits = EndIndex - Index + 1;
		typedef typename internal::MinimumTypeHelper<Index + Bits>::type T;
		const static T Mask = (1u << Bits) - 1u;
	public:
		DECL_STRUCT(TPLT(BitField), Struct);

		template <class T2>
		BitField &operator=(T2 value) {
			value_ = (value_ & ~(Mask << Index)) | ((value & Mask) << Index);
			return *this;
		}

		operator T() const { return (value_ >> Index) & (Mask); }
		explicit operator bool() const { return value_ & (Mask << Index); }
		BitField &operator++() { return *this = *this + 1; }
		T operator++(int) { T r = *this; ++*this; return r; }
		BitField &operator--() { return *this = *this - 1; }
		T operator--(int) { T r = *this; ++*this; return r; }

	private:
		T value_;
	};
}
#endif // GUARD_BitField_h__
