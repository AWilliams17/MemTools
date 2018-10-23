#include <string>
#include "stdafx.h"
#include <Tlhelp32.h>
#include <psapi.h>
#include "mProcess.h"

namespace mProcessFunctions {
	HANDLE mGetHandle(const std::string &PROCESSNAME, const ProcessAccess DESIREDACCESS) {
		DWORD pID = mGetPID(PROCESSNAME);
		HANDLE processHandle = OpenProcess(DESIREDACCESS, FALSE, pID);

		if (!mValidateHandle(processHandle)) {
			return NULL;
		}

		return processHandle;
	}

	DWORD mGetPID(const std::string &PROCESSNAME) {
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);
		HANDLE tool32SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (!mValidateHandle(tool32SnapShot)) {
			return NULL;
		}

		if (Process32First(tool32SnapShot, &procEntry)) {
			while (Process32Next(tool32SnapShot, &procEntry)) {
				if (strcmp(PROCESSNAME.c_str(), procEntry.szExeFile) == 0) {
					return procEntry.th32ProcessID;
				}
			}
		}

		return NULL;
	}

	bool mValidateHandle(HANDLE &ProcessHandle) {
		if (ProcessHandle == NULL || ProcessHandle == INVALID_HANDLE_VALUE) {
			CloseHandle(ProcessHandle);
			return false;
		}

		return true;
	}

	DWORD mGetModuleAddress(const std::string &PROCESS_NAME, const std::string &MODULE_NAME) {
		HANDLE targetProcessHandle = mGetHandle(PROCESS_NAME, ProcessAccess::QueryInformation);
		HMODULE hMods[1024];
		DWORD cbNeeded;
		DWORD targetModuleAddress = NULL;

		if (targetProcessHandle != NULL) {
			if (EnumProcessModules(targetProcessHandle, hMods, sizeof(hMods), &cbNeeded)) {
				for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
					char szModName[MAX_PATH];
					if (GetModuleBaseNameA(targetProcessHandle, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR))) {
						if (strcmp(szModName, MODULE_NAME.c_str()) == 0) {
							targetModuleAddress = (DWORD)hMods[i];
							break;
						}
					}
				}
			}
			CloseHandle(targetProcessHandle);
		}

		return targetModuleAddress;
	}
}