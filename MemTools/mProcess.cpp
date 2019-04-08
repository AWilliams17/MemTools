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

	uintptr_t mGetModuleAddress(const std::string &PROCESS_NAME, const std::string &MODULE_NAME) {
		HANDLE targetProcessHandle = mGetHandle(PROCESS_NAME, ProcessAccess::QueryInformation);
		HMODULE hMods[1024];
		DWORD cbNeeded;
		uintptr_t targetModuleAddress = NULL;

		if (targetProcessHandle != NULL) {
			if (EnumProcessModules(targetProcessHandle, hMods, sizeof(hMods), &cbNeeded)) {
				for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
					char szModName[MAX_PATH];
					if (GetModuleBaseNameA(targetProcessHandle, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR))) {
						if (strcmp(szModName, MODULE_NAME.c_str()) == 0) {
							targetModuleAddress = (uintptr_t)hMods[i];
							break;
						}
					}
				}
			}
			CloseHandle(targetProcessHandle);
		}

		return targetModuleAddress;
	}

	uintptr_t mGetModuleAddress(const HANDLE &PROCESS_HANDLE, const std::string &MODULE_NAME) {
		HMODULE hMods[1024];
		DWORD cbNeeded;
		uintptr_t targetModuleAddress = NULL;

		if (EnumProcessModules(PROCESS_HANDLE, hMods, sizeof(hMods), &cbNeeded)) {
			for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
				char szModName[MAX_PATH];
				if (GetModuleBaseNameA(PROCESS_HANDLE, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR))) {
					if (strcmp(szModName, MODULE_NAME.c_str()) == 0) {
						targetModuleAddress = (uintptr_t)hMods[i];
						break;
					}
				}
			}
		}

		return targetModuleAddress;
	}

	DWORD mGetExportedFunctionOffset(const HMODULE &MODULE_HANDLE, const std::string TARGET_FUNCTION) {
		DWORD targetOffset = NULL;
		PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)((BYTE *)MODULE_HANDLE);
		PIMAGE_NT_HEADERS pNTHeader = (PIMAGE_NT_HEADERS)((BYTE *)pDosHeader + pDosHeader->e_lfanew);
		PIMAGE_OPTIONAL_HEADER pOptionalHeader = (PIMAGE_OPTIONAL_HEADER)(&pNTHeader->OptionalHeader);
		PIMAGE_EXPORT_DIRECTORY pExportsDirectory = (PIMAGE_EXPORT_DIRECTORY)((BYTE *)MODULE_HANDLE + pOptionalHeader->
			DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

		DWORD* NamesArray = (DWORD*)((BYTE*)MODULE_HANDLE + pExportsDirectory->AddressOfNames);
		DWORD* AddressArray = (DWORD*)((BYTE*)MODULE_HANDLE + pExportsDirectory->AddressOfFunctions);

		for (DWORD i = 0; i < pExportsDirectory->NumberOfNames; i++) {
			char* currName = (char*)MODULE_HANDLE + NamesArray[i];
			if (strcmp(currName, TARGET_FUNCTION.c_str()) == 0) {
				targetOffset = AddressArray[i];
				break;
			}
		}

		return targetOffset;
	}
}