#ifndef GUARD_display_h__
#define GUARD_display_h__
#include "../hpp/reflection.h"
namespace ts
{
	void display(Type type,Struct* str,int depth) {
		cachar* cls = type.getName();

		LOG_D(depth,"%s{}", cls);
		Propertys& propertys = type.getPropertys();
		const Fields* attr = propertys.getFields();
		for (int i = 0; i < propertys.getFieldSize(); ++i) {
			cachar* name = attr->getDesc();
			cachar* tname = attr->getType().getName();
			double value = 0;
			char*  string_value;
			switch (attr->getType().getTypeId())
			{
			case TypeId::u32:
				attr->set(str, (u32)i);
				attr->get<u32>(str, value);
				break;
			case TypeId::s32:
				attr->set(str, (s32)i);
				attr->get<s32>(str, value);
				break;
			case TypeId::u8:
				attr->set(str, (u8)i);
				attr->get<u8>(str, value);
				break;
			case TypeId::s16:
				attr->set(str, (s16)i);
				attr->get<s16>(str, value);
				break;
			case TypeId::u16:
				attr->set(str, (u16)i);
				attr->get<u16>(str, value);
				break;
			case TypeId::f64:
				attr->set(str, (f64)i);
				attr->get<f64>(str, value);
				break;
			case TypeId::f32:
				attr->set(str, (f32)i);
				attr->get<f32>(str, value);
				break;
			case TypeId::astr:
				attr->set(str, (char*)"test");
				attr->get<char*>(str, string_value);
				LOG_D(depth, "%s[0x%x].%s == %s[%s]", cls, str, name, attr->getType().getName(), string_value);
				attr++;
				continue;
				break;
			case TypeId::enu:
				attr->set(str, attr->getType().getPropertys().getEnums()[2].flag);
				attr->get<u32>(str, value);
				LOG_D(depth, "%s[0x%x].%s == %s",cls,str,name, attr->getType().getPropertys().getEnums()[(int)value].name);
				attr++;
				continue;
				break;
			case TypeId::ptr:
				if (attr->getType() == TClass<f32*>::type) {
					attr->set(str, (f32*)0x123890);
					f32* fptr;
					attr->get<f32*>(str, fptr);
					LOG_D(depth, "%s[0x%x].%s == %s[0x%x]", cls, str, name, attr->getType().getName(), fptr);
					attr++;
					continue;
				}
				break;
			case TypeId::arr:
				if (attr->getType().isKindOf(TClass<char[]>::type)) {
					if (attr->getType().getLength() == 15) {
						auto p= attr->ref<char[]>(str);
						char* pstr = (char*)p;
						strcpy((char*)p, "array");
						LOG_D(depth, "%s[0x%x].%s == %s[\"%s\"]", cls, str, name, attr->getType().getName(), p);
						attr++;
					}
					continue;
				}
				break;
			default:
				//name = "unknown";
				break;
			}
			LOG_D(depth, "%s[0x%x].%s == %s[%f]", cls, str, name, tname, value);
			attr++;
		}
		const Methods* func = propertys.getMehods();
		for (int i = 0; i < propertys.getMethodSize(); ++i) {
			cachar* desc = func->getDesc();
			Type type = func->getFuncType();
			LOG_D(depth, "%s[0x%x].%s == %s", cls, str, desc, type.getName());
			func++;
		}

		for (BaseTypes* typeprops = type.getBaseTypes(); typeprops->rtti; typeprops++) {
			cachar* name = typeprops->rtti->getName();
			display(*typeprops->rtti, typeprops->fromDerived(str),depth + 1);
		}
	}
	void display(Object* obj) {
		Type type = obj->getType();
		display(type, obj,0);
		LOG_P("\r\n");
	}
	void display(Type type, Struct* str)
	{
		display(type, str, 0);
		LOG_P("\r\n");
	}
}
#endif // GUARD_display_h__
