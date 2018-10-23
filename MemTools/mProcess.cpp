#include <string>
#include "stdafx.h"
#include <Tlhelp32.h>
#include "mProcess.h"

namespace mProcessFunctions {
	HANDLE mGetHandle(const std::wstring &PROCESSNAME, const ProcessAccess DESIREDACCESS) {
		DWORD pID = mGetPID(PROCESSNAME);
		HANDLE processHandle = OpenProcess(DESIREDACCESS, FALSE, pID);

		if (!mValidateHandle(processHandle)) {
			return NULL;
		}

		return processHandle;
	}

	DWORD mGetPID(const std::wstring &PROCESSNAME) {
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);
		HANDLE tool32SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (!mValidateHandle(tool32SnapShot)) {
			return NULL;
		}

		if (Process32First(tool32SnapShot, &procEntry)) {
			while (Process32Next(tool32SnapShot, &procEntry)) {
				if (lstrcmpi(PROCESSNAME.c_str(), procEntry.szExeFile) == 0) {
					return procEntry.th32ProcessID;
				}
			}
		}

		return NULL;
	}

	bool mValidateHandle(HANDLE &ProcessHandle) {
		if (ProcessHandle != NULL && ProcessHandle != INVALID_HANDLE_VALUE) {
			CloseHandle(ProcessHandle);
			return false;
		}

		return true;
	}
}