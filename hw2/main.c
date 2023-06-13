#include<stdio.h>
 
int main() 
{
    volatile int num=7;
 
    switch (num) {
    case 1:
        printf("case 1\n");
		break;
    case 2:
        printf("case 2\n");
		break;
    case 3:
        printf("case 3\n");
		break;
    case 7:
        printf("case 7\n");
		break;
    case 100:
        printf("case 100\n");
		break;
    case 1131:
        printf("case 1131\n");
		break;
    default:
        printf("default case\n");
		break;
    }
	printf("num = %d\n", num);

    return 0;
}