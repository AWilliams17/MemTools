#pragma once
#include <string>

#ifdef MEMTOOLS_EXPORTS  
#define MEMTOOLS_API __declspec(dllexport)   
#else  
#define MEMTOOLS_API __declspec(dllimport)   
#endif

namespace mMemoryFunctions {
	// Returns the value read on success, NULL otherwise.
	MEMTOOLS_API LPCVOID mReadMemory(const std::wstring &PROCESS_NAME, const LPCVOID &READ_LOCATION, const size_t &READ_SIZE);
	// Returns true on a successful write, false otherwise.
	MEMTOOLS_API bool mWriteMemory(const std::wstring &PROCESS_NAME, const LPVOID &WRITE_LOCATION, const LPCVOID &DATA_TO_WRITE, const size_t &DATA_SIZE);
	// Returns true on a successful injection, false otherwise.
	MEMTOOLS_API bool mInjectDLL(const std::wstring &PROCESS_NAME, const std::string &DLL_LOCATION);
}
