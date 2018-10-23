#pragma once
#include <string>

#ifdef MEMTOOLS_EXPORTS  
#define MEMTOOLS_API __declspec(dllexport)   
#else  
#define MEMTOOLS_API __declspec(dllimport)   
#endif

namespace mProcessFunctions {
	// // See https://docs.microsoft.com/en-us/windows/desktop/procthread/process-security-and-access-rights
	enum MEMTOOLS_API ProcessAccess : DWORD {
		Full = PROCESS_ALL_ACCESS,
		ReadOnly = PROCESS_VM_OPERATION | PROCESS_VM_READ,
		WriteOnly = PROCESS_VM_OPERATION | PROCESS_VM_WRITE,
		QueryInformation = PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
		ReadWrite = ReadOnly | WriteOnly
	};

	// Returns a handle to the specified process, NULL otherwise.
	MEMTOOLS_API HANDLE mGetHandle(const std::string &PROCESSNAME, const ProcessAccess DESIREDACCESS);
	// Returns the PID of the specified process, NULL otherwise.
	MEMTOOLS_API DWORD mGetPID(const std::string &PROCESSNAME);
	// If the handle passed is not valid, the handle is CLOSED and false is returned. Otherwise, the handle is unaffected and true is returned.
	MEMTOOLS_API bool mValidateHandle(HANDLE &ProcessHandle);
	// Attempts to get the address of a loaded module in a process. Returns the address on success, NULL otherwise.
	MEMTOOLS_API DWORD mGetModuleAddress(const std::string &PROCESS_NAME, const std::string &MODULE_NAME);
}
