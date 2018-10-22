#include "mMemory.h"
#include "stdafx.h"
#include <windows.h> 
#include <exception>
#include <string>

struct mMemoryOperationException : public std::exception {
	const char * what() const throw () {
		DWORD lastError = GetLastError();
		std::string errorCodeStr = std::to_string(lastError);
		std::string errorMessage = "Memory Operation failed with Error Code: " + errorCodeStr;

		return errorMessage.c_str();
	}
};


LPCVOID mReadMemory(const HANDLE PROCESS_HANDLE, const LPCVOID READ_LOCATION) {
	LPCVOID readValue = NULL;
	bool readSuccess = ReadProcessMemory(PROCESS_HANDLE, READ_LOCATION, &readValue, sizeof(readValue), NULL);

	if (!readSuccess) {
		throw mMemoryOperationException();
	}

	return readValue;
}

void mWriteMemory(const HANDLE PROCESS_HANDLE, const LPVOID WRITE_LOCATION, const LPCVOID DATA_TO_WRITE) {
	bool writeSuccess = WriteProcessMemory(PROCESS_HANDLE, WRITE_LOCATION, DATA_TO_WRITE, sizeof(DATA_TO_WRITE), 0);

	if (!writeSuccess) {
		throw mMemoryOperationException();
	}
}

void mInjectDLL(const HANDLE PROCESS_HANDLE, const std::string *DLL_LOCATION) {

}
