#ifndef DLL_H
#define DLL_H

/**
@file dll.h
@brief Win32 DLL class.

A DLL class for handling Win32 dynamic linked libraries.
*/


#include <windows.h>

namespace bcm {

        /**
        @class Dll
        @brief Win32 DLL class.

        This class defines an object oriented API for Win32
        dynamic linked libraries.
        */

	class Dll {
	protected:
		HINSTANCE hDll;
	public:
		Dll() : hDll(NULL)
		{
		}
		bool open(LPCTSTR fileName)
		{
			hDll = LoadLibrary(fileName);
			return hDll != NULL;
		}
		void close()
		{
			if (isOpen())
				FreeLibrary(hDll);
		}
		bool isOpen()
		{
			return hDll != NULL;
		}
		FARPROC getProc(LPCSTR procName)
		{
			return GetProcAddress(hDll, procName);
		}
		virtual ~Dll()
		{
			close();
		}
	};

} // namespace pcm

#endif

