// dllmain.cpp : 定义 DLL 应用程序的入口点。

#include "stdafx.h"


CCyUSBDevice *USBDevice[16] = {NULL};
ULONG BulkInSize = 4096;
ULONG BulkOutSize = 4096;
#define TimeoutConst 1000

ULONG GetPara(BYTE dev_index, BYTE option){
	if (option == 0) return USBDevice[dev_index]->BulkInEndPt->GetXferSize( );
	else if (option == 1) return USBDevice[dev_index]->BulkInEndPt->GetXferSize( );
	else if (option == 2) return USBDevice[dev_index]->BulkInEndPt->TimeOut;
	else if (option == 3) return USBDevice[dev_index]->BulkOutEndPt->TimeOut;
	else if (option == 4) return USBDevice[dev_index]->DeviceCount();
	else return 10;
}

void flushInputBuffer(BYTE dev_index){
	/*UCHAR *buffer = new UCHAR[BulkInSize];
	LONG readnum = BulkInSize;
	if (USBDevice[dev_index]->BulkInEndPt){
		while (USBDevice[dev_index]->BulkInEndPt->XferData(buffer, readnum));
	}
	USBDevice[dev_index]->BulkInEndPt->Reset();*/
	USBDevice[dev_index] ->Reset();
	//while (! USBDevice[dev_index] ->Resume());
}
void ResetInputEnpt(BYTE dev_index){
	USBDevice[dev_index]->BulkInEndPt->Reset();
}
bool read(BYTE dev_index, UCHAR* buf, LONG* num){
	//UCHAR *buffer = new UCHAR[BulkInSize];
	LONG readnum = BulkInSize;
	bool temp;
	if (USBDevice[dev_index]->BulkInEndPt){
		temp = USBDevice[dev_index]->BulkInEndPt->XferData(buf, readnum);
		//strcpy_s((char *)buf, readnum, (const char *)buffer);
		//for (int i=0;i<readnum;i++) buf[i]=buffer[i];
		*num = readnum;
		return temp;
	}
	return false;
}


bool read_until(BYTE dev_index, UCHAR* buf, LONG* num, LONG timeout){
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
		if (read(dev_index, buf+rxnum, &temp)){
		//if (read(buffer, &temp)){
		//	//printf("Read succeed.");
		//	for (int i=0; i<temp; i++)
		//		buf[rxnum+i]=buffer[i];
			rxnum += temp;
		}

		//else
		//{
			//USBDevice[dev_index] ->BulkInEndPt->Reset();
			//USBDevice[dev_index] ->BulkInEndPt->Abort();
		//}
	}
	return true;
}


void write(BYTE dev_index, UCHAR* buf, LONG num){
	if (USBDevice[dev_index]->BulkOutEndPt)
		if (num>4096){
			//UCHAR *buffer = new UCHAR[BulkOutSize];
			LONG remain = num;
			LONG temp = 0;
			LONG ptr = 0;
			while (remain > 4096)
			{
				temp = 4096;
				USBDevice[dev_index]->BulkOutEndPt->XferData(buf+ptr, temp);
				remain -= 4096;
				ptr += 4096;
			}
			if (remain > 0) USBDevice[dev_index]->BulkOutEndPt->XferData(buf+ptr, remain);
		}
		else	USBDevice[dev_index]->BulkOutEndPt->XferData(buf, num);
}

BOOL open(BYTE index){
	BYTE nUSB=USBDevice[0]->DeviceCount();
	if (index >= nUSB) return false;
	USBDevice[index]->Close();
	return USBDevice[index]->Open(index);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		USBDevice[0] = new CCyUSBDevice(NULL);
		printf ("Number of Device:%d\n",USBDevice[0]->DeviceCount());
			if (USBDevice[0]->DeviceCount())
			{
				

				// search for all connected devices, and add them to the device
				USBDevice[0]->Open(0);
				//printf ("%X, %X", USBDevice->ProductID, USBDevice->VendorID);

				USBDevice[0]->BulkInEndPt->TimeOut = TimeoutConst;
				USBDevice[0]->BulkInEndPt->SetXferSize(BulkInSize);
				
				USBDevice[0]->BulkOutEndPt->TimeOut = TimeoutConst;
				USBDevice[0]->BulkOutEndPt->SetXferSize(BulkOutSize);
				for (int i = 1; i < USBDevice[0]->DeviceCount(); i++)
				{
					USBDevice[i] = new CCyUSBDevice(NULL);
					USBDevice[i]->Open(i);
					USBDevice[i]->BulkInEndPt->TimeOut = TimeoutConst;
					USBDevice[i]->BulkInEndPt->SetXferSize(BulkInSize);

					USBDevice[i]->BulkOutEndPt->TimeOut = TimeoutConst;
					USBDevice[i]->BulkOutEndPt->SetXferSize(BulkOutSize);
				}
			}
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		for (int i = 0; i < USBDevice[0]->DeviceCount(); i++)
		{
			USBDevice[i]->Close();
		}
		break;
	}
	return TRUE;
}

