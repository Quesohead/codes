#include<bits/stdc++.h>
using namespace std;

long long int a[1000002],power[1000002];

int main()
{
	int t,k,i;
	long long int x;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&k);
		for(i=1;i<=k;i++)
		scanf("%lld",&a[i]);
		
		{
			
			int flag=0; x=1; 
			
			for(i=1;i<=k;i++)
			{
				x=2*(x-a[i]);
				if(i==k)
				{
					if(x!=0)
					flag=1;
				}
				else{
					if(x<=0)
					flag=1;
				}
			}
			if(flag)
			printf("No\n");
			else
			printf("Yes\n");
		}
		
	}
	return 0;
}
