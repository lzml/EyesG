#pragma once
#include <string.h>
#include <vector>




//获取当前进程的第i个参数，第0个参数是exe文件名
string ParamStr(size_t i);
wstring ParamStrW(size_t i);
//获取当前进程的命令行参数列表，其中lst[0]表示exe文件名，后续依次为各个参数
void GetCommandLineList(vector<string> &lst);







