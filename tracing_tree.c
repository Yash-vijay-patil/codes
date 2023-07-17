#include<stdio.h>
void recursion(int n)
{

    for(int i=0;i<n;i++)
    {
        printf("%d ",n);
    }
    recursion(n-1);
}
void main()
{
    int n;
    printf("enter n:- ");
    scanf("%d",&n);
    recursion(n);
}
