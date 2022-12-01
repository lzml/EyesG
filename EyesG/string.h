#pragma once
#include <string>
#include <vector>
#include <atlstr.h>
/************************************************************************/
/* 
	ͨ���͵��ַ���������
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