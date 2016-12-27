#ifndef GUARD_tmplt_h__
#define GUARD_tmplt_h__
#include "../hpp/reflection.h"
#include "./display.h"
namespace ts
{
	template <typename T>
	struct TStruct : public Struct {
		DECL_STRUCT(TPLT(TStruct, T), Struct);
	public:
		u8 _u8;
		char* _char = "TStruct";
	public:
		static Propertys& GetClassProperty(Propertys& prop) {
			typedef TStruct self;
			const static Fields ap[] = {
				{ &self::_u8,"u8_in_TStruct" },
				Fields() };
			const static Methods fp[] = {
				Methods() };
			prop.setPropertys(type, ap, fp);
			return prop;
		}
	};
	template <typename T,int N>
	class TObject : public Object {
		DECL_OBJECT(TPLT(TObject,T,NType<N>), Object);
	public:
		char* _char = "TObject";
		u8    _u8;
	public:
		static Propertys& GetClassProperty(Propertys& prop) {
			typedef TObject self;
			const static Fields ap[] = {
				{ &self::_u8,"u8_inTObject" },
				{ &self::_char,"char_inTObject"},
				Fields() };
			const static Methods fp[] = {
				Methods() };
			prop.setPropertys(type, ap, fp);
			return prop;
		}
	};
	template <typename T>
	class TDerivedObject : public TObject<T, 20>, public TStruct<T> {
		DECL_OBJECT(TPLT(TDerivedObject, T), TObject, TStruct);
	public:
		char* _char = "TDerivedObject";
	public:
		static Propertys& GetClassProperty(Propertys& prop) {
			typedef TDerivedObject self;
			const static Fields ap[] = {
				{ &self::_char,"char*_inTDerivedObject" },
				Fields() };
			const static Methods fp[] = {
				Methods() };
			prop.setPropertys(type, ap, fp);
			return prop;
		}
	};
}

namespace ts {
	void testTemplate()
	{
		Type type = TDerivedObject<int>::type;
		Object* obj = type.newObject();
		display(obj);
		del_me obj;

		type = TDerivedObject<TDerivedObject<float>>::type;
		obj = type.newObject();
		display(obj);
		del_me obj;
	}
}
#endif // GUARD_tmplt_h__
