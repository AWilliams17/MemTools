#pragma once
#include <string>

#ifdef MEMTOOLS_EXPORTS  
#define MEMTOOLS_API __declspec(dllexport)   
#else  
#define MEMTOOLS_API __declspec(dllimport)   
#endif

namespace mProcessFunctions {
	enum MEMTOOLS_API ProcessAccess : DWORD {
		Full = PROCESS_ALL_ACCESS,
		ReadOnly = PROCESS_VM_OPERATION | PROCESS_VM_READ,
		WriteOnly = PROCESS_VM_OPERATION | PROCESS_VM_WRITE,
		ReadWrite = ReadOnly | WriteOnly
	};

	MEMTOOLS_API HANDLE mGetHandle(const std::wstring &PROCESSNAME, const ProcessAccess DESIREDACCESS);
	MEMTOOLS_API DWORD mGetPID(const std::wstring &PROCESSNAME);
	MEMTOOLS_API bool mValidateHandle(HANDLE &ProcessHandle);
}
