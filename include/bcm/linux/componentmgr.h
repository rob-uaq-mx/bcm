#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

/**
@file dll.h
@brief Linux DLL manager singleton class.

A DLL class for managing Linux dynamic linked libraries
that contain BCM components.
*/

#include <bcm/component.h>
#include <bcm/linux/dll.h>
#include <string>
#include <map>
#include <iostream>

namespace bcm {

	enum LoadComponentResult {
		LC_NODLL,
		LC_NOCOMPONENT,
		LC_ALREADYUSED,
		LC_OK
	};

	enum GetComponentResult {
		GC_UNREGISTERED,
		GC_NOCOMPONENT,
		GC_INCOMPLETE,
		GC_OK
	};

        /**
        @class ComponentManager
        @brief Linux DLL manager singleton class.

        A DLL class for managing Linux dynamic linked libraries
	that contain BCM components.
        */

	class ComponentManager
	{
		typedef Component *(*GET_COMPONENT)(GetComponentResult *result);
/*#ifdef _UNICODE
		typedef std::wstring tstring;
#else
		typedef std::string tstring;
#endif*/
		struct ComponentData {
			std::string name;
			Dll *dll;
		};
		std::map<std::string, ComponentData> dllMap;
	protected:
		ComponentManager()
		{
		}
	public:
		static ComponentManager &instance()
		{
			static ComponentManager object;
			return object;
		}
		LoadComponentResult loadComponent(const char *dllName)
		{
			Dll *dll = new Dll;
			if (dll->open(dllName) == false)
				return LC_NODLL;
			GET_COMPONENT lpGetComponent = (GET_COMPONENT)dll->getProc("getComponent");
			if (lpGetComponent == (GET_COMPONENT)NULL)
				return LC_NOCOMPONENT;
			else {
				GetComponentResult result;
				Component *component = lpGetComponent(&result);
				if (dllMap.find(component->getID()) != dllMap.end())
					return LC_ALREADYUSED;
				ComponentData cd;
				cd.name = component->getName();
				cd.dll = dll;
				dllMap[component->getID()] = cd;
			}
			return LC_OK;
		}
		bool releaseComponent(const char *id)
		{
			std::map<std::string, ComponentData>::iterator it = dllMap.find(id);
			if (it != dllMap.end()) {
				delete it->second.dll;
				dllMap.erase(it);
				return true;
			}
			return false;
		}
		GetComponentResult getComponent(/*in*/ const char *id, /*out*/ Component **component)
		{
			std::map<std::string, ComponentData>::iterator it = dllMap.find(id);
			if (it == dllMap.end()) {
				*component = 0;
				return GC_UNREGISTERED;
			}
			Dll *dll = it->second.dll;
			GET_COMPONENT lpGetComponent = (GET_COMPONENT)dll->getProc("getComponent");
			if (lpGetComponent == (GET_COMPONENT)NULL) {
				*component = 0;
				return GC_NOCOMPONENT;
			}
			GetComponentResult result;
			*component = (*lpGetComponent)(&result);
			return result;
		}
	};

} // namespace bcm

#endif

