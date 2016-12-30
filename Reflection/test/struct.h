#ifndef GUARD_struct_h__
#define GUARD_struct_h__
#include "../hpp/reflection.h"
#include "./display.h"

using namespace zhihe;

namespace ts {
	struct RawBase;
	struct Base;
	DECL_ENUM(Flag, Open, Close, Invalid, Other);
	namespace fff {
		DECL_ENUM(Flag, Open, Close, Other);
	}
}


namespace zhihe {
	template <>Propertys& ImpStaticReflection<ts::RawBase>();
	Propertys& ImpStaticBaseReflection();
	template <>Propertys& ImpStaticReflection<ts::Base>() { return zhihe::ImpStaticBaseReflection(); };
}

namespace ts {
	struct RawBase : public Struct
	{
		DECL_ENUM(ERawBase, RED,GREEN,BLUE,YELLOW,PINK,DARK,WHITE);

		char* _char;
		u32 _u32;
		f32* _pf32;
		s32 _s32;
		u16 _u16;
		char _charArr[15] = "charArr";
		u8  _u8;
		f32 _f32;
		f64 _f64;
		ERawBase _enum = ERawBase::PINK;
		void setU32Attr(u32 i) { _u32 = i; }
		u32  getU32Attr()const { return _u32; }
		char* setget(f64 v64, f32 v32, char* str, u8 vu8) {
			printf("setget(%f,%f,%s,%d)\r\n", v64, v32, str, vu8);
			_f64 = v64;
			_f32 = v32;
			_char = str;
			_u8 = vu8;
			return "hello";
		}
		void tell() {
			printf("tell(%f,%f,%s,%d)\r\n", _f64, _f32, _char, _u8);
		}
	};

	struct Base : public Struct
	{
		char* _char;
		u32 _u32;
		f32* _pf32;
		s32 _s32;
		u16 _u16;
		char _charArr[15] = "charArr";
		u8  _u8;
		f32 _f32;
		f64 _f64;
		void setU32Attr(u32 i) { _u32 = i; }
		u32  getU32Attr()const { return _u32; }
		char* setget(f64 v64, f32 v32, char* str, u8 vu8) {
			printf("setget(%f,%f,%s,%d)\r\n", v64, v32, str, vu8);
			_f64 = v64;
			_f32 = v32;
			_char = str;
			_u8 = vu8;
			return "setget()";
		}
		void tell() {
			printf("tell(%f,%f,%s,%d)\r\n", _f64, _f32, _char, _u8);
		}
	};

	template <typename T>
	struct TBase : public Base
	{
		DECL_STRUCT(TPLT(TBase, T), Base);
		u8 _u8_tbase;
		fff::Flag _flag = fff::Flag::Open;
		void set_u8_tbase(u8 i) { _u8_tbase = i; }
		u8   get_u8_tbase()const { return _u8_tbase; }
		DECL_PROPERTY(TBase, FIELDS(_u8_tbase,_flag), METHODS(set_u8_tbase, get_u8_tbase));
	};
}

namespace zhihe
{
	DECL_REFLECT(ts::Base, "Base");
	DECL_REFLECT(ts::RawBase, "RawBase");
	template <>
	Propertys& ImpStaticReflection<ts::RawBase>()
	{
		typedef ts::RawBase self;
		const static Fields ap[] = {
			{ &self::_charArr,"_charArr" },
			{ &self::_char,"_char" },
			{ &self::_u32,"_u32" },
			{ &self::_f64,"_f64" },
			{ &self::_f32,"_f32" },
			{ &self::_s32,"_s32" },
			{ &self::_pf32,"_pf32" },
			{ &self::_u16,"_u16" },
			{ &self::_enum ,"_enum"},
			{ &self::_u8,"_u8"},
			{ &self::getU32Attr,&self::setU32Attr,"strintattr" },
			Fields() };
		const static Methods fp[] = {
			{ &self::setget,"setget" },
			Methods() };
		static Propertys prop(TClass<self>::type, ap, fp);
		return prop;
	}


	Propertys& ImpStaticBaseReflection()
	{
		typedef ts::Base self;
		const static Fields ap[] = {
			{ &self::_charArr,"_charArr" },
			{ &self::_char,"_char" },
			{ &self::_u32,"_u32" },
			{ &self::_f64,"_f64" },
			{ &self::_f32,"_f32" },
			{ &self::_s32,"_s32" },
			{ &self::_pf32,"_pf32" },
			{ &self::_u16,"_u16" },
			{ &self::getU32Attr,&self::setU32Attr,"strintattr" },
			Fields() };
		const static Methods fp[] = {
			{ &self::setget,"setget" },
			Methods() };
		static Propertys prop(TClass<self>::type, ap, fp);
		return prop;
	}
}

#define Varr(a,b,...) Varr(__VA_ARGS__)
namespace ts {
	void testStruct()
	{
		Base base;
		Type type = zhihe::TClass<ts::Base>::type;
		printf("test Struct:size %d\r\n", sizeof(Struct));
		printf("test ts::Base:size %d\r\n", sizeof(ts::Base));
		Method fref = type.getPropertys().getMehod("setget");
		printf("typename %s \r\n", fref.type.getName());
		char* tmp = "char*";
		char* rstr = fref.invoke<char*, f64, f32, char*, u8>(&base,64.000f,32.00f, "char*",8);
		printf(rstr); printf("\r\n");
		base.tell();
		f64 ret;
		printf("read _f64:%f  \r\n", ret, type.getPropertys().getField("_f64").get<f64>(&base,ret));
		printf("write _f64:123\r\n", ret, type.getPropertys().getField("_f64").set<f64>(&base,123));
		printf("read _f64:%f  \r\n", ret, type.getPropertys().getField("_f64").get<f64>(&base,ret));
		f64* p64 = type.getPropertys().getField("_f64").ref<f64>(&base);
		if (p64) {
			*p64 = 1234567;
			printf("refraction read _f64:%f\r\n",ret, type.getPropertys().getField("_f64").get<f64>(&base,ret));
		}

		ts::RawBase rawBase;
		display(TClass<ts::RawBase>::type, (Struct*)&rawBase);

		display(type,(Struct*)&base);

		TBase<int> ibase;
		display(TBase<int>::type, &ibase);
	}
}

#endif // GUARD_struct_h__
