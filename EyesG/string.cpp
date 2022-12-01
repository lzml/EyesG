#include "stdafx.h"
#include "string.h"
#include <algorithm>
#include <functional>

namespace AdStd
{
	wstring to_wstring(const string &str, UINT codepage )
	{
		if (str.empty())
			return L"";
		int iULen = MultiByteToWideChar(codepage, 0, str.c_str(), -1, NULL, 0);
		wchar_t *ustr = (wchar_t*)malloc((iULen)*sizeof(wchar_t));
		if (!ustr)
			return L"";
		memset(ustr, 0, (iULen)*sizeof(wchar_t));
		MultiByteToWideChar(codepage, 0, str.c_str(), -1, ustr, iULen);
		wstring ret;
		ret.assign(ustr);
		free(ustr);
		return ret;
	}

	wstring to_wstring(CStringW &str)
	{
		wstring s = str.GetBuffer();
		str.ReleaseBuffer();
		return s;
	}

	wstring to_wstring(const CStringA &str)
	{
		 return to_wstring((CStringW)CA2W(str,CP_ACP));
	}
	string	to_string(const wstring &wstr, UINT codepage)
	{
		if (wstr.empty())
			return "";
		int iALen = WideCharToMultiByte(codepage, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
		char *astr = (char*)malloc(iALen);
		if (!astr)
			return "";
		memset(astr, 0, iALen);
		WideCharToMultiByte(codepage, 0, wstr.c_str(), -1, astr, iALen, NULL, NULL);
		string ret;
		ret.assign(astr);
		free(astr);
		return ret;
	}
	string	to_string(const CStringW &str)
	{
		return to_string((CStringA)CW2A(str, CP_ACP));
	}
	string	to_string(CStringA &str)
	{
		string s = str.GetBuffer();
		str.ReleaseBuffer();
		return s;
	}

	CStringW to_CStringW(std::string &str)
	{
		CString strW = CA2W(str.c_str(), CP_ACP);
		return strW;
	}

	CStringW to_CStringW(std::wstring &str)
	{
		CString strW = str.c_str();
		return strW;
	}

	CStringA to_CStringA(std::wstring &str)
	{
		CStringA strA = CW2A(str.c_str(), CP_ACP);
		return strA;
	}

	CStringA to_CStringA(std::string &str)
	{
		CStringA strA = str.c_str();
		return strA;
	}

	
}