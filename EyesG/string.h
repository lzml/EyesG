#pragma once
#include <string>
#include <vector>
#include <atlstr.h>
/************************************************************************/
/* 
	通用型的字符串处理函数
*/
/************************************************************************/
namespace AdStd
{

	wstring to_wstring(const string &str, UINT codepage = 936);
	wstring to_wstring(CStringW &str);
	wstring to_wstring(const CStringA &str);
	string	to_string(const wstring &wstr, UINT codepage = 936);
	string	to_string(const CStringW &str);
	string	to_string(CStringA &str);



}