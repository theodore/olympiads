#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
int main ()
{
	int l1,l2,i,j,k,a[505],b[505],f[505][505],p[505][505],len,I,J,res[505];
	while(scanf("%d",&l1)!=EOF)
	{
		for(i=0;i<l1;i++)
			scanf("%d",&a[i]);
		scanf("%d",&l2);
		for(i=0;i<l2;i++)
			scanf("%d",&b[i]);
		for(i=0;i<=l1;i++)
			for(j=0;j<=l2;j++)
			{
				f[i][j]=0;
				p[i][j]=-1;
			}
		len=0;I=0;J=0;
		for(i=1;i<=l1;i++)
		{
			k=0;
			for(j=1;j<=l2;j++)
			{
				f[i][j]=f[i-1][j];
				if(a[i-1]>b[j-1] && f[i][j]>f[i][k])
					k=j;
				if(a[i-1]==b[j-1] && f[i][j]<f[i][k]+1)
				{
					f[i][j]=f[i][k]+1;
					p[i][j]=k;
					if(f[i][j]>len)
					{
						len=f[i][j];
						I=i;J=j;
					}
				}
			}
		}
		printf("%d\n",len);
		k=len;
		while(k)
		{
			if(p[I][J]>-1)
			{
				res[k--]=b[J-1];
				J=p[I][J];
			}
			I--;
		}
		for(i=1;i<=len;i++)
			printf("%d ",res[i]);
		printf("\n");
	}
	return 0;
}
