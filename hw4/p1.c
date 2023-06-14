#include <stdio.h>

int main()
{
	int n, i, j, counter=1;
	
	printf("Input n:\n");
	scanf("%d",&n);
	
	if(n<=0)
		return 0;

	int arr[n][n];
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			arr[i][j]=counter++;
	
	printf("Array:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			printf("%d ",arr[i][j]);
		printf("\n");
	}

	return 0;
}