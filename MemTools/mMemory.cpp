#include "mMemory.h"
#include "stdafx.h"
#include <windows.h> 
#include <exception>
#include <cstring>
#include <iostream>
#include <string>

struct mMemoryOperationException : public std::exception {
	const char * what() const throw () {
		DWORD lastError = GetLastError();
		std::string errorCodeStr = std::to_string(lastError);
		std::string errorMessage = "Memory Operation failed with Error Code: " + errorCodeStr;

		return errorMessage.c_str();
	}
};


LPCVOID mReadMemory(HANDLE ProcessHandle, LPCVOID ReadLocation) {
	LPCVOID readValue = NULL;
	bool readSuccess = ReadProcessMemory(ProcessHandle, ReadLocation, &readValue, sizeof(readValue), NULL);

	if (!readSuccess) {
		throw mMemoryOperationException();
	}

	return readValue;
}

void mWriteMemory(HANDLE ProcessHandle, LPVOID WriteLocation, LPCVOID DataToWrite) {
	bool writeSuccess = WriteProcessMemory(ProcessHandle, WriteLocation, DataToWrite, sizeof(DataToWrite), 0);

	if (!writeSuccess) {
		throw mMemoryOperationException();
	}
}
