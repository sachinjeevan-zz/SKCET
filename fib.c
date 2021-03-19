#include<stdio.h>
long long int fib(long long int n,long long int dp[]) //  f(n) = 2^n // f(n) = n
{
    if(n<=1)
    {
        dp[n] = n;
        return n;
    }
    else
    {
        long long int a,b;
        a = dp[n-1]==-1?fib(n-1,dp):dp[n-1];
        b = dp[n-2]==-1?fib(n-2,dp):dp[n-2];
        dp[n] = a+b;
        return a+b;
    }
}
int main()
{
    long long int n;
    scanf("%lld",&n);
    long long int dp[n+1];
    for(long long int i=0;i<=n;i++)
    {
        dp[i] = -1;
    }
    long long int ans = fib(n,dp);
    printf("%lld",ans);
}