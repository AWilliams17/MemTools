#pragma once

LPCVOID mReadMemory(const HANDLE PROCESS_HANDLE, const LPCVOID READ_LOCATION);
void mWriteMemory(const HANDLE PROCESS_HANDLE, const LPVOID WRITE_LOCATION, const LPCVOID DATA_TO_WRITE);
void mInjectDLL(const HANDLE PROCESS_HANDLE, const std::string DLL_LOCATION);
