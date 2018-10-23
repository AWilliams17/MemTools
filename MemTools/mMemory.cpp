#include "stdafx.h"
#include <windows.h> 
#include <exception>
#include <string>
#include "mMemory.h"
#include "mProcess.h"

namespace mMemoryFunctions {
	LPCVOID mReadMemory(const std::wstring &PROCESS_NAME, const uintptr_t &READ_LOCATION, const size_t &READ_SIZE) {
		LPCVOID readValue;

		HANDLE processHandle = mProcessFunctions::mGetHandle(PROCESS_NAME, mProcessFunctions::ProcessAccess::ReadOnly);

		if (!mProcessFunctions::mValidateHandle(processHandle)) {
			return NULL;
		}

		if (!ReadProcessMemory(processHandle, (LPCVOID)READ_LOCATION, &readValue, READ_SIZE, NULL)) {
			return NULL;
		}

		CloseHandle(processHandle);
		return readValue;
	}

	bool mWriteMemory(const std::wstring &PROCESS_NAME, const uintptr_t &WRITE_LOCATION, const LPCVOID &DATA_TO_WRITE, const size_t &DATA_SIZE) {
		HANDLE processHandle = mProcessFunctions::mGetHandle(PROCESS_NAME, mProcessFunctions::ProcessAccess::ReadWrite);

		if (!mProcessFunctions::mValidateHandle(processHandle)) {
			return false;
		}

		bool writeSuccessful = WriteProcessMemory(processHandle, (LPVOID)WRITE_LOCATION, DATA_TO_WRITE, DATA_SIZE, 0);
		CloseHandle(processHandle);
	}

	bool mInjectDLL(const std::wstring &PROCESS_NAME, const std::string &DLL_LOCATION) {
		size_t dllLen = DLL_LOCATION.length();
		int procID = mProcessFunctions::mGetPID(PROCESS_NAME);

		HANDLE injecteeHandle = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION
											| PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, procID);

		if (!mProcessFunctions::mValidateHandle(injecteeHandle)) {
			return false;
		}

		LPVOID loadLibrary = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
		LPVOID locationToWrite = (LPVOID)VirtualAllocEx(injecteeHandle, NULL, dllLen, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

		if (locationToWrite == NULL) {
			return false;
		}

		if (!WriteProcessMemory(injecteeHandle, locationToWrite, DLL_LOCATION.c_str(), dllLen, 0)) {
			return false;
		}

		HANDLE remoteThread = CreateRemoteThread(injecteeHandle, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibrary, locationToWrite, 0, NULL);

		if (!mProcessFunctions::mValidateHandle(remoteThread)) {
			return false;
		}

		CloseHandle(injecteeHandle);
		CloseHandle(remoteThread);
		return true;
	}
}
