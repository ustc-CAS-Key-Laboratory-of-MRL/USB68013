// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>

//Todo: Write Function Header Here
extern "C" __declspec(dllexport) ULONG GetPara(BYTE dev_index, BYTE option);
extern "C" __declspec(dllexport) void flushInputBuffer(BYTE dev_index);
extern "C" __declspec(dllexport) void ResetInputEnpt(BYTE dev_index);
extern "C" __declspec(dllexport) bool read(BYTE dev_index, UCHAR* buf, LONG* num);
extern "C" __declspec(dllexport) bool read_until(BYTE dev_index, UCHAR* buf, LONG* num, LONG timeout);
extern "C" __declspec(dllexport) void write(BYTE dev_index, UCHAR* buf, LONG num);
extern "C" __declspec(dllexport) BOOL open(BYTE index);

// TODO: 在此处引用程序需要的其他头文件
#include "stdio.h"
#include "CyAPI.h"
#include<time.h>