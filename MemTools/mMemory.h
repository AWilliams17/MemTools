#pragma once
#include <string>

#ifdef MEMTOOLS_EXPORTS  
#define MEMTOOLS_API __declspec(dllexport)   
#else  
#define MEMTOOLS_API __declspec(dllimport)   
#endif

namespace mMemoryFunctions {
	LPCVOID mReadMemory(const HANDLE &PROCESS_HANDLE, const LPCVOID &READ_LOCATION);
	void mWriteMemory(const HANDLE &PROCESS_HANDLE, const LPVOID &WRITE_LOCATION, const LPCVOID &DATA_TO_WRITE);
	void mInjectDLL(const int &PROCESS_ID, const std::string &DLL_LOCATION);
}
