#include<stdio.h>
int main()
{
    int A[20],B[30],C[50],i,j,k,n,m,flag=0;
    printf("Enter the number of elements in first array");
    scanf("%d",&n);
    printf("Enter the elements in the array");
    for(i=0;i<n;i++)
    {
        scanf("%d",&A[i]);
    }
    printf("Enter the number of elements in second array");
    scanf("%d",&m);
    printf("Enter the elements in second");
    for(j=0;j<m;j++)
    {
        scanf("%d",&B[j]);
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            if(A[i]!=B[j])
            {
                flag=1;
                //printf("%d and%d are duplicate",A[i])
            }
	    else
	    	printf("%d and%d are duplicate",A[i],B[j]);
        }
    }
    //if(flag==0)
    //{
    //    ;
    //}
	int c[10];
    for(i=0;i<n;i++){
	//if(i<n)
		c[i]=A[i];
    }
    k=0;
    for(j=n;j<(m+n);j++){
		//int k=0;
		c[j]=B[k];
		k++;
    }
    for(i=0;i<(m+n);i++){
	printf("%d ",c[i]);
    }
    

}
