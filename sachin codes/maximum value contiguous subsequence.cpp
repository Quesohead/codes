#include<stdio.h>
 
int max(int x, int y)
{ return (y > x)? y : x; }
 
int maxSubArraySum(int a[], int size)
{
   int max_so_far = a[0], i;
   int curr_max = a[0];
 
   for (i = 1; i < size; i++)
   {
        curr_max = max(a[i], curr_max+a[i]);
        max_so_far = max(max_so_far, curr_max);
   }
   return max_so_far;
}
 int main()
{
   int a[] =  {-2, -3, 4, -1, -2, 1, 5, -3};
   int n = sizeof(a)/sizeof(a[0]);
   int max_sum = maxSubArraySum(a, n);
   printf("Maximum contiguous sum is %d\n", max_sum);
   return 0;
}/*Now try below question
Given an array of integers (possibly some of the elements negative),
 write a C program to find out the *maximum product* possible by adding 'n' consecutive integers in the array,
  n <= ARRAY_SIZE. Also give where in the array this sequence of n integers starts*/
