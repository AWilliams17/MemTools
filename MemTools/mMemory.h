#pragma once
#include <string>

#ifdef MEMTOOLS_EXPORTS  
#define MEMTOOLS_API __declspec(dllexport)
#else  
#define MEMTOOLS_API __declspec(dllimport)
#endif

namespace mMemoryFunctions {
	// Returns the value read on success, NULL otherwise.
	MEMTOOLS_API LPCVOID mReadMemory(const std::string &PROCESS_NAME, const uintptr_t &READ_LOCATION, const size_t &READ_SIZE);
	// Returns the value read on success, NULL otherwise. Note: The handle is NOT closed.
	MEMTOOLS_API LPCVOID mReadMemory(const HANDLE &PROCESS_HANDLE, const uintptr_t &READ_LOCATION, const size_t &READ_SIZE);

	// Returns true on a successful write, false otherwise.
	MEMTOOLS_API bool mWriteMemory(const std::string &PROCESS_NAME, const uintptr_t &WRITE_LOCATION, const LPCVOID &DATA_TO_WRITE, const size_t &DATA_SIZE);
	// Returns true on a successful write, false otherwise. Note: The handle is NOT closed.
	MEMTOOLS_API bool mWriteMemory(const HANDLE &PROCESS_HANDLE, const uintptr_t &WRITE_LOCATION, const LPCVOID &DATA_TO_WRITE, const size_t &DATA_SIZE);

	// Returns the address of the first occurrence of a pattern in the target process' memory. NOTE: The handles are NOT closed.
	MEMTOOLS_API DWORD mGetPatternAddress(const char &PATTERN, const char &PATTERN_MASK, const HANDLE &PROCESS_HANDLE, const HMODULE MODULE_HANDLE);

	// Returns true on a successful injection, false otherwise.
	MEMTOOLS_API bool mInjectDLL(const std::string &PROCESS_NAME, const std::string &DLL_LOCATION);
}