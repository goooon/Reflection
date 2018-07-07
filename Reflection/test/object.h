#ifndef GUARD_object_h__
#define GUARD_object_h__
#include "../hpp/reflection.h"
#include "./display.h"
#include "./struct.h"

class DerObject;
class SubObject;
using namespace zhihe;
Propertys& ImpSubObjectReflection();

namespace zhihe {
	template <>Propertys& ImpStaticReflection<SubObject>() { return ImpSubObjectReflection(); }
}

class DerObject : public Object
{
	DECL_OBJECT(TPLT(DerObject), Object);
	struct InnerStruct : public Struct
	{
		DECL_ENUM(EFlag, E0, E1, E2, E3, E4);
	};
public:
	int intValue1;
	int intValue2;
	u32 u32Value1;
	u32 u32Value2;
	u8  u8Value1;
	u8  u8Value2;
	s16 s16Value1;
	InnerStruct::EFlag eflag;
	int getint()const { return intValue2; }
	virtual void setint(int i) { intValue2 = i; }
	virtual int getJ() { return 0; }
	virtual void setJ(int j) { return; }
	virtual float floatf(float f) { return 0; }
public:
	DECL_PROPERTY(DerObject, FIELDS(eflag,intValue1, intValue2, u32Value1, u32Value2, u8Value1, u8Value2, s16Value1), METHODS(setint, getint, setJ, getJ, floatf));
};


class SubClass : public DerObject,public ts::TBase<DerObject>
{
	DECL_OBJECT(TPLT(SubClass), DerObject,TBase);
	int k;
	int j;
	f32 f;
	u32 getU(int i) { return i; }
	virtual int getJ() { return j; }
	virtual void setJ(int j) { this->j = j; return; }
	virtual float floatf(float f) { this->f = f; return f; }
	DECL_PROPERTY(SubClass, FIELDS(), METHODS());
};

Propertys& ImpSubObjectReflection()
{
	typedef SubClass self;
	const static Fields ap[] = {
		{ &self::f,"f" },
		{ &self::k,"k" },
		{ &self::j,"j" },
		Fields() };
	const static Methods fp[] = {
		{ &self::getU,"getU" },
		Methods() };
	static Propertys prop(self::type, ap, fp);
	return prop;
}

namespace ts {
	void testObject()
	{
		zhihe::Object* obj = new_me DerObject();
		Type type = obj->getType();
		display(obj);
		del_me obj;

		obj = type.newObject();
		display(obj);
		del_me obj;

		obj = new_me SubClass();
		display(obj);
		Method fprop = obj->getType().getPropertys().getMethod("setJ");
		fprop.call<void, int>(obj, 0x3456);
		fprop = obj->getType().getPropertys().getMethod("getJ");
		if (fprop) {
			int getJ = fprop.call<int>(obj);
			LOG_A(0x3456 == getJ, "setJ or getJ failed %d", getJ);
		}

		fprop = obj->getType().getPropertys().getMethod("floatf");
		if (fprop) {
			float getf = fprop.call<float>(obj, 1.02f);
			LOG_A(getf == 1.02f, "floatf failed %f", getf);
		}
		del_me obj;
	}
}
#endif // GUARD_object_h__
