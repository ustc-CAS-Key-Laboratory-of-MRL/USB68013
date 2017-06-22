#include <malloc.h>
void num_to_bytes(int num, short bytenum, unsigned char* bytes, bool high_head = true)
{
	//unsigned char *bytes;
	//bytes = (unsigned char *)malloc(sizeof(unsigned char)*bytenum);
	if (high_head == true)
	{
		for (int i=0;i<bytenum;i++) bytes[i] = (num >> ((bytenum-i-1)*8)) & 0xFF;
		//bytes[0] = (n >> 24) & 0xFF;
		//bytes[1] = (n >> 16) & 0xFF;
		//bytes[2] = (n >> 8) & 0xFF;
		//bytes[3] = n & 0xFF;
	}
	else
	{
		for (int i = 0; i<bytenum; i++) bytes[i] = (num >> (i * 8)) & 0xFF;
		//bytes[3] = (num >> 24) & 0xFF;
		//bytes[2] = (num >> 16) & 0xFF;
		//bytes[1] = (num >> 8) & 0xFF;
		//bytes[0] = num & 0xFF;
	}
}