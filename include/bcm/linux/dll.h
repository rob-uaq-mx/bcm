#ifndef DLL_H
#define DLL_H

#include <cstdlib>
#include <dlfcn.h>

namespace bcm {

	class Dll
	{
	protected:
		void *handle;
	public:
		Dll() : handle(nullptr)
		{
		}
		bool open(const char *fileName)
		{
			handle = dlopen(fileName, RTLD_LAZY);
			return handle != nullptr;
		}
		void close()
		{
			if (handle != nullptr)
				dlclose(handle);
		}
		bool isOpen()
		{
			return handle != nullptr;
		}
		void *getProc(const char *loaderName)
		{
			return dlsym(handle, loaderName);
		}
		virtual ~Dll()
		{
			close();
		}
	};

} // namespace bcm

#endif
