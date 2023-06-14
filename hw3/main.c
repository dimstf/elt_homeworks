#include <stdio.h>

int main()
{
    // 1 Third byte
	int num = 0xDDCCBBAA;
	int byte = 1;
	unsigned char c=1;
    
	while(byte<=sizeof(int))
	{
		c = ((num >> (8 * (byte - 1)) ) & 0xFF);
		printf("Byte №%d of number 0x%X = %X\n", byte, num, c);
		byte++;
	}
	
	// 2 CC OR 22 = EE
	printf("Change CC on EE:\n");
	printf(" 0x%X | 0x220000 = %X\n", num, num | 0x220000);
	
	return 0;
}