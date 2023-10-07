#include <iostream>
#include <cstdlib>
using namespace std;

#define modnum 2147483647
#define Size 2010

long long dp[Size][Size];
long long head[Size];

long long max(long long a, long long b)
{
    if (a > b)
        return a;
    else
        return b;
}

long long min(long long a, long long b)
{
    if (a > b)
        return b;
    else
        return a;
}
int main()
{
    long long N, Lmin, Rmax, ans = 0;
    int i, j;
    cin>>N;
    cin>>head[0];
    dp[1][head[0]] = 1;
    for (i = 1; i <= N; i++)
    {
        cin>>head[i];
        for (j = 0; j < N + 2; j++)
        {
            Lmin = min(head[i - 1], j);
            Rmax = max(head[i - 1], j);
            if (head[i] >= Rmax)
                dp[i][Lmin] = (dp[i - 1][j] + dp[i][Lmin]) % modnum;
            else if (head[i] <= Lmin)
                dp[i][Rmax] = (dp[i - 1][j] + dp[i][Rmax]) % modnum;
            else
            {
                dp[i][Lmin] = (dp[i - 1][j] + dp[i][Lmin]) % modnum;
                dp[i][Rmax] = (dp[i - 1][j] + dp[i][Rmax]) % modnum;
            }
        }
    }
    for (i = 0; i < N + 2; i++)
        ans = (ans + dp[N][i]) % modnum;
    cout<<ans<<endl;
}