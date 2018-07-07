#ifndef GUARD_struct_h__
#define GUARD_struct_h__
#include "../hpp/reflection.h"
using namespace zhihe;

namespace ts {
	struct RawBase;
	struct Base;
	DECL_ENUM(Flag, Open, Close, Invalid, Other);
	namespace fff {
		DECL_ENUM(Flag, Open, Close, Other);
	}
}


// namespace zhihe {
// 	template <>Propertys& ImpStaticReflection<ts::RawBase>();
// 	Propertys& ImpStaticBaseReflection();
// 	template <>Propertys& ImpStaticReflection<ts::Base>() { return zhihe::ImpStaticBaseReflection(); };
// }

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

	DECL_ENUM(Color, RED, GREEN, BLUE, YELLOW, PINK, DARK, WHITE);
	template <typename T>
	struct TBase : public Struct
	{
		DECL_STRUCT(TPLT(TBase, T), Struct);
		u8  val8;
		Color color;
		T    tval;
		int* pval;
		void set_val(u8 i) { val8 = i; }
		u8   get_val()const { return val8; }
		void set_color(Color c, const int v, int* pv) { 
			color = c; 
			val8 = v; 
			pval = pv; }
		DECL_PROPERTY(TBase, FIELDS(color,tval,val8), METHODS(set_color,set_val));
	};
}

DECL_REFLECT(ts::Base, "Base",FIELDS(_charArr,_char,_u32,_f64,_f32,_s32,_pf32,_u16),METHODS(setget));
DECL_REFLECT(ts::RawBase, "RawBase",FIELDS(_charArr,_char,_u32,_f64,_f32,_s32,_pf32,_u16,_enum),METHODS(setget));


#include "./display.h"

namespace ts {
	void testStruct()
	{
		Base base;
		Type type = zhihe::TypeOf<ts::Base>::type;
		printf("test Struct:size %d\r\n", sizeof(Struct));
		printf("test ts::Base:size %d\r\n", sizeof(ts::Base));
		Method fref = type.getPropertys().getMethod("setget");
		printf("typename %s \r\n", fref.type.getName());
		char* tmp = "char*";
		char* rstr = fref.call<char*, f64, f32, char*, u8>(&base,64.000f,32.00f, "char*",8);
		printf(rstr); printf("\r\n");
		base.tell();
		f64 ret;
		printf("read _f64:%f  \r\n", type.getPropertys().getField("_f64").get<f64>(&base,ret) ? ret : 0);
		printf("write _f64:123\r\n", type.getPropertys().getField("_f64").set<f64>(&base,123) ? ret : 0);
		printf("read _f64:%f  \r\n", type.getPropertys().getField("_f64").get<f64>(&base,ret) ? ret : 0);
		f64* p64 = type.getPropertys().getField("_f64").ref<f64>(&base);
		if (p64) {
			*p64 = 1234567;
			printf("refraction read _f64:%f\r\n",type.getPropertys().getField("_f64").get<f64>(&base,ret) ? ret : 0);
		}

		ts::RawBase rawBase;
		display(zhihe::TypeOf<ts::RawBase>::type, (Struct*)&rawBase);

		display(type,(Struct*)&base);

		TBase<int> ibase;
		type = TBase<int>::type;
		type.getPropertys().getField("tval").set<int>(&ibase, 11);
		int val;
		type.getPropertys().getMethod("set_color").call<void, Color,const int,int*>(&ibase, Color::GREEN,4,&val);
		display(TBase<int>::type, &ibase);
	}
}

#endif // GUARD_struct_h__
