#ifndef GUARD_display_h__
#define GUARD_display_h__
#include "../hpp/reflection.h"
using namespace zhihe;
namespace ts
{
	void display(Type type,Struct* str,int depth);
	void display(Object* obj);
	void display(Type type, Struct* str);
}
#endif // GUARD_display_h__
