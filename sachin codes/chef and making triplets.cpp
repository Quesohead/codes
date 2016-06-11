#include<bits/stdc++.h>
using namespace std;
 
long long int a[300007];
int hash[300007];
 
long long int sd=73,x,y,z,t,w;
 
void random_seed(long long int s)
{
	x=s;
  y = x * s;
  z = y * s;
  w = z * s;
}
 
long long int random_number()
{	 
	t = x ^ (x << 11);
  x = y; y = z; z = w;                       
  return w = abs((w ^ (w >> 19)) ^ (t ^ (t >> 8))); 
}
 
int search_it(long long int x,int n)
{
	for(int i=0;i<3*n;i++)
	{
		if(a[i]==x&&hash[i]==1)
		return i;
	}
	return -1;
}
 
int main()
{
	int n,i,id1,id2,id3,j;
	long long int x,y,z,low,high,diff,sum,mid;
	
	scanf("%d",&n);
	sum=0;
	for(i=0;i<3*n;i++)
	{
		scanf("%lld",&a[i]);
		hash[i]=1;
		sum=sum+a[i];
	}
 	
 	map<long long int, int> m;
	map<long long int, int> :: iterator it;
	
	random_seed(sd++);
	for(i=0;i<100000;i++)
	{
		id1=random_number()%(3*n);  id2=random_number()%(3*n);  id3=random_number()%(3*n); 
		sum=a[id1]+a[id2]+a[id3];
		m[sum]++;
	} 
	int mm=0;
	for(it = (m).begin(); it != (m).end(); it++)
	{//cout<<"sum="<<it->first<<"count="<<it->second<<endl;
		if(it->second>mm)
		{
			mm=it->second;
			mid=it->first;
		}
	}
	
	//mid=sum/n;
 
	vector<pair<int,pair<int,int> > > res;
	vector<pair<int,pair<int,int> > > final_res;
	int ans=0;  int count=0;  long long int s=-1;
	
	
	for(i=0;i<=0;i++)
	{
		count=0;  res.clear();
		
		sum=mid;//-(random_number()%diff);  
		//cout<<"sum="<<sum<<endl;
		for(j=0;j<15000;j++)
		{
			id1=random_number()%(3*n);  id2=random_number()%(3*n);
			if(id1!=id2&&hash[id1]==1&&hash[id2]==1)
			{
				long long int rem = sum-(a[id1]+a[id2]);
				id3=search_it(rem,n);
				if(id3!=-1&&id1!=id3&&id2!=id3)
				{
					hash[id1]=0;  hash[id2]=0;   hash[id3]=0; 
					count++;
					res.push_back(make_pair(id1+1,make_pair(id2+1,id3+1)));
				}
			}
		}
		if(count>ans)
		{
			s=sum;	
			ans=count;
			final_res=res;
		}
	}
	
	cout<<ans<<endl;
	for(int i=0;i<final_res.size();i++)
	cout<<final_res[i].first<<" "<<final_res[i].second.first<<" "<<final_res[i].second.second<<" ";
	
	return 0;
}  
