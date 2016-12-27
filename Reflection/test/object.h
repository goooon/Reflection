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
public:
	int intValue1;
	int intValue2;
	u32 u32Value1;
	u32 u32Value2;
	u8  u8Value1;
	u8  u8Value2;
	s16 s16Value1;
	int getint()const { return intValue2; }
	virtual void setint(int i) { intValue2 = i; }
	virtual int getJ() { return 0; }
	virtual void setJ(int j) { return; }
	virtual float floatf(float f) { return 0; }
public:
	static Propertys& GetClassProperty(Propertys& prop) {
		typedef DerObject self;
		const static Fields ap[] = {
			{ &self::intValue1,"intValue1" },
			{ &self::intValue2,"intValue2" },
			{ &self::u32Value1,"u32Value1" },
			{ &self::u32Value2,"u32Value2" },
			{ &self::u8Value1,"u8Value1" },
			{ &self::u8Value2,"u8Value2" },
			{ &self::s16Value1,"s16Value1" },
			{ &self::getint,&self::setint,"intattr" },
			Fields() };
		const static Methods fp[] = {
			{ &self::setint,"setint" },
			{ &self::getint,"getint" },
			{ &self::getJ,"getJ" },
			{ &self::setJ,"setJ" },
			{ &self::floatf,"floatf" },
			Methods() };
		prop.setPropertys(type, ap, fp);
		return prop;
	}
};


class SubClass : public DerObject,public ts::TBase<DerObject>
{
	DECL_OBJECT(TPLT(SubClass), DerObject,TBase);
	int k;
	int j;
	u32 f;
	u32 getU(int i) { return i; }
	virtual int getJ() { return j; }
	virtual void setJ(int j) { this->j = j; return; }
	virtual float floatf(float f) { this->f = f; return f; }
	static Propertys& GetClassProperty(Propertys& prop) { return prop; }
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
		Method fprop = obj->getType().getPropertys().getMehod("setJ");
		fprop.invoke<void, int>(obj, 0x3456);
		fprop = obj->getType().getPropertys().getMehod("getJ");
		int getJ = fprop.invoke<int>(obj);
		LOG_A(0x3456 == getJ, "setJ or getJ failed %d", getJ);

		fprop = obj->getType().getPropertys().getMehod("floatf");
		float getf = fprop.invoke<float>(obj, 1.02f);
		LOG_A(getf == 1.02f, "floatf failed %f", getf);
		del_me obj;
	}
}
#endif // GUARD_object_h__
