#include "./rtti.h"
#include "./reflection.h"

using namespace zhihe;

#ifndef ME_COMPILER_HEADER_ONLY

const Type Type::vNone;
zhihe::Fields Fields::vNone;
Type::TypeNodes Type::TypeNodes::vNone = { 0 };
Type::Rtti None::rtti = { &Type::TypeNodes::vNone,None::TypeDesc::TypeName.Name,None::TypeDesc::TypeName.Hash,TypeId::v,&ImpStaticReflection<None> };
zhihe::Type::Rtti TypeOf<void>::rtti = { &zhihe::TypeNodes::vNone,TypeOf<void>::TypeDesc::TypeName.Name,TypeOf<void>::TypeDesc::TypeName.Hash,TypeOf<void>::TypeIndex,&ImpStaticReflection<void>,0,0 };

#define IMPL_RAW_TYPE(T,s,e) \
zhihe::Type::Rtti TypeOf<T>::rtti = {&zhihe::TypeNodes::vNone,TypeOf<T>::TypeDesc::TypeName.Name,TypeOf<T>::TypeDesc::TypeName.Hash,TypeOf<T>::TypeIndex,&ImpStaticReflection<T>,&Wrapper<T>::newStruct,0};


IMPL_RAW_TYPE(char, "char", TypeId::u8);
IMPL_RAW_TYPE(wchar_t, "wchar", TypeId::u16);
IMPL_RAW_TYPE(char*, "char*", TypeId::astr);
IMPL_RAW_TYPE(wchar_t*, "wchar*", TypeId::wstr);
IMPL_RAW_TYPE(u8, "u8", TypeId::u8);
IMPL_RAW_TYPE(s8, "s8", TypeId::s8);
IMPL_RAW_TYPE(u16, "u16", TypeId::u16);
IMPL_RAW_TYPE(s16, "s16", TypeId::s16);
IMPL_RAW_TYPE(u32, "u32", TypeId::u32);
IMPL_RAW_TYPE(s32, "s32", TypeId::s32);
IMPL_RAW_TYPE(u64, "u64", TypeId::u64);
IMPL_RAW_TYPE(s64, "s64", TypeId::s64);
IMPL_RAW_TYPE(f32, "f32", TypeId::f32);
IMPL_RAW_TYPE(f64, "f64", TypeId::f64);
IMPL_RAW_TYPE(bool, "bool", TypeId::u8);
IMPL_RAW_TYPE(zhihe::Type, "Type", TypeId::type);
//IMPL_RAW_TYPE(void, "void", TypeId::v,0);


AnyPointer::ConvFunc AnyPointer::convs[TypeIdMask::CateCount][TypeIdMask::CateCount] = {
		{ void_all ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all,fail_all ,fail_all ,fail_all ,fail_all ,fail_all },
		{ fail_all ,b8_b8,	  b8_b16,	b8_b32,	  b8_b64,	b8_f32,   b8_f64  ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all },
		{ fail_all ,b16_b8,	  b16_b16,	b16_b32,  b16_b64,	b16_f32,  b16_f64 ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all },
		{ fail_all ,b32_b8,	  b32_b16,	b32_b32,  b32_b64,	b32_f32,  b32_f64 ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all },
		{ fail_all ,b64_b8,	  b64_b16,	b64_b32,  b64_b64,	b64_f32,  b64_f64 ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all },
		{ fail_all ,f32_b8,	  f32_b16,	f32_b32,  f32_b64,	f32_f32,  f32_f64 ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all },
		{ fail_all ,f64_b8,	  f64_b16,	f64_b32,  f64_b64,	f64_f32,  f64_f64 ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all },
		{ fail_all ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all,fail_all ,fail_all ,fail_all ,fail_all ,fail_all },
		{ fail_all ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all,fail_all ,fail_all ,fail_all ,fail_all ,fail_all },
		{ fail_all ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all,fail_all ,fail_all ,fail_all ,fail_all ,fail_all },
		{ fail_all ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all,fail_all ,fail_all ,fail_all ,fail_all ,fail_all },
		{ fail_all ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all,fail_all ,fail_all ,fail_all ,fail_all ,fail_all },
	};

Methods Propertys::EndMethod;

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

#endif