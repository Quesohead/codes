#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

int main()
{
 int arr[]={2, 4, 9, 16, 25, 64, 289, 729, 1681, 2401, 3481, 4096, 5041, 7921, 10201, 15625, 17161, 27889, 28561, 29929, 65536, 83521, 85849, 146689, 262144, 279841, 458329, 491401, 531441, 552049, 579121, 597529, 683929, 703921, 707281, 734449, 829921,1190281 };
int t;
 cin>>t;
 int a,b;
 while(t--)
 {
         cin>>a>>b;
         int a1 = 0,a2=0;
         while(arr[a1++]<a);
         while(arr[a2++]<b);
         cout<<a2-a1<<endl;
 }
 return 0;
}

