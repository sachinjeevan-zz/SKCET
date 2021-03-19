#include<stdio.h>
void func(int n)
{
    if(n>0)
    {
        printf("%d ",n);
        func(n-1);
        printf("%d ",n);
    }
}
int main()
{
    int n=3;
    func(n);
}
// 3 2 1 1 2 3