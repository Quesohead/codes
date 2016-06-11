#include<iostream>
#include<stdio.h>
#include <string.h>
using namespace std;

int a[100007],primes[10009],k=0;

void SieveOfEratosthenes(int n)
{
	int i,j;
	for(i=2;i<=n;i++)
	{
		if(a[i]==0)
	 	{
	 		primes[k++]=i;
	 		j=2;
	 		while((i*j)<=n)
	 		{
	 			a[i*j]=1;
	 			j++;
	 		}
	 	}
	}
}

int main()
{
	int t,i,n,x,count,pos;
	SieveOfEratosthenes(10002);
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		count=0;
		for(i=0;i<k;i++)
		{
			x=n-(2*primes[i]);
			if(x>=2)
			{
				if(a[x]==0)
				count++;
			}
			
		}
		printf("%d\n",count);
	}
	return 0;
}

