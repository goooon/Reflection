#ifndef GUARD_tmplt_h__
#define GUARD_tmplt_h__
#include "../hpp/reflection.h"
#include "./display.h"
namespace ts
{
	template <typename T>
	struct TStruct : public Struct {
        DECL_PROPERTY(TStruct, FIELDS(_char), METHODS(method));
		DECL_STRUCT(TPLT(TStruct, T), Struct);
	public:
		u8 _u8;
		char* _char = "TStruct";
	public:
        int method() { return 0; }
	};


	template <typename T,int N>
	class TObject : public Object {
        DECL_PROPERTY(TObject, FIELDS(_u8), METHODS(method));
		DECL_OBJECT(TPLT(TObject,T,NType<N>), Object);
	public:
		char* _char = "TObject";
		u8    _u8;
		int method() { return 0; }
	};
	template <typename T>
	class TDerivedObject : public TObject<T, 20>, public TStruct<T> {
		typedef TObject<T, 20> BASE1;
		DECL_PROPERTY(TDerivedObject, FIELDS(_char), METHODS());
		DECL_OBJECT(TPLT(TDerivedObject, T), BASE1, TStruct<T>);
	public:
		char* _char = "TDerivedObject";
	public:
        int method() { return 0; }
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

		type = TObject<int, 2>::type;
		obj = type.newObject();
		display(obj);
		del_me obj;
	}
}
#endif // GUARD_tmplt_h__
