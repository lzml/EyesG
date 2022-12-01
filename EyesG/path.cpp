#include "stdafx.h"
#include "path.h"
#include <ShlObj.h>
#include "string.h"

#pragma comment(lib,"shlwapi.lib")


wstring GetCurrentDir()
{
	TCHAR szCurrentPath[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, szCurrentPath, MAX_PATH);
	PathRemoveFileSpec(szCurrentPath);
	return szCurrentPath;
}



