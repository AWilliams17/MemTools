#include <string>
#include "stdafx.h"
#include "mProcess.h"


__declspec(dllexport) bool mIsProcessRunning(const std::string PROCESSNAME) {

}

__declspec(dllexport) HANDLE mGetHandle(const std::string PROCESSNAME, const ProcessAccess DESIREDACCESS) {

}

__declspec(dllexport) int mGetPID(const std::string PROCESSNAME) {

}

__declspec(dllexport) bool mIsHandleValid(const HANDLE *PROCESSHANDLE) {

}
