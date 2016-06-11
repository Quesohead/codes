#include<iostream>
#include<stdio.h>
using namespace std;

int a[5000005],primes[5000005],k=0;
long long arr[5000005];

void SieveOfEratosthenes()
{
	int i,j;
	for(i=2;i<=5000001;i++)
	{
		if(a[i]==0)
	 	{
	 		primes[k++]=i;
	 		j=2;
	 		while((i*j)<=5000001)
	 		{
	 			a[i*j]=1;
	 			j++;
	 		}
	 	}
	}
	int c=1;
	arr[1]=1;
	for(int i=2;i<=5000001;i++)
	{
		if(a[i]==0)
			c++;
		arr[i]=(arr[i-1]*c)%1000000007;
	}
}

/*long long int countt(int n)
{
	int i;
	long long int c=0;
	for(i=0;i<k;i++)
	{
		if(primes[i]<=n)
		c++;
		else
		break;
	}
	return c+1;
}

long long int memoization(int n)
{//cout<<"dgg";
	arr[1]=1;
	arr[2]=2;
	if(arr[n]!=0)
	return arr[n];
	else
	{
		long long int x=countt(n);
		arr[n]=(x*memoization(n-1))%1000000007;
		return a[n];
	}
		
}
*/
int main()
{
	int t,n,m,i,c;
	long long int s;
	SieveOfEratosthenes();
	//memoization(5000002);
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		
		printf("%lld\n",arr[n]);
	}
	return 0;
}
