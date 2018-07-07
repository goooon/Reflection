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
	struct Convertor
	{
		void* ptr;
		TypeIdMask idMask;
		Convertor() :ptr(0), idMask(TypeId::v) {}
		Convertor(const void* v, Type type) :idMask(type.getTypeId()) {
			ptr = const_cast<void*>(v);
		}
		operator u8() { return operator u64(); }
		operator s8() { return operator u64(); }
		operator u16() { return operator u64(); }
		operator s16() { return operator u64(); }
		operator u32() { return operator u64(); }
		operator s32() { return operator u64(); }
		operator u64() {
			switch (idMask.getCate())
			{
			case TypeIdMask::CateN8:return *(u8*)ptr;
			case TypeIdMask::CateN16:return *(u16*)ptr;
			case TypeIdMask::CateN32:return *(u32*)ptr;
			case TypeIdMask::CateN64:return *(u64*)ptr;
			case TypeIdMask::CateF32:return *(f32*)ptr;
			case TypeIdMask::CateF64:return *(f64*)ptr;
			default:return 0;
			}
		}
		operator s64() { return operator u64(); }
		operator f32() {
			switch (idMask.getCate())
			{
			case TypeIdMask::CateN8:return *(u8*)ptr;
			case TypeIdMask::CateN16:return *(u16*)ptr;
			case TypeIdMask::CateN32:return *(u32*)ptr;
			case TypeIdMask::CateN64:return *(u64*)ptr;
			case TypeIdMask::CateF32:return *(f32*)ptr;
			case TypeIdMask::CateF64:return *(f64*)ptr;
			default:return 0;
			}
		}
		operator f64() {
			switch (idMask.getCate())
			{
			case TypeIdMask::CateN8:return *(u8*)ptr;
			case TypeIdMask::CateN16:return *(u16*)ptr;
			case TypeIdMask::CateN32:return *(u32*)ptr;
			case TypeIdMask::CateN64:return *(u64*)ptr;
			case TypeIdMask::CateF32:return *(f32*)ptr;
			case TypeIdMask::CateF64:return *(f64*)ptr;
			default:return 0;
			}
		}
		template <typename T>
		operator T() { return *(T*)ptr; }

		void operator = (u64 v) {
			switch (idMask.getCate())
			{
			case TypeIdMask::CateN8:*(u8*)ptr = v; break;
			case TypeIdMask::CateN16:*(u16*)ptr = v; break;
			case TypeIdMask::CateN32:*(u32*)ptr = v; break;
			case TypeIdMask::CateN64:*(u64*)ptr = v; break;
			case TypeIdMask::CateF32:*(f32*)ptr = v; break;
			case TypeIdMask::CateF64:*(f64*)ptr = v; break;
			default:
				return ;
			}
		}
		void operator = (s64 v) { return operator= ((u64)v); }
		void operator = (u32 v) { return operator= ((u64)v); }
		void operator = (s32 v) { return operator= ((u64)v); }
		void operator = (u16 v) { return operator= ((u64)v); }
		void operator = (s16 v) { return operator= ((u64)v); }

		void operator = (u8 v) { return operator= ((u64)v); }
		void operator = (s8 v) { return operator= ((u64)v); }
		void operator = (f32 v) {
			switch (idMask.getCate())
			{
			case TypeIdMask::CateN8:*(u8*)ptr = v; break;
			case TypeIdMask::CateN16:*(u16*)ptr = v; break;
			case TypeIdMask::CateN32:*(u32*)ptr = v; break;
			case TypeIdMask::CateN64:*(u64*)ptr = v; break;
			case TypeIdMask::CateF32:*(f32*)ptr = v; break;
			case TypeIdMask::CateF64:*(f64*)ptr = v; break;
			default:
				return;
			}
		}
		void operator = (f64 v) {
			switch (idMask.getCate())
			{
			case TypeIdMask::CateN8:*(u8*)ptr = v; break;
			case TypeIdMask::CateN16:*(u16*)ptr = v; break;
			case TypeIdMask::CateN32:*(u32*)ptr = v; break;
			case TypeIdMask::CateN64:*(u64*)ptr = v; break;
			case TypeIdMask::CateF32:*(f32*)ptr = v; break;
			case TypeIdMask::CateF64:*(f64*)ptr = v; break;
			default:
				return;
			}
		}
		template <typename T>
		void operator = (T v) { *(T*)ptr = v; }
	};
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
			Property(TypeOf<T>::type, desc, props),
			clsType(TypeOf<C>::type),
			getdata((StructData)(typename Type_Select<std::is_base_of<Object,C>::value, ObjectData, StructData>::Result)dpr)
		{
			off = 0;
			setdata = getdata;
			static_assert(!std::is_base_of<Struct,C>::value, "type_is_not_supported");
		}
		template <typename T, class C>Fields(T(C::* dpr) = 0, const char* desc = 0, PropertyDesc* props = vNull) :
			Property(TypeOf<T>::type, desc, props),
			clsType(TypeOf<C>::type),
			getdata((StructData)(typename Type_Select<std::is_base_of<Object,C>::value, ObjectData, StructData>::Result)((int(C::*))dpr))
		{
			off = static_cast<s32>((u8*)(C*)(typename C::RootType*)(Struct*)1 - (u8*)(Struct*)1);
			setdata = getdata;
			static_assert(std::is_base_of<Struct,C>::value, "type_is_not_supported");
		}
		template <typename T, class C>Fields(T(C::*get)()const = 0, void(C::*set)(T) = 0, const char* desc = 0, PropertyDesc* props = 0) :
			Property(TypeOf<T>::type, desc, props),
			clsType(TypeOf<C>::type)
		{
			off = static_cast<s32>((u8*)(C*)(typename C::RootType*)(Struct*)1 - (u8*)(Struct*)1);
			castFunction(get,set);
		}
		template <typename T, class C>Fields(T(C::*get)()const = 0, const char* desc = 0, PropertyDesc* props = 0) :
			Property(TypeOf<T>::type, desc, props),
			clsType(TypeOf<C>::type)
		{
			off = (int)(C*)(typename C::RootType*)(Struct*)1 - (int)(Struct*)1;
			castFunction(get, nullptr);
		}
		template <typename T, class C>Fields(T(C::*get)() = 0, const char* desc = 0, PropertyDesc* props = 0) :
			Property(TypeOf<T>::type, desc, props),
			clsType(TypeOf<C>::type)
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
			Type outtype = TypeOf<T>::type;
			if (setdata != getdata) {
				LOG_E("it's a function attribute,not supported refference");
				return nullptr;
			}
			else {
				if (outtype != type &&
					(TypeIdMask::TYPEID_CONV_MASK & (u32)outtype.getTypeId()) != (TypeIdMask::TYPEID_CONV_MASK & (u32)type.getTypeId()) &&
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
			Type outtype = TypeOf<T>::type;
			if (setdata != getdata) {
				typedef T(Struct::*AttrPtr)(void);
				if (outtype != type &&
					(TypeIdMask::TYPEID_CONV_MASK & (u32)outtype.getTypeId()) != (TypeIdMask::TYPEID_CONV_MASK & (u32)type.getTypeId()) &&
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
					(TypeIdMask::TYPEID_CONV_MASK & (u32)outtype.getTypeId()) != (TypeIdMask::TYPEID_CONV_MASK & (u32)type.getTypeId()) &&
					!type.isKindOf(outtype))
				{
					LOG_E("%s casting to %s", type.getName(), outtype.getName());
					return vFalse;
				}
				typedef T(Struct::*TStructData);
				t = Convertor(&(c->*(TStructData)(StructData)setdata),type);
				return vTrue;
			}
		}
		template <typename T>b32  set(Struct* c, T v)const
		{
			if (type == Type::vNone)return vFalse;
			if (setdata != getdata) {
				typedef void(Struct::*AttrPtr)(T);
				Type itype = TypeOf<T>::type;
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
				Type from = TypeOf<T>::type;
				if (from != type &&
					(TypeIdMask::TYPEID_CONV_MASK & (u32)from.getTypeId()) != (TypeIdMask::TYPEID_CONV_MASK & (u32)type.getTypeId()) &&
					!from.isKindOf(type))
				{
					LOG_E("%s can't cast to %s", from.getName(), type.getName());
					return vFalse;
				}
				typedef T(Struct::*TStructData);
				Convertor(&(c->*(TStructData)setdata), type) = v;
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
	
	struct Delegate {
	public:
		Delegate() :ccf(0), mf(0) {}
		template<typename R, typename C, typename ...Args>
		Delegate(R(C::*mf)(Args...)) :
			bt(FuncTraits<R(*)(Args...)>::Rtti::prop->rtti->getBaseTypes()),
			ccf(reinterpret_cast<int (*)(void*)>((R(*)(R, Struct, Args...))&FuncTraits<R(Struct::*)(Args...)>::rcall)),
			count(sizeof...(Args)) {
			typedef typename Type_Select<std::is_base_of<Object, C>::value, Object, Struct>::Result Refflector;
			typedef R(Refflector::*ObjFunc)(Args...);
			typedef R(C::*ClsFunc)(Args...);
			typedef void* (Refflector::*Func)(void*);
			this->mf = (void* (Struct::*)(void*))(Func)(ObjFunc)(ClsFunc)mf;
		}
		
		template<typename C, typename ...Args>
		Delegate(void(C::*mf)(Args...)) :
			bt(FuncTraits<void(*)(Args...)>::Rtti::prop->rtti->getBaseTypes()),
			ccf(reinterpret_cast<int (*)(void*)>((void(*)(void*, Struct, Args...))&FuncTraits<void*(Struct::*)(Args...)>::rcall)),
			count(sizeof...(Args)) {
			typedef typename Type_Select<std::is_base_of<Object, C>::value, Object, Struct>::Result Refflector;
			typedef void(Refflector::*ObjFunc)(Args...);
			typedef void(C::*ClsFunc)(Args...);
			typedef void* (Refflector::*Func)(void*);
			this->mf = (void* (Struct::*)(void*))(Func)(ObjFunc)(ClsFunc)mf;
		}
		template<typename R, typename C, typename ...Args>
		Delegate(R(C::*mf)(Args...)const) :
			bt(FuncTraits<R(*)(Args...)>::Rtti::prop->rtti->getBaseTypes()),
			ccf(reinterpret_cast<int (*)(void*)>((R(*)(R, Struct, Args...))&FuncTraits<R(Struct::*)(Args...)>::rcall)),
			count(sizeof...(Args)) {
			typedef typename Type_Select<std::is_base_of<Object, C>::value, Object, Struct>::Result Refflector;
			typedef R(Refflector::*ObjFunc)(Args...);
			typedef R(C::*ClsFunc)(Args...);
			typedef void* (Refflector::*Func)(void*);
			this->mf = (void* (Struct::*)(void*))(Func)(ObjFunc)(ClsFunc)mf;
		}
		template<typename C, typename ...Args>
		Delegate(void(C::*mf)(Args...)const) :
			bt(FuncTraits<void(*)(Args...)>::Rtti::prop->rtti->getBaseTypes()),
			ccf(reinterpret_cast<int (*)(void*)>((void(*)(void*, Struct, Args...))&FuncTraits<void*(Struct::*)(Args...)>::rcall)),
			count(sizeof...(Args)) {
			typedef typename Type_Select<std::is_base_of<Object, C>::value, Object, Struct>::Result Refflector;
			typedef void(Refflector::*ObjFunc)(Args...);
			typedef void(C::*ClsFunc)(Args...);
			typedef void* (Refflector::*Func)(void*);
			this->mf = (void* (Struct::*)(void*))(Func)(ObjFunc)(ClsFunc)mf;
		}
		template<typename R, typename C, typename...  Args>
		bool invoke(R& r, C* c, Args&&... args)const {
			if (sizeof...(Args) != count) {
				LOG_E("Params Count Should be %d Not %d", count, (int)sizeof...(Args));
				return false;
			}
			typedef R(Struct::*MembFunc)(Args...);
			typedef int(*CallFunc)(ValuePointer*, Struct*, R(Struct::*)(Args...), ValuePointer*...);
			CallFunc  cf = (CallFunc)ccf;
			typename Reff2Value<R>::Type rr;
			int result = cf(&ValuePointer(&rr), (Struct*)c, (MembFunc)mf, &ValuePointer(&args)...);
			if (result) {
				if (result < 0) {
					LOG_E("Return Type Should Be %s Not %s", bt[0].rtti->getName(), TypeOf<R>::type().getName());
				}
				else {
					Type type[] = { TypeOf<Args>::type... };
					LOG_E("Argument %d Type Should Be %s Not %s", result, bt[result].rtti->getName(), type[result - 1].getName());
				}
				return false;
			}
			r = rr;
			return true;
		}
		template<typename R, typename C, typename...  Args>
		R call(C* c, Args&&... args)const {
			typedef R(Struct::*MembFunc)(Args...);
			return (c->*(MembFunc)mf)(std::forward<Args>(args)...);
		}
		template<typename C, typename ...Args >
		bool invoke(C* c, Args&&... args)const {
			if (sizeof...(Args) != count) {
				LOG_E("Params Count Should be %d Not %d", count, (int)sizeof...(Args));
				return false;
			}
			typedef void(Struct::*MembFunc)(Args...);
			typedef int (*CallFunc)(ValuePointer*, Struct*, void(Struct::*)(Args...), ValuePointer*...);
			CallFunc  cf = (CallFunc)ccf;
			void* r = 0;
			int result = cf(&ValuePointer(&r), (Struct*)c, (MembFunc)mf, &ValuePointer(&args)...);
			if (result) {
				Type type[] = { TypeOf<Args>::type... };
				LOG_E("Argument %d Type Should Be %s Not %s", result, bt[result].rtti->getName(), type[result - 1].getName());
				return false;
			}
			return true;
		}
		operator bool()const { return mf; }
		const TypeNodes* getArgTypes()const { return bt; }
	private:
		unsigned int count;
		const TypeNodes* bt;
		void* (Struct::*mf)(void*);
		int (*ccf)(void*);
	};

	struct Methods : public Property
	{
	private:
		typedef void* (Object::*Func)(void*);
	public:
		Methods(){}
		template<typename R, typename C, typename... Args>
		Methods(R(C::*mf)(Args...)const = 0, const char* desc = 0, PropertyDesc* props = 0) :
			Property(TypeOf<R>::type, desc, props), dele(mf) {};
		template<typename R, typename C, typename... Args>Methods(R(C::*mf)(Args...) = 0, const char* desc = 0, PropertyDesc* props = 0) :
			Property(TypeOf<R>::type, desc, props),dele(mf) {};
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
			// if (prop.ret != TypeOf<typename removeConst<R>::Type>::type) {
			// 	LOG_E("Return Type %s != %s", prop.ret.getName(), Type(TypeOf<R>::type).getName());
			// }
			return (str->*((typename F::RawMemberFunc)prop.dele.mf))(std::forward<Args>(args)...);
		}
	public:
		template<typename R, typename ...Args>bool invoke(R& r,Struct* str, Args&&... args)const
		{
			return dele.invoke(r,str, std::forward<Args>(args)...);
		}
		template<typename R, typename ...Args>bool invoke(Struct* str, Args&&... args)const
		{
			return dele.invoke(str, std::forward<Args>(args)...);
		}
		template<typename R, typename ...Args>R call(Struct* str, Args&&... args)const
		{
			return dele.call<R>(str, std::forward<Args>(args)...);
		}
		operator bool() const{ return dele.operator bool(); }
		const TypeNodes* getArgTypes()const { return dele.getArgTypes(); }
		Delegate dele;
	private:

	};
	//zhihe::Methods Methods::vNone;

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
		template<typename R, typename ...Args>bool invoke(R& r,Struct* str, Args&&... args)const
		{
			return prop->invoke<R>(r,str, std::forward<Reff2Value<Args>::Type>((Reff2Value<Args>::Type)(args))...);
		}
		template<typename ...Args>bool invoke(Struct* str, Args&&... args)const
		{
			return prop->invoke<void>(str, std::forward<typename Reff2Value<Args>::Type>((typename Reff2Value<Args>::Type)(args))...);
		}
		template<typename R, typename ...Args>R call(Struct* str, Args&&... args)const
		{
			return prop->call<R>(str, std::forward<typename Reff2Value<Args>::Type>((typename Reff2Value<Args>::Type)(args))...);
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
		) : clstype(type),attrCount(0), funcCount(0), attrProps(&Fields::vNone), funcProps(&EndMethod) {}
		template <u32 NF>
		Propertys(
			Type type,
			const Methods(&fp)[NF]
		) : clstype(type),attrCount(0), funcCount(NF - 1), attrProps(&Fields::vNone), funcProps(fp){}
		template <u32 NA>
		Propertys(
			Type type,
			const Fields(&ap)[NA]
		) : clstype(type), funcCount(0), attrCount(NA - 1), attrProps(ap), funcProps(&EndMethod){}
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
		Method getMethod(const char* name)const
		{
			const Methods* prop = funcProps;
			while (*prop)
			{
				const char* desc = prop->desc;
				if (!strcmp(name,desc))
				{
					return{ 0, clstype,prop };
				}
				prop++;
			}
			const TypeNodes* cprop = clstype.getBaseTypes();
			while (cprop->rtti)
			{
				Method closure = cprop->rtti->getPropertys().getMethod(name);
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
			const TypeNodes* cprop = clstype.getBaseTypes();
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
		Method getMethod(u32 index)const
		{
			if (index < funcCount)return{ 0, clstype,&funcProps[index] };
			const TypeNodes* cprop = clstype.getBaseTypes();
			if (cprop->rtti)
			{
				return cprop->rtti->getPropertys().getMethod(funcCount - index);
			}
			return{ 0, Type::vNone,&funcProps[funcCount] };
		}
		Field  getField(u32 index)const
		{
			if (index < attrCount)return{ 0, clstype,&attrProps[index] };
			const TypeNodes* cprop = clstype.getBaseTypes();
			if (cprop->rtti)
			{
				return cprop->rtti->getPropertys().getField(attrCount - index);
			}
			return{ 0, Type::vNone,&attrProps[attrCount] };
		}
		const Fields*  getFields()const { return attrProps; }
		const Methods* getMethods()const { return funcProps; }
		Type   getClassType()const { return clstype; }
		Enum   getEnums()const {
			if (clstype.getTypeId() == TypeId::enu) {
				Method method = getMethod("GetEnums");
				if (method) {
					return method.call<Enum>((Struct *)0);
				}
			}
			return{ 0,nullptr };
		}
	protected:
		static Methods EndMethod;
	private:
		Type clstype;
		u32 attrCount;
		u32 funcCount;
		const Fields* attrProps;
		const Methods* funcProps;
	};
	Methods Propertys::EndMethod;
}
#endif
