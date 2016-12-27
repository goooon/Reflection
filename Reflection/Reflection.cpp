// Propertys.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <string.h>
#include <stdio.h>
#include "./hpp/reflection.h"

using namespace zhihe;
#include "./test/struct.h"
#include "./test/object.h"
#include "./test/tmplt.h"
using namespace ts;
#include <iostream>
//241.
int main()
{
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