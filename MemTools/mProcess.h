#pragma once

enum ProcessAccess : DWORD {
	Full = PROCESS_ALL_ACCESS,
	ReadOnly = PROCESS_VM_OPERATION | PROCESS_VM_READ,
	WriteOnly = PROCESS_VM_OPERATION | PROCESS_VM_WRITE,
	ReadWrite = ReadOnly | WriteOnly
};