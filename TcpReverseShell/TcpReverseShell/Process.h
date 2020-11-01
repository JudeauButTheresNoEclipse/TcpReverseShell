#pragma once

#include <windows.h> 
#include <tchar.h>
#include <stdio.h> 
#include <strsafe.h>

PPROCESS_INFORMATION CreateChildProcess(
	SOCKET ConnectSocket
	);
