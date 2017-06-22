// dllmain.cpp : 定义 DLL 应用程序的入口点。

#include "stdafx.h"


CCyUSBDevice *USBDevice = new CCyUSBDevice(NULL);
ULONG BulkInSize = 4096;
ULONG BulkOutSize = 4096;
#define TimeoutConst 1000

ULONG GetPara(BYTE option){
	if (option == 0) return USBDevice->BulkInEndPt->GetXferSize( );
	else if (option == 1) return USBDevice->BulkInEndPt->GetXferSize( );
	else if (option == 2) return USBDevice->BulkInEndPt->TimeOut;
	else if (option == 3) return USBDevice->BulkOutEndPt->TimeOut;
	else if (option == 4) return USBDevice->DeviceCount();
	else return 10;
}

void flushInputBuffer(){
	/*UCHAR *buffer = new UCHAR[BulkInSize];
	LONG readnum = BulkInSize;
	if (USBDevice->BulkInEndPt){
		while (USBDevice->BulkInEndPt->XferData(buffer, readnum));
	}
	USBDevice->BulkInEndPt->Reset();*/
	USBDevice ->Reset();
	//while (! USBDevice ->Resume());
}
void ResetInputEnpt(){
	USBDevice->BulkInEndPt->Reset();
}
bool read(UCHAR* buf, LONG* num){
	//UCHAR *buffer = new UCHAR[BulkInSize];
	LONG readnum = BulkInSize;
	bool temp;
	if (USBDevice->BulkInEndPt){
		temp = USBDevice->BulkInEndPt->XferData(buf, readnum);
		//strcpy_s((char *)buf, readnum, (const char *)buffer);
		//for (int i=0;i<readnum;i++) buf[i]=buffer[i];
		*num = readnum;
		return temp;
	}
	return false;
}


bool read_until(UCHAR* buf, LONG* num, LONG timeout){
	long beginTime = clock();
	long rxnum = 0;
	long temp=0;
	UCHAR *buffer= new UCHAR[*num];
	while (rxnum < *num)
	{
		if (clock()-beginTime > timeout) {
			*num = rxnum;
			return false;
		}
		temp = *num-rxnum;
		if (temp > BulkInSize) temp =BulkInSize;
		if (read(buf+rxnum, &temp)){
		//if (read(buffer, &temp)){
		//	//printf("Read succeed.");
		//	for (int i=0; i<temp; i++)
		//		buf[rxnum+i]=buffer[i];
			rxnum += temp;
		}

		//else
		//{
			//USBDevice ->BulkInEndPt->Reset();
			//USBDevice ->BulkInEndPt->Abort();
		//}
	}
	return true;
}


void write(UCHAR* buf, LONG num){
	if (USBDevice->BulkOutEndPt)
		if (num>4096){
			//UCHAR *buffer = new UCHAR[BulkOutSize];
			LONG remain = num;
			LONG temp = 0;
			LONG ptr = 0;
			while (remain > 4096)
			{
				temp = 4096;
				USBDevice->BulkOutEndPt->XferData(buf+ptr, temp);
				remain -= 4096;
				ptr += 4096;
			}
			if (remain > 0) USBDevice->BulkOutEndPt->XferData(buf+ptr, remain);
		}
		else	USBDevice->BulkOutEndPt->XferData(buf, num);
}

BOOL open(BYTE index){
	BYTE nUSB=USBDevice->DeviceCount();
	if (index >= nUSB) return false;
	USBDevice->Close();
	return USBDevice->Open(index);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		printf ("Number of Device:%d",USBDevice->DeviceCount());
			if (USBDevice->DeviceCount())
			{
				// search for all connected devices, and add them to the device
				USBDevice->Open(0);
				//printf ("%X, %X", USBDevice->ProductID, USBDevice->VendorID);

				USBDevice->BulkInEndPt->TimeOut = TimeoutConst;
				USBDevice->BulkInEndPt->SetXferSize(BulkInSize);
				
				USBDevice->BulkOutEndPt->TimeOut = TimeoutConst;
				USBDevice->BulkOutEndPt->SetXferSize(BulkOutSize);
				/*for (int i = 0; i < USBDevice->DeviceCount(); i++)
				{
					USBDevice->Open(i);
				}*/
				}
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		USBDevice->Close();
		break;
	}
	return TRUE;
}

