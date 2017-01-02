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
  
	namespace ts{
	  DECL_ENUM(Color, RED, GREEN, BLUE, YELLOW, PINK, DARK, WHITE);
		template <typename T>
		struct TBase : public Struct
		{
			DECL_STRUCT(TPLT(TBase, T), Struct);
			u8  val8;
			Color color;
			T    tval;
			void set_val(u8 i) { val8 = i; }
			u8   get_val()const { return val8; }
			void set_color(Color c){color = c;}
			DECL_PROPERTY(TBase, FIELDS(val8, color,tval), METHODS(set_val, get_val,set_color));
		};
	}

	Type type = Type::vNone;
	const char* name;
	hash64 hash;
	TypeId typeId;
	BaseTypes* typeprops;
	Propertys* propertys;
	
	type = TClass<ts::TBase<int>>::type;
	hash = type.getHash();
	name = type.getName();
	typeId = type.getTypeId();
	typeprops = type.getBaseTypes();
	propertys = &type.getPropertys();

	type = TClass<int*>::type;
	hash = type.getHash();
	name = type.getName();
	typeId = type.getTypeId();
	typeprops = type.getBaseTypes();
	propertys = &type.getPropertys();

See more from ./test