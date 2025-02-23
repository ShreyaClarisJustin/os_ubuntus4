#include<stdio.h>
int main()
{
	int m,n,i,j,k,y,alloc[20][20],max[20][20],avail[50],x=0;
	printf("\n Enter the number of processes");
	scanf("%d",&m);
	printf("\n Enter the number of resources");
	scanf("%d",&n);
	printf("\n Enter the allocation matrix");
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&alloc[i][j]);
		}
	}
	printf("\n Enter the max matrix");
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&max[i][j]);
		}
	}
	printf("\n Enter the available matrix");
	for(i=0;i<n;i++)
		scanf("%d",&avail[i]);
	int finish[m],safesequence[m],work[n],need[m][n];
	for(i=0;i<n;i++)
	{
		work[i]=avail[i];
	}
	//calculating need matrix
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			need[i][j]=max[i][j]-alloc[i][j];
		}
	}
	printf("\n Need matrix is:");
	for(i=0;i<m;i++)
	{
		printf("\n");
		for(j=0;j<n;j++)
		{
			printf(" %d\t",need[i][j]);
		}
	}
	for(i=0;i<n;i++)
	{
		work[i]=avail[i];
	}
	for(i=0;i<m;i++)
	{
		finish[i]=0;
	}
	for(k=0;k<m;k++)
	{
		for(i=0;i<m;i++)
		{
			if(finish[i]==0)
			{
				int flag=0;
				for(j=0;j<n;j++)
				{
					if(need[i][j]>work[j])
					{
						flag=1;
						break;
					}
				}
				if(flag==0)
				{
					safesequence[x++]=i;
					for(y=0;y<n;y++)
					{
						work[y]+=alloc[i][y];
					}
					finish[i]=1;
				}
			}
		}
	}
	int c=1;
	for(int i=0;i<m;i++)
	{
		if(finish[i]==0)
		{
			c=0;
			printf("the system is not in safe state");
			break;
		}
	}
	if(c==1)

	{	printf("\nthe system is safe and Following is the safe sequence\n");
		for(i=0;i<=m-1;i++)
		{	printf("P%d  ",safesequence[i]);
		}
		printf("P%d",safesequence[n-1]);
	}
}
