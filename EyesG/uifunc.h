#pragma once
#include <string.h>
#include <vector>




//��ȡ��ǰ���̵ĵ�i����������0��������exe�ļ���
string ParamStr(size_t i);
wstring ParamStrW(size_t i);
//��ȡ��ǰ���̵������в����б�����lst[0]��ʾexe�ļ�������������Ϊ��������
void GetCommandLineList(vector<string> &lst);







