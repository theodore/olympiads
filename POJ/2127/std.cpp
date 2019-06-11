#include <cstdio>
#include <cstring>

int a[505],b[505];
int dp[505][505];
int n,m;
int path[505][505];
int I,J,ans,res[505];
int main()
{
	int i,j,k;
	while(scanf("%d",&n)!=-1)
	{
		ans=0;
		for(i=0;i<n;i++)
			scanf("%d",&a[i]);
		scanf("%d",&m);
		for(i=0;i<m;i++)
			scanf("%d",&b[i]);
		memset(path,-1,sizeof(path));
		memset(dp,0,sizeof(dp));
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
			{
				dp[i][j]=dp[i-1][j];
				if(a[i-1]==b[j-1])
				{
					int max=0;
					for(k=1;k<j;k++)
						if(b[k-1]<b[j-1]&&dp[i][max]<dp[i][k])
							max=k;
					if(dp[i][max]+1>dp[i][j])
					{
						dp[i][j]=dp[i][max]+1;
						path[i][j]=max;
						if(dp[i][j]>ans)
						{
							ans=dp[i][j];
							I=i;
							J=j;
						}
					}
				}
			}
		printf("%d\n",ans);
		k=ans;
		while(ans)
		{
			if(path[I][J]>=0)
			{
				res[ans--]=b[J-1];
				J=path[I][J];
			}
			I--;
		}
		for(i=1;i<=k;i++)
		{
			printf("%d",res[i]);
			putchar(' ' + (i == k) * ('\n' - ' '));
		}
	}
}
