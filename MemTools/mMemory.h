#pragma once

LPCVOID mReadMemory(HANDLE ProcessHandle, LPCVOID ReadLocation);
void mWriteMemory(HANDLE ProcessHandle, LPVOID WriteLocation, LPCVOID DataToWrite);
