# Reflection
C++ Reflection and header only

## Preface
This project use c++ 11 feature to implement class data member and function member reflection and rtti;

## Building
Build successful under vs2015 (win10) and gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.4) ,other env are not tested

#### Runtime
There are no dependencies in the runtime so building is pretty straightforward.


#### Examples
You will find some demo in test directory

### Limits
virtual inheritance of class not supported,currently int only support no more than three base classes


### Usage
#### how to use
  
	/* demo */
  DECL_ENUM(Color, RED, GREEN, BLUE, YELLOW, PINK, DARK, WHITE);
	template <typename T>
	struct TBase : public Struct
	{
		DECL_STRUCT(TPLT(TBase, T), Struct);
		u8 _u8_tbase;
		Color color;
		void set_u8_tbase(u8 i) { _u8_tbase = i; }
		u8   get_u8_tbase()const { return _u8_tbase; }
		DECL_PROPERTY(TBase, FIELDS(_u8_tbase, _flag, color), METHODS(set_u8_tbase, get_u8_tbase));
	};
	
	
  Type type;
	const char* name;
	hash64 hash;
	TypeId typeId;
	BaseTypes* typeprops;
	Propertys* propertys;
	
	type = TClass<TBase>::type;
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

See more from ./test