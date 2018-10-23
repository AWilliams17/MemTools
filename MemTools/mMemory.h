#pragma once
#include <string>

#ifdef MEMTOOLS_EXPORTS  
#define MEMTOOLS_API __declspec(dllexport)   
#else  
#define MEMTOOLS_API __declspec(dllimport)   
#endif

namespace mMemoryFunctions {
	MEMTOOLS_API LPCVOID mReadMemory(const std::wstring &PROCESS_NAME, const LPCVOID &READ_LOCATION, const size_t &READ_SIZE);
	MEMTOOLS_API bool mWriteMemory(const std::wstring &PROCESS_NAME, const LPVOID &WRITE_LOCATION, const LPCVOID &DATA_TO_WRITE, const size_t &DATA_SIZE);
	MEMTOOLS_API bool mInjectDLL(const std::wstring &PROCESS_NAME, const std::string &DLL_LOCATION);
}
