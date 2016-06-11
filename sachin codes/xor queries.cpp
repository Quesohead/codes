#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<climits>
using namespace std;
int a[500002];
int pointer=0;


int partition(int arr[], int l, int r, int k);
 
// A simple function to find median of arr[]
int findMedian(int arr[], int n)
{
    sort(arr, arr+n);  // Sort the array
    return arr[n/2];   // Return middle element
}
 
// Returns k'th smallest element in arr[l..r] in worst case
// linear time. ASSUMPTION: ALL ELEMENTS IN ARR[] ARE DISTINCT
int kthSmallest(int arr[], int l, int r, int k)
{
    // If k is smaller than number of elements in array
    if (k > 0 && k <= r - l + 1)
    {
        int n = r-l+1; // Number of elements in arr[l..r]
 
        // Divide arr[] in groups of size 5, calculate median
        // of every group and store it in median[] array.
        int i, median[(n+4)/5]; // There will be floor((n+4)/5) groups;
        for (i=0; i<n/5; i++)
            median[i] = findMedian(arr+l+i*5, 5);
        if (i*5 < n) //For last group with less than 5 elements
            median[i++] = findMedian(arr+l+i*5, n%5); 
 
        // Find median of all medians using recursive call.
        // If median[] has only one element, then no need
        // of recursive call
        int medOfMed = (i == 1)? median[i-1]:
                                 kthSmallest(median, 0, i-1, i/2);
 
        // Partition the array around a random element and
        // get position of pivot element in sorted array
        int pos = partition(arr, l, r, medOfMed);
 
        // If position is same as k
        if (pos-l == k-1)
            return arr[pos];
        if (pos-l > k-1)  // If position is more, recur for left
            return kthSmallest(arr, l, pos-1, k);
 
        // Else recur for right subarray
        return kthSmallest(arr, pos+1, r, k-pos+l-1);
    }
 
    // If k is more than number of elements in array
    return INT_MAX;
}
 
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
 
// Standard partition process of QuickSort(). It considers
// the last element as pivot and moves all smaller element
// to left of it and greater elements to right. This function
// is used by randomPartition()
int partition(int arr[], int l, int r, int x)
{
    // Search for x in arr[l..r] and move it to end
    int i;
    for (i=l; i<r; i++)
        if (arr[i] == x)
           break;
    swap(&arr[i], &arr[r]);
 
    // Standard partition algorithm
    i = l;
    for (int j = l; j <= r - 1; j++)
    {
        if (arr[j] <= x)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}
 


void f0(int x)
{
	a[pointer]=x;
	pointer++;
}
void f1(int l, int r, int x)
{
	int y,max,i,num;
	max=a[l-1]^x;
	num=a[l-1];
	for(i=l-1;i<=r-1;i++)
	{
		y=a[i]^x;
		if(y>max)
		{
			max=y;
			num=a[i];
		}
	}
	printf("%d\n",num);
}
void f2(int x)
{
	int i;
	for(i=0;i<x;i++)
	pointer--;
}
void f3(int l,int r ,int x)
{
	int i,count=0;
	for(i=l-1;i<=r-1;i++)
	{
		if(a[i]<=x)
		count++;
	}
	printf("%d\n",count);
}
void f4(int l,int r,int x)
{
	/*int i,d,b[500002];
	for(i=l-1;i<=r-1;i++)
	{
		b[i-l+1]=a[i];
	}
	d=r-l+1;
	sort(b,b+d);*/
	int d=kthSmallest(a, l-1, r-1, x);
	printf("%d\n",d);
}

int main()
{
	int m,i,x,l,r,id;
	scanf("%d",&m);
	while(m--)
    {
    	scanf("%d",&id);
    	if(id==0)
    	{
    		scanf("%d",&x);
    		f0(x);
    	}
    	if(id==1)
    	{
    		scanf("%d%d%d",&l,&r,&x);
    		f1(l,r,x);
    	}
    	if(id==2)
    	{
    		scanf("%d",&x);
    		f2(x);
    	}
    	if(id==3)
    	{
    		scanf("%d%d%d",&l,&r,&x);
    		f3(l,r,x);
    	}
    	if(id==4)
    	{
    		scanf("%d%d%d",&l,&r,&x);
    		f4(l,r,x);
    	}
    }
    return 0;
}
