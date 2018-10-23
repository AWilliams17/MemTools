# MemTools - A Memory Hacking Library written in C  
This is an effort to write an easy to use library for performing  
common memory-related operations when writing game hacks.  
All of the functions are made to be stateless and functional.  
  
# The Library
```c 
// -Functions List-
// Note: Use GetLastError() for more information on failures.
// Note: All functions relating to handles other than mIsHandleValid and mGetHandle close their handles after usage.

// 			-Functions inside the mMemoryFunctions namespace-
// Returns the value read on success, NULL otherwise.
LPCVOID mReadMemory(const std::wstring &PROCESS_NAME, const LPCVOID &READ_LOCATION, const size_t &READ_SIZE);
// Returns true on a successful write, false otherwise.
bool mWriteMemory(const std::wstring &PROCESS_NAME, const LPVOID &WRITE_LOCATION, const LPCVOID &DATA_TO_WRITE, const size_t &DATA_SIZE);
// Returns true on a successful injection, false otherwise.
bool mInjectDLL(const std::wstring &PROCESS_NAME, const std::string &DLL_LOCATION);

//			-Functions inside the mProcessFunctions namespace-
// Returns a handle to the specified process, NULL otherwise.
HANDLE mGetHandle(const std::wstring &PROCESSNAME, const ProcessAccess DESIREDACCESS);
// Returns the PID of the specified process, NULL otherwise.
DWORD mGetPID(const std::wstring &PROCESSNAME);
// If the handle passed is not valid, the handle is CLOSED and false is returned. Otherwise, the handle is unaffected and true is returned.
bool mValidateHandle(HANDLE &ProcessHandle);

//			-Enums-
// Makes specifying access rights for an operation easier. 
// See https://docs.microsoft.com/en-us/windows/desktop/procthread/process-security-and-access-rights
enum mProcessFunctions::ProcessAccess : DWORD {
	Full = PROCESS_ALL_ACCESS,
	ReadOnly = PROCESS_VM_OPERATION | PROCESS_VM_READ,
	WriteOnly = PROCESS_VM_OPERATION | PROCESS_VM_WRITE,
	ReadWrite = ReadOnly | WriteOnly
};
```
# License  
This library is licensed under version 3 of the General Public License. You are free  
to do whatever you wish the code in this library. No credit due.