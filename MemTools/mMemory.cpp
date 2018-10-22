#include "stdafx.h"
#include <windows.h> 
#include <exception>
#include <string>
#include "mMemory.h"

namespace mMemoryFunctions {
	struct mMemoryOperationException : public std::exception {
		const char * what() const throw () {
			DWORD lastError = GetLastError();
			std::string errorCodeStr = std::to_string(lastError);
			std::string errorMessage = "Memory Operation failed with Error Code: " + errorCodeStr;

			return errorMessage.c_str();
		}
	};


	LPCVOID mReadMemory(const HANDLE &PROCESS_HANDLE, const LPCVOID &READ_LOCATION) {
		LPCVOID readValue = NULL;
		bool readSuccess = ReadProcessMemory(PROCESS_HANDLE, READ_LOCATION, &readValue, sizeof(readValue), NULL);

		if (!readSuccess) {
			throw mMemoryOperationException();
		}

		return readValue;
	}

	void mWriteMemory(const HANDLE &PROCESS_HANDLE, const LPVOID &WRITE_LOCATION, const LPCVOID &DATA_TO_WRITE) {
		bool writeSuccess = WriteProcessMemory(PROCESS_HANDLE, WRITE_LOCATION, DATA_TO_WRITE, sizeof(DATA_TO_WRITE), 0);

		if (!writeSuccess) {
			throw mMemoryOperationException();
		}
	}

	void mInjectDLL(const int &PROCESS_ID, const std::string &DLL_LOCATION) {
		size_t dllLen = strlen(DLL_LOCATION.c_str());

		HANDLE injecteeHandle = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION
											| PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, PROCESS_ID);
		LPVOID loadLibrary = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
		LPVOID locationToWrite = (LPVOID)VirtualAllocEx(injecteeHandle, NULL, dllLen, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

		if (injecteeHandle == INVALID_HANDLE_VALUE) {
			CloseHandle(injecteeHandle);
			return throw mMemoryOperationException();
		}

		mWriteMemory(injecteeHandle, locationToWrite, DLL_LOCATION.c_str());

		HANDLE remoteThread = CreateRemoteThread(injecteeHandle, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibrary, locationToWrite, 0, NULL);
	}
}
