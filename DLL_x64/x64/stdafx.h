// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�: 
#include <windows.h>

//Todo: Write Function Header Here

extern "C" __declspec(dllexport) bool read(UCHAR* buf, LONG* num);
extern "C" __declspec(dllexport) void write(UCHAR* buf, LONG num);
extern "C" __declspec(dllexport) bool read_until(UCHAR* buf, LONG* num, LONG timeout);
extern "C" __declspec(dllexport) ULONG GetPara(BYTE option);
extern "C" __declspec(dllexport) void flushInputBuffer();
extern "C" __declspec(dllexport) void ResetInputEnpt();
extern "C" __declspec(dllexport) BOOL open(BYTE index);
// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "stdio.h"
#include "CyAPI.h"
#include<time.h>