#include <iostream> 
#include<stdio.h>
#include<math.h>
 

#define MAX 1000003
#define LMT 1003
#define LEN 1000003
using namespace std;
 	long long int l=1;
  long long int primes[LEN];
  long long int arr[MAX],isprime[MAX],S[MAX],num[MAX];
void sieve()
{
	for(int i=4;i<MAX;i+=2)
		arr[i]=1;
	arr[0]=1;
	arr[1]=1;
	arr[2]=0;
	 
	for(long long int i=3;i<=sqrt(MAX);i+=2)
	{
	
		if(!arr[i])
		{
			
      		for(long long int j=i*i,k=i*2; j<MAX; j+=k)
      		{
      
				arr[j]=1;
			}
		}
	}
	
	primes[0] = 2;
	for(long long int i=3;i<=MAX;i=i+2)
	{
	
		if(!arr[i])
		{
			isprime[i]=1;
       		primes[l++] = i;
   		}
	}
 
		
}


int main()
{
	long long int a,b,j,n,i,x,count,c,check;
	int t,h;
	sieve();
/*	for(i=0;i<l;i++)
	cout<<prime[i]<<"  ";*/
	scanf("%d",&t);
	while(t--)
	{
	
		scanf("%lld%lld",&a,&b);
		for(i=a;i<=b;i++)
		{
			//h=i-a;
			S[i-a]=1;
			num[i-a]=i;
		}
		
		j=0;
		while( primes[j]*primes[j]<=b)         //or simply write j<l      
		{
			for(i=((((a-1)/primes[j])+1)*primes[j]);i<=b;i+=primes[j])
			{
				count=0;
				while(num[i-a]%primes[j]==0)
				{
					num[i-a]=num[i-a]/primes[j];  //cout<<"jjk";
					count++;
				}
				S[i-a]*=(count+1);
			}
			j++;
		}
		c=0;
		for(i=a;i<=b;i++)
		{
			//h=i-a;
			if(num[i-a]!=1)
			S[i-a]*=2;
			if(arr[S[i-a]]==0)
			c++;
		}
		printf("%lld\n",c);
	}
	return 0;
}


