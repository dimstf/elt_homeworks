#include <stdio.h>

void arr_reverse(int m[],int size)
{
	if(size>1)
	{
		int k=0;
		int tmp=0;
		for(k=0;k<size/2;k++)
		{
			tmp=m[k];
			m[k]=m[size-1-k];
			m[size-1-k]=tmp;
		}
	} else {
		printf("Size == 1. Nothing changed.\n");
	}
}

int main()
{
	int n, i, counter=1;
	
	printf("Input n:\n");
	scanf("%d",&n);
	
	if(n<=0)
		return 0;

	int arr[n];
	
	printf("Array before reversing:\n");
	for(i=0;i<n;i++)
	{
		arr[i]=counter++;
		printf("%d ",arr[i]);
	}
	printf("\n");
	
	printf("Array after reversing:\n");
	arr_reverse(arr, n);
	for(i=0;i<n;i++)
		printf("%d ",arr[i]);
	printf("\n");
	
	return 0;
}