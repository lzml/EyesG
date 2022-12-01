#include "stdafx.h"
#include "uifunc.h"

#include "path.h"
#include "string.h"
using namespace AdStd;
#include <UserEnv.h>
#pragma comment(lib, "UserEnv.lib")
#pragma comment(lib, "version.lib")
#include "process.h"
#include <TlHelp32.h>
#include <process.h>
#include "string.h"
#include <Psapi.h>
#include <WtsApi32.h>
#pragma comment(lib, "WtsApi32.lib")
#include <Shlwapi.h>
#include <atlpath.h>
#include <shobjidl.h>
#include <Shldisp.h>
#include <ShlObj.h>


string ParamStr(size_t i)
{
	vector<string> lstCmdline;
	GetCommandLineList(lstCmdline);
	if (i >= lstCmdline.size() || i < 0)
		return "";
	else
		return lstCmdline[i];

	return "";
}

wstring ParamStrW(size_t i)
{
	return to_wstring(ParamStr(i));
}


void GetCommandLineList(vector<string>& lst)
{
	LPCSTR cstr = GetCommandLineA();
	string s(cstr);
	bool bSub = false;
	string sSub = "";
	lst.clear();
	for (int i = 0; i != s.length(); ++i)
	{
		if ('\"' == s[i])
		{
			if (!bSub)
			{
				bSub = true;
				if (sSub != "")
				{
					lst.push_back(sSub);
					sSub = "";
				}
				continue;
			}
			else
			{
				bSub = false;
				lst.push_back(sSub);
				sSub = "";
			}
		}
		else if (' ' == s[i])
		{
			if (bSub)
			{
				sSub += s[i];
				continue;
			}
			else //not bsub
			{
				if (sSub != "")
				{
					lst.push_back(sSub);
					sSub = "";
				}
				else
					continue;
			}
		}
		else
			sSub += s[i];
	}
	if (sSub != "")
		lst.push_back(sSub);
}


