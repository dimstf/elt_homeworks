#include <stdio.h>

int insert_elem(int a, int b, int s)
{
	if((a!=s-1)&&(b<s-a-1))
		return 0;
	
	return 1;
}

void change_matrix(int size, int mas[size][size])
{
	if(size>1)
	{
		int k, l;
		for(k=0;k<size;k++)
		{
			for(l=0;l<size;l++)
			{
				mas[k][l]=insert_elem(k,l,size);
			}
		}
	} else {
		mas[0][0]=1;
	}
}

int main()
{
	int n, i, j;
	
	printf("Input n:\n");
	scanf("%d",&n);
	
	if(n<=0)
		return 0;

	int arr[n][n];
	
	printf("Array before change:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			arr[i][j]=n;
			printf("%d ",arr[i][j]);
		}
		printf("\n");
	}
	
	printf("Array after change:\n");
	change_matrix(n,arr);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",arr[i][j]);
		}
		printf("\n");
	}

	return 0;
}