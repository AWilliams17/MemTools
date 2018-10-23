# MemTools - A Memory Hacking Library written in C++  
This is an effort to write an easy to use library for performing common memory-related operations when writing game hacks.

# The Library
```c 
// -Functions List-
// Note: Use GetLastError() for more information on failures.
// Note: All functions relating to handles other than mIsHandleValid and mGetHandle close their handles after usage.

// 			-Functions inside the mMemoryFunctions namespace-
// Returns the value read on success, NULL otherwise.
LPCVOID mReadMemory(const std::string &PROCESS_NAME, const uintptr_t &READ_LOCATION, const size_t &READ_SIZE);
// Returns true on a successful write, false otherwise.
bool mWriteMemory(const std::string &PROCESS_NAME, const uintptr_t &WRITE_LOCATION, const LPCVOID &DATA_TO_WRITE, const size_t &DATA_SIZE);
// Returns true on a successful injection, false otherwise.
bool mInjectDLL(const std::string &PROCESS_NAME, const std::string &DLL_LOCATION);

//			-Functions inside the mProcessFunctions namespace-
// Returns a handle to the specified process, NULL otherwise.
HANDLE mGetHandle(const std::string &PROCESSNAME, const ProcessAccess DESIREDACCESS);
// Returns the PID of the specified process, NULL otherwise.
DWORD mGetPID(const std::string &PROCESSNAME);
// If the handle passed is not valid, the handle is CLOSED and false is returned. Otherwise, the handle is unaffected and true is returned.
bool mValidateHandle(HANDLE &ProcessHandle);
// Attempts to get the address of a loaded module in a process. Returns the address on success, NULL otherwise.
DWORD mGetModuleAddress(const std::string &PROCESS_NAME, const std::string &MODULE_NAME);

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

# Example Usage: Changing Player Health in CSGO
```c
// Disclaimer for people who don't know what they're doing: Don't do this in a VAC server.
// You will not be pleased with the aftermath.
// Also the offset used here is not a static offset.

DWORD csgoPID = mProcessFunctions::mGetPID("csgo.exe");
DWORD csgoPanoramaClientDLL = mProcessFunctions::mGetModuleAddress("csgo.exe", "client_panorama.dll");

uintptr_t healthAddress = 0x1E29B8FC;
LPCVOID previousHealthValue = mMemoryFunctions::mReadMemory("csgo.exe", healthAddress, sizeof(healthAddress));
int newHealth = 12345;
mMemoryFunctions::mWriteMemory("csgo.exe", healthAddress, &newHealth, sizeof(newHealth));
LPCVOID newHealthValue = mMemoryFunctions::mReadMemory("csgo.exe", healthAddress, sizeof(healthAddress));

printf("csgo.exe PID: %d\n", csgoPID);
printf("Health Value before write: %d\n", previousHealthValue); // 100
printf("Health Value after write: %d\n", newHealthValue); // 12345
printf("client_panorama.dll address: %d\n", csgoPanoramaClientDLL);
```

# License  
This library is licensed under version 3 of the General Public License. You are free to do whatever you wish the code in this library. No credit due.