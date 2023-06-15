#include <stdio.h>

int main()
{
	int a=270533154;
	char *ptr=&a;
	int byte=1;

	// 1 Print bytes of number
	while(byte<=sizeof(a))
	{
		printf("Byte №%d of number %d = %d\n", byte, a, *ptr);
		ptr++;
		byte++;
	}
	printf("\n");
	
	// 2 Change third byte of number a (2 -> 77)
	ptr=&a;
	byte=3;
	int t=sizeof(a)-byte;
	while(t>0)
	{
		ptr++;
		t--;
	}
	byte=1;
	*ptr=77;
	ptr=&a;
	while(byte<=sizeof(a))
	{
		printf("Byte №%d of number %d = %d\n", byte, a, *ptr);
		ptr++;
		byte++;
	}
	
	return 0;
}