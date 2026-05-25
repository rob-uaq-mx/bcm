#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

/**
@file componentmgr.h
@brief Win32 DLL manager singleton class.

A DLL class for managing Win32 dynamic linked libraries
that contain BCM components.
*/

#include <bcm/component.h>
#include <bcm/win32/dll.h>
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
        @brief Win32 DLL manager singleton class.

        A DLL class for managing Win32 dynamic linked libraries
	that contain BCM components.
        */

	class ComponentManager
	{
		using GET_COMPONENT = Component *(*)();
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
		LoadComponentResult loadComponent(LPCTSTR dllName)
		{
			Dll *dll = new Dll;
			if (dll->open(dllName) == false) {
				delete dll;
				return LC_NODLL;
			}
			auto lpGetComponent = reinterpret_cast<GET_COMPONENT>(dll->getProc("getComponent"));
			if (lpGetComponent == nullptr) {
				delete dll;
				return LC_NOCOMPONENT;
			}
			Component *component = lpGetComponent();
			if (dllMap.find(component->getID()) != dllMap.end()) {
				delete dll;
				return LC_ALREADYUSED;
			}
			ComponentData cd;
			cd.name = component->getName();
			cd.dll = dll;
			dllMap[component->getID()] = cd;
			return LC_OK;
		}
		bool releaseComponent(const char *id)
		{
			auto it = dllMap.find(id);
			if (it != dllMap.end()) {
				delete it->second.dll;
				dllMap.erase(it);
				return true;
			}
			return false;
		}
		GetComponentResult getComponent(/*in*/ const char *id, /*out*/ Component **component)
		{
			auto it = dllMap.find(id);
			if (it == dllMap.end()) {
				*component = nullptr;
				return GC_UNREGISTERED;
			}
			Dll *dll = it->second.dll;
			auto lpGetComponent = reinterpret_cast<GET_COMPONENT>(dll->getProc("getComponent"));
			if (lpGetComponent == nullptr) {
				*component = nullptr;
				return GC_NOCOMPONENT;
			}
			*component = lpGetComponent();
			return (*component != nullptr) ? GC_OK : GC_NOCOMPONENT;
		}
	};

} // namespace bcm

#endif



