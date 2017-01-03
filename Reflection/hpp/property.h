#ifndef ZHIHE_ClassProperty_GUARD_H__
#define ZHIHE_ClassProperty_GUARD_H__
#include <utility>
#include <string.h>
#include <type_traits>

#include "./rtti.h"
#include "./trace.h"
#include "./functraits.h"

namespace zhihe
{
	class Object;
	class PropertyDesc;
	struct Property
	{
	public:
		static PropertyDesc* add(PropertyDesc* desc);
	public:
		Property() = default;
		Property(Type c, const char* d, PropertyDesc* p) :type(c), desc(d), props(p) {}
		const char* getDesc()const { return desc; }
		Type getType()const { return type; }
	public:
		int  off = 0;
		Type type;
		const char* desc = 0;
		PropertyDesc* props = 0;
	};
	typedef bool(*ConvFunc)(void* in, void* out);
	bool fail_all(void*, void*) { return false; }
	bool b8_b8(void* in,void* out) { *(u8*)out = *(u8*)in; return true; }
	bool b8_b16(void* in, void* out) { *(u16*)out = *(u8*)in; return true; }
	bool b8_b32(void* in, void* out) { *(u32*)out = *(u8*)in; return true; }
	bool b8_b64(void* in, void* out) { *(u64*)out = *(u8*)in; return true; }
	bool b8_f32(void* in, void* out) { *(f32*)out = *(u8*)in; return true; }
	bool b8_f64(void* in, void* out) { *(f64*)out = *(u8*)in; return true; }

	bool b16_b8(void* in, void* out) { *(u8*)out = *(u16*)in; return true; }
	bool b16_b16(void* in, void* out) { *(u16*)out = *(u16*)in; return true; }
	bool b16_b32(void* in, void* out) { *(u32*)out = *(u16*)in; return true; }
	bool b16_b64(void* in, void* out) { *(u64*)out = *(u16*)in; return true; }
	bool b16_f32(void* in, void* out) { *(f32*)out = *(u16*)in; return true; }
	bool b16_f64(void* in, void* out) { *(f64*)out = *(u16*)in; return true; }
	
	bool b32_b8(void* in, void* out) { *(u8*)out = *(u32*)in; return true; }
	bool b32_b16(void* in, void* out) { *(u16*)out = *(u32*)in; return true; }
	bool b32_b32(void* in, void* out) { *(u32*)out = *(u32*)in; return true; }
	bool b32_b64(void* in, void* out) { *(u64*)out = *(u32*)in; return true; }
	bool b32_f32(void* in, void* out) { *(f32*)out = *(u32*)in; return true; }
	bool b32_f64(void* in, void* out) { *(f64*)out = *(u32*)in; return true; }

	bool b64_b8(void* in, void* out) { *(u8*)out = *(u64*)in; return true; }
	bool b64_b16(void* in, void* out) { *(u16*)out = *(u64*)in; return true; }
	bool b64_b32(void* in, void* out) { *(u32*)out = *(u64*)in; return true; }
	bool b64_b64(void* in, void* out) { *(u64*)out = *(u64*)in; return true; }
	bool b64_f32(void* in, void* out) { *(f32*)out = *(u64*)in; return true; }
	bool b64_f64(void* in, void* out) { *(f64*)out = *(u64*)in; return true; }

	bool f32_b8(void* in, void* out) { *(u8*)out = *(f32*)in; return true; }
	bool f32_b16(void* in, void* out) { *(u16*)out = *(f32*)in; return true; }
	bool f32_b32(void* in, void* out) { *(u32*)out = *(f32*)in; return true; }
	bool f32_b64(void* in, void* out) { *(u64*)out = *(f32*)in; return true; }
	bool f32_f32(void* in, void* out) { *(f32*)out = *(f32*)in; return true; }
	bool f32_f64(void* in, void* out) { *(f64*)out = *(f32*)in; return true; }

	bool f64_b8(void* in, void* out) { *(u8*)out = *(f64*)in; return true; }
	bool f64_b16(void* in, void* out) { *(u16*)out = *(f64*)in; return true; }
	bool f64_b32(void* in, void* out) { *(u32*)out = *(f64*)in; return true; }
	bool f64_b64(void* in, void* out) { *(u64*)out = *(f64*)in; return true; }
	bool f64_f32(void* in, void* out) { *(f32*)out = *(f64*)in; return true; }
	bool f64_f64(void* in, void* out) { *(f64*)out = *(f64*)in; return true; }

	//bool struct_object(void* in, void* out) { *(Object*)out = *(Object*)(Struct*)in; return true; }
	//bool object_struct(void* in, void* out) { *(Struct*)out = *(Struct*)(Object*)in; return true; }
	//7 x 7
	/*ConvFunc convs[7][7] = {
		{ fail_all ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all ,fail_all },
		{ fail_all ,b8_b8,	  b8_b16,	b8_b32,	  b8_b64,	b8_f32,   b8_f64},
		{ fail_all ,b16_b8,	  b16_b16,	b16_b32,  b16_b64,	b16_f32,  b16_f64 },
		{ fail_all ,b32_b8,	  b32_b16,	b32_b32,  b32_b64,	b32_f32,  b32_f64 },
		{ fail_all ,b64_b8,	  b64_b16,	b64_b32,  b64_b64,	b64_f32,  b64_f64 },
		{ fail_all ,f32_b8,	  f32_b16,	f32_b32,  f32_b64,	f32_f32,  f32_f64 },
		{ fail_all ,f64_b8,	  f64_b16,	f64_b32,  f64_b64,	f64_f32,  f64_f64 },
	};*/
	struct Fields : public Property
	{
		
	private:
		typedef int(Struct::*StructData);
		typedef int(Object::*ObjectData);
		typedef void*(Struct::*StructAttr)(void*);
		typedef void*(Object::*ObjectAttr)(void*);
		template <typename T, class C>
		void castFunction(T(C::*get)()const, void(C::*set)(T) = 0)
		{
			typedef typename Type_Select<std::is_base_of<Object,C>::value, Object, Struct>::Result Refflector;
			typedef typename Type_Select<std::is_base_of<Object,C>::value, ObjectAttr, StructAttr>::Result Result;
			typedef T(Refflector::*ConstAttrGet)(void)const;
			typedef void*(Refflector::*PtrAttrGet)(void);
			typedef void*(Refflector::*AttrGet)(void*);
			structget = (StructAttr)(Result)(AttrGet)(PtrAttrGet)(ConstAttrGet)(get);

			typedef void(Refflector::*ConstAttrSet)(T);
			typedef void*(Refflector::*PtrAttrSet)(void);
			typedef void*(Refflector::*AttrSet)(void*);
			structset = (StructAttr)(Result)(AttrSet)(PtrAttrSet)(ConstAttrSet)(set);
		}
	public:
		Fields() :setdata(0), getdata(0) {}
		template <typename T, class C>Fields(int offset, T(C::* dpr) = 0, const char* desc = 0, PropertyDesc* props = vNull) :
			Property(TClass<T>::type, desc, props),
			clsType(TClass<C>::type),
			getdata((StructData)(typename Type_Select<std::is_base_of<Object,C>::value, ObjectData, StructData>::Result)dpr)
		{
			off = 0;
			setdata = getdata;
			static_assert(!std::is_base_of<Struct,C>::value, "type_is_not_supported");
		}
		template <typename T, class C>Fields(T(C::* dpr) = 0, const char* desc = 0, PropertyDesc* props = vNull) :
			Property(TClass<T>::type, desc, props),
			clsType(TClass<C>::type),
			getdata((StructData)(typename Type_Select<std::is_base_of<Object,C>::value, ObjectData, StructData>::Result)((int(C::*))dpr))
		{
			off = static_cast<s32>((u8*)(C*)(typename C::RootType*)(Struct*)1 - (u8*)(Struct*)1);
			setdata = getdata;
			static_assert(std::is_base_of<Struct,C>::value, "type_is_not_supported");
		}
		template <typename T, class C>Fields(T(C::*get)()const = 0, void(C::*set)(T) = 0, const char* desc = 0, PropertyDesc* props = 0) :
			Property(TClass<T>::type, desc, props),
			clsType(TClass<C>::type)
		{
			off = static_cast<s32>((u8*)(C*)(typename C::RootType*)(Struct*)1 - (u8*)(Struct*)1);
			castFunction(get,set);
		}
		template <typename T, class C>Fields(T(C::*get)()const = 0, const char* desc = 0, PropertyDesc* props = 0) :
			Property(TClass<T>::type, desc, props),
			clsType(TClass<C>::type)
		{
			off = (int)(C*)(typename C::RootType*)(Struct*)1 - (int)(Struct*)1;
			castFunction(get, nullptr);
		}
		template <typename T, class C>Fields(T(C::*get)() = 0, const char* desc = 0, PropertyDesc* props = 0) :
			Property(TClass<T>::type, desc, props),
			clsType(TClass<C>::type)
		{
			off = (int)(C*)(typename C::RootType*)(Struct*)1 - (int)(Struct*)1;
			castFunction(get, nullptr);
		}
		b32 isRefference()const {
			return setdata == getdata;
		}
		template <typename T>T*   ref(Struct* c)const
		{
			if (type == Type::vNone)return vFalse;
			Type outtype = TClass<T>::type;
			if (setdata != getdata) {
				LOG_E("it's a function attribute,not supported refference");
				return nullptr;
			}
			else {
				if (outtype != type &&
					(TYPEID_CONV_MASK & (u32)outtype.getTypeId()) != (TYPEID_CONV_MASK & (u32)type.getTypeId()) &&
					!type.isKindOf(outtype)){
					LOG_E("%s casting to %s", type.getName(), outtype.getName());
				}
				typedef T(Struct::*TStructData);
				return &(c->*(TStructData)(StructData)setdata);
			}
		}
		template <typename T,typename I>b32  get(const Struct* c,I& t)const
		{
			if (type == Type::vNone)return vFalse;
			Type outtype = TClass<T>::type;
			if (setdata != getdata) {
				typedef T(Struct::*AttrPtr)(void);
				if (outtype != type &&
					(TYPEID_CONV_MASK & (u32)outtype.getTypeId()) != (TYPEID_CONV_MASK & (u32)type.getTypeId()) &&
					!type.isKindOf(outtype))
				{
					LOG_E("%s casting to %s", type.getName(), outtype.getName());
					return vFalse;
				}
				AttrPtr p = (AttrPtr)structget;
				t = ((Struct*)(reinterpret_cast<u8*>(const_cast<Struct*>(c)) + off)->*p)();
				return vTrue;
			}
			else {
				if (outtype != type &&
					(TYPEID_CONV_MASK & (u32)outtype.getTypeId()) != (TYPEID_CONV_MASK & (u32)type.getTypeId()) &&
					!type.isKindOf(outtype))
				{
					LOG_E("%s casting to %s", type.getName(), outtype.getName());
					return vFalse;
				}
				typedef T(Struct::*TStructData);
				t = (c->*(TStructData)(StructData)setdata);
				return vTrue;
			}
		}
		template <typename T>b32  set(Struct* c, T v)const
		{
			if (type == Type::vNone)return vFalse;
			if (setdata != getdata) {
				typedef void(Struct::*AttrPtr)(T);
				Type itype = TClass<T>::type;
				if (itype != type) {
					LOG_E("%s != %s", type.getName(), itype.getName());
					return vFalse;
				}
				if (!structset) {
					LOG_E("Acess Error:%s is read only", desc);
					return vFalse;
				}
				AttrPtr p = (AttrPtr)structset;
				if (clsType.getTypeId() == TypeId::raw) {
					((Struct*)(reinterpret_cast<u8*>(const_cast<Struct*>(c)) + off)->*p)(v);
				}
				else if (clsType.getTypeId() == TypeId::obj) {
					((Object*)(reinterpret_cast<u8*>(const_cast<Struct*>(c)) + off)->*p)(v);
				}
				return vTrue;
			}
			else {
				Type from = TClass<T>::type;
				if (from != type &&
					(TYPEID_CONV_MASK & (u32)from.getTypeId()) != (TYPEID_CONV_MASK & (u32)type.getTypeId()) &&
					!from.isKindOf(type))
				{
					LOG_E("%s can't cast to %s", from.getName(), type.getName());
					return vFalse;
				}
				typedef T(Struct::*TStructData);
				(c->*(TStructData)setdata) = v;
				return vTrue;
			}
		}
		union
		{
			StructData setdata;
			StructAttr structset;
		};
		union
		{
			StructData getdata;
			StructAttr structget;
		};
		Type   clsType;
		static Fields vNone;
	};

	zhihe::Fields Fields::vNone;

	typedef Object* (*ConvertFunc)(void* p);

	template <typename R,bool>struct ConvertHelper
	{
        static Object* convertToObject(void* from) {
            return (Object*)(R)from;
        }
		static ConvertFunc GetFunc(void) {
			return &convertToObject;
		}
	};
	template <typename R>struct ConvertHelper<R,false>
	{
		static ConvertFunc GetFunc(void) {
			return nullptr;
		}
	};
	struct Methods : public Property
	{
	private:
		typedef void* (Object::*Func)(void*);
	public:
		Methods() :ret(Type::vNone), cls(Type::vNone), func(0), conv(0) {}
		template<typename R, typename C, typename... Args>
		Methods(R(C::*funcc)(Args...)const = 0, const char* desc = 0, PropertyDesc* props = 0) :
			Property(Type::vNone, desc, props),
			cls(TClass<C>::type) {
			typedef R RetType;
			typedef typename removeConst<RetType>::Type SR;
            ret = TClass<SR>::type;
			typedef typename Type_Select<std::is_base_of<Object,C>::value, Object, Struct>::Result Refflector;

			typedef RetType(Refflector::*ObjFunc)(Args...);
			typedef RetType(C::*ClsFunc)(Args...);
			func = (Func)(ObjFunc)(ClsFunc)funcc;
			typedef R(C::*ArgsFunc)(Args...);
			typedef typename zhihe::FuncTraits<R(C::*)(Args...)> FuncTraitsArgs;
			typedef typename zhihe::FuncTraits<ArgsFunc>::RFuncTraits RFuncTraits;
			type = RFuncTraits::TArgsRawFuncRtti::rtti;
			typedef Can_R_Conv_To_L_Strict<Object*, R> Convatable;
			conv =  ConvertHelper<R,Convatable::value>::GetFunc();
		}
		template<typename R, typename C, typename... Args>Methods(R(C::*funcc)(Args...) = 0, const char* desc = 0, PropertyDesc* props = 0) :
			Property(Type::vNone, desc, props),
			ret(TClass<typename removeConst<R>::Type>::type),
			cls(TClass<C>::type) {
			typedef typename Type_Select<std::is_base_of<Object,C>::value, Object, Struct>::Result Refflector;
			typedef R(Refflector::*ObjFunc)(Args...);
			func = (Func)(ObjFunc)funcc;
			typedef typename zhihe::FuncTraits<R(C::*)(Args...)>::RFuncTraits RFuncTraits;
			type = RFuncTraits::TArgsRawFuncRtti::rtti;
			typedef Can_R_Conv_To_L_Strict<Object*, R> Convatable;
			conv =  ConvertHelper<R,Convatable::value>::GetFunc();
		}
		template<typename R, typename ...Args>
		static R invoke_internalObject(const Methods& prop, Object* obj, Args&&... args);
		template<typename R, typename ...Args>
		static R invoke_internalStruct(const Methods& prop, Struct* str, Args&&... args)
		{
			typedef typename zhihe::FuncTraits<R(Struct::*)(Args...)> F;
			typedef typename F::RFuncTraits RFuncTraits;
			Type argtype = RFuncTraits::TArgsRawFuncRtti::rtti;
			if (prop.type != argtype)
			{
				if (prop.type == Type::vNone) {
					LOG_E("Arg Error:Property is Null");
					return R();
				}
				else {
					LOG_E("Func Args Error:%s !=> %s", prop.type.getName(), argtype.getName());
					return R();
				}
			}
			if (prop.ret != TClass<typename removeConst<R>::Type>::type) {
				LOG_E("Return Type %s != %s", prop.ret.getName(), Type(TClass<R>::type).getName());
			}
			return (str->*((typename F::RawMemberFunc)prop.func))(std::forward<Args>(args)...);
		}
	public:
		template<typename R, typename ...Args>R invoke(Object* obj, Args&&... args)const
		{
			return invoke_internalObject<R>(*this, obj, std::forward<Args>(args)...);
		}
		template<typename R, typename ...Args>R invoke(Struct* str, Args&&... args)const
		{
			if (cls.getTypeId() == TypeId::obj) {
				return invoke_internalObject<R>(*this, (Object*)str, std::forward<Args>(args)...);
			}
			else {
				return invoke_internalStruct<R>(*this, str, std::forward<Args>(args)...);
			}
		}
		Type  getFuncType()const { return type; }
		Type  ret;
		Type  cls;
		ConvertFunc conv;
		Func  func;
		static Methods vNone;
	private:

	};
	zhihe::Methods Methods::vNone;

	struct Field
	{
		s32  offset;
		Type type;
		const Fields* prop;
		template<typename R>b32 get(Struct* str, R& r)const
		{
			return prop->get<R>(str, r);
		}
		template<typename T>b32 set(Struct* str, const T& args)const
		{
			return prop->set<T>(str, args);
		}
		template<typename T>T* ref(Struct* str)const
		{
			return prop->ref<T>(str);
		}
	};
	struct Method
	{
		s32  offset;
		Type type;
		const Methods* prop;
		operator bool() {
			return type;
		}
		Method& operator =(const Method & that)
		{
			this->offset = that.offset;
			this->type = that.type;
			this->prop = that.prop;
			return *this;
		}
		template<typename R, typename ...Args>R invoke(Struct* str, Args... args)const
		{
			return prop->invoke<R, Args...>(str, std::forward<Args>(args)...);
		}
		template<typename R, typename ...Args>R invoke(Object* obj, Args... args)const
		{
			return prop->invoke<R, Args...>(obj, std::forward<Args>(args)...);
		}
		
	};
	class  Propertys
	{
	public:
		template <u32 NA, u32 NF>
		Propertys(
			Type type,
			const Fields(&ap)[NA],
			const Methods(&fp)[NF]
		) :clstype(type), attrCount(NA - 1), funcCount(NF - 1), attrProps(ap), funcProps(fp){}
		Propertys(
			Type type
		) : clstype(type),attrCount(0), funcCount(0), attrProps(&Fields::vNone), funcProps(&Methods::vNone) {}
		template <u32 NF>
		Propertys(
			Type type,
			const Methods(&fp)[NF]
		) : clstype(type),attrCount(0), funcCount(NF - 1), attrProps(&Fields::vNone), funcProps(fp){}
		template <u32 NA>
		Propertys(
			Type type,
			const Fields(&ap)[NA]
		) : clstype(type), funcCount(0), attrCount(NA - 1), attrProps(ap), funcProps(&Methods::vNone){}
	public:
		template <u32 NA, u32 NF>
		void setPropertys(
			Type type,
			const Fields(&ap)[NA],
			const Methods(&fp)[NF]
		)
		{
			if (type != clstype)return;
			attrCount = (NA - 1); 
			funcCount = (NF - 1); 
			attrProps = (ap); 
			funcProps = (fp);
		}
		template <u32 NF>
		void setPropertys(
			Type type,
			const Methods(&fp)[NF]
		)
		{
			if (type != clstype)return;
			attrCount = 0;
			funcCount = (NF - 1);
			attrProps = 0;
			funcProps = (fp);
		}
	public:
		Method getMehod(const char* name)const
		{
			const Methods* prop = funcProps;
			while (prop->func != vNull)
			{
				const char* desc = prop->desc;
				if (!strcmp(name,desc))
				{
					return{ 0, clstype,prop };
				}
				prop++;
			}
			const BaseTypes* cprop = clstype.getBaseTypes();
			while (cprop->rtti)
			{
				Method closure = cprop->rtti->getPropertys().getMehod(name);
				if (closure.prop->type)return{ cprop->off + closure.offset,closure.prop->type,closure.prop };
				cprop++;
			}
			LOG_E("Can't Found FuncProperty:%s", name);
			return{ 0,Type::vNone, prop };
		}
		Field  getField(const char* name)const
		{
			const Fields* prop = attrProps;
			while (prop->clsType)
			{
				const char* desc = prop->desc;
				if (!strcmp(desc, name))
				{
					return{ 0, clstype,prop };
				}
				prop++;
			}
			const BaseTypes* cprop = clstype.getBaseTypes();
			while (cprop->rtti)
			{
				Field closure = cprop->rtti->getPropertys().getField(name);
				if (closure.prop->type)return{ cprop->off + closure.offset,closure.prop->type,closure.prop };
				cprop++;
			}
			LOG_E("Can't Found FuncProperty:%s", name);
			return{ 0,Type::vNone, prop };
		}
		u32    getFieldSize()const { return attrCount; }
		u32    getMethodSize()const { return funcCount; }
		Method getMehod(u32 index)const
		{
			if (index < funcCount)return{ 0, clstype,&funcProps[index] };
			const BaseTypes* cprop = clstype.getBaseTypes();
			if (cprop->rtti)
			{
				return cprop->rtti->getPropertys().getMehod(funcCount - index);
			}
			return{ 0, Type::vNone,&funcProps[funcCount] };
		}
		Field  getField(u32 index)const
		{
			if (index < attrCount)return{ 0, clstype,&attrProps[index] };
			const BaseTypes* cprop = clstype.getBaseTypes();
			if (cprop->rtti)
			{
				return cprop->rtti->getPropertys().getField(attrCount - index);
			}
			return{ 0, Type::vNone,&attrProps[attrCount] };
		}
		const Fields*  getFields()const { return attrProps; }
		const Methods* getMehods()const { return funcProps; }
		Type   getClassType()const { return clstype; }
		Enum   getEnums()const {
			if (clstype.getTypeId() == TypeId::enu) {
				Method method = getMehod("GetEnums");
				if (method) {
					return method.invoke<Enum>((Struct *)0);
				}
			}
			return{ 0,nullptr };
		}
	private:
		Type clstype;
		u32 attrCount;
		u32 funcCount;
		const Fields* attrProps;
		const Methods* funcProps;
	};
}
#endif
