#pragma once

#ifdef MEMTOOLS_EXPORTS  
#define MEMTOOLS_API __declspec(dllexport)   
#else  
#define MEMTOOLS_API __declspec(dllimport)   
#endif

namespace mProcessFunctions {
	// See https://docs.microsoft.com/en-us/windows/desktop/procthread/process-security-and-access-rights
	enum MEMTOOLS_API ProcessAccess : DWORD {
		Full = PROCESS_ALL_ACCESS,
		ReadOnly = PROCESS_VM_OPERATION | PROCESS_VM_READ,
		WriteOnly = PROCESS_VM_OPERATION | PROCESS_VM_WRITE,
		QueryInformation = PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
		ReadWrite = ReadOnly | WriteOnly
	};

	MEMTOOLS_API typedef enum {
		UNKNOWN,
		PWIN32,
		PWIN64
	} Bitness;

	// Returns a handle to the specified process, NULL otherwise.
	MEMTOOLS_API HANDLE mGetHandle(const std::string &PROCESS_NAME, const ProcessAccess DESIRED_ACCESS);

	// Returns the PID of the specified process, NULL otherwise.
	MEMTOOLS_API DWORD mGetPID(const std::string &PROCESS_NAME);

	// If the handle passed is not valid, the handle is CLOSED and false is returned. Otherwise, the handle is unaffected and true is returned.
	MEMTOOLS_API bool mValidateHandle(HANDLE &ProcessHandle);

	// Attempts to get the address of a loaded module in a process. Returns the address on success, NULL otherwise.
	MEMTOOLS_API uintptr_t mGetModuleAddress(const std::string &PROCESS_NAME, const std::string &MODULE_NAME);

	// Attempts to get the address of a loaded module in a process. Returns the address on success, NULL otherwise. Note: The handle is NOT closed.
	MEMTOOLS_API uintptr_t mGetModuleAddress(const HANDLE &PROCESS_HANDLE, const std::string &MODULE_NAME);

	// Returns a handle to the specified module in the process, NULL otherwise. Note: The handle is NOT closed.
	MEMTOOLS_API HMODULE mGetModuleHandle(const std::string &PROCESS_NAME, const std::string &MODULE_NAME);

	// Returns a handle to the specified module in the process, NULL otherwise.
	MEMTOOLS_API HMODULE mGetModuleHandle(const HANDLE &PROCESS_HANDLE, const std::string &MODULE_NAME);

	// Attempts to get the offset of an exported function in a DLL. Returns the offset on success, NULL otherwise. NOTE: The handle is NOT closed.
	MEMTOOLS_API DWORD mGetExportedFunctionOffset(const HMODULE &MODULE_HANDLE, const std::string &TARGET_FUNCTION);

	// Determines the bitness of a specified module. Returns UNKNOWN from the Bitness enum if it can't be determined.
	MEMTOOLS_API Bitness mGetModuleBitness(const HMODULE &MODULE_HANDLE);
}