# MemTools - A Memory Hacking Library written in C  
This is an effort to write an easy to use library for performing  
common memory-related operations when writing game hacks.  
All of the functions are made to be stateless and functional.  
  
# The Functions
```c 
// Note: Use GetLastError() for more information on failures.

// Checks if the specified process is running. Returns true if it is, false otherwise.
mIsProcessRunning(char* ProcessName)
// Returns the handle to a process, or NULL if it failed.  
mOpenHandle(const char* ProcessName, const ProcessAccess DesiredAccess)
// Writes data to the target location in the process' memory. Returns NonZero if it is a success, 0 otherwise.
mWriteMemory(handle ProcessHandle, LPVOID WriteLocation, LPCVOID Data)
// Reads data from the specified address in the process' memory. Returns the read value on success, NULL otherwise.
mReadMemory(handle ProcessHandle, LPCVOID ReadLocation)
// Gets the PID of the specified process. Returns the PID on success, or NULL if it failed.
mGetPID(const char* ProcessName)
// Checks if the specified handle is still valid. Returns true if it is, false otherwise.
mIsHandleValid(handle ProcessHandle)
```  
  
# Usage  
To be written...  
  
# License  
This library is licensed under version 3 of the General Public License. You are free  
to do whatever you wish the code in this library. No credit due.