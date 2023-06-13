#include <stdio.h>

int main()
{
    // 1 Third byte
	int num = 0xDDCCBBAA;
	int byte = 3;
	unsigned char c = ((num >> (8 * (byte - 1)) ) & 0xFF);
    printf("Byte №%d of number 0x%X = %X\n", byte, num, c);
	
	// 2 CC OR 22 = EE
	printf("result = %X\n",num | 0x220000);
	
	return 0;
}