#include <stdio.h>
 
int main()
{
    int k=1, i=0, j=0, n=1;
    printf("Input n:\n");
    scanf("%d",&n);
	
	if(n<1)
		return 0;
    int a[n][n];

    while(k<=n*n)
	{
        a[i][j]=k;
        if((i<=j+1)&&(i+j<n-1))
            j++;
        else if((i<j)&&(i+j>=n-1))
            i++;
        else if((i>=j)&&(i+j>n-1))
            j--;
        else 
            i--;
        k++;
    }
    
    for(i=0;i<n;++i){
        for(j=0;j<n;++j)
            printf("%d ",a[i][j]);
        printf("\n");
    }
	
	return 0;
}