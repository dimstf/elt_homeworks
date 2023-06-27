#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Begin\n");
	int *arr;
	// double malloc
	arr=(int*)malloc(5*sizeof(int));
	arr=(int*)malloc(10*sizeof(int));
	
	// after last element
	arr[11]=12;
	
	// double free
	free(arr);
	free(arr);
	printf("End.");
	return 0;
}
