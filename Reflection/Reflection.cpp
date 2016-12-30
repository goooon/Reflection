// Propertys.cpp : 定义控制台应用程序的入口点。
//

#include <string.h>
#include <stdio.h>
#include "./hpp/reflection.h"

using namespace zhihe;
#include "./test/struct.h"
#include "./test/object.h"
#include "./test/tmplt.h"
using namespace ts;
#include <iostream>

template <typename T>
struct Rttis
{
	static const int iii = 0;
	static int get() { return iii; }
};

class abcd : public Struct
{
public:
	DECL_ENUM(Color, GREEN, BLACK, Other, RED);
	struct InnerStruct : public Struct
	{
		DECL_ENUM(Flag4, E0, E1, E2, E3,E4);
	};
};

int main()
{
	int i = 0;

	Type ttt = TClass<abcd::Color>::type;
	Enum e = ttt.getPropertys().getEnums();
	LOG_P("enum %s:",ttt.getName());
	for (int i = 0; i < e.getLength(); i++) {
		LOG_P("%s(%d) ", e[i].name,e[i].flag);
	}
	ttt = TClass<abcd::InnerStruct::Flag4>::type;
	LOG_P("\r\nenum %s:", ttt.getName());
	e = ttt.getPropertys().getEnums();
	for (int i = 0; i < e.getLength(); i++) {
		LOG_P("%s(%d) ", e[i].name, e[i].flag);
	}

	LOG_P("\r\n");
	ts::testStruct();
	ts::testObject();
	ts::testTemplate();
	Type type;
	cachar* name;
	hash64 hash;
	TypeId typeId;
	BaseTypes* typeprops;
	Propertys* propertys;

	type = TClass<int>::type;
	hash = type.getHash();
	name = type.getName();
	typeId = type.getTypeId();
	typeprops = type.getBaseTypes();
	propertys = &type.getPropertys();
	int* a = (int*)type.newStruct();

	type = TClass<int*>::type;
	hash = type.getHash();
	name = type.getName();
	typeId = type.getTypeId();
	typeprops = type.getBaseTypes();
	propertys = &type.getPropertys();

	type = TClass<int&>::type;
	hash = type.getHash();
	name = type.getName();
	typeId = type.getTypeId();
	typeprops = type.getBaseTypes();
	propertys = &type.getPropertys();

    return 0;
}
