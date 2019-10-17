#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;

using ci = const int;
using ld = long double;
using llint = long long;
using ullint = unsigned long long;
using pii = pair <int,int>;
using pcc = pair <char,char>;
using pss = pair <string,string>;
using vi = vector <int>;
using vb = vector <bool>;
using vii = vi::iterator;

#define INF (1<<30)
#define MOD 1000000007
#define mp make_pair
#define mt make_tuple
#define all(c) c.begin(), c.end()
#define ms(name,val) memset(name, val, sizeof name)
#define np nullptr


const int MX = 100;
int n, DP[MX][MX][MX], g[MX][MX];

int shortestPath(int a, int b, int k)
{
    for (int len = 0; len <= k; ++len)
    {
        for (int src = 0; src < n; ++src)
        {
            for (int dest = 0; dest < n; ++dest)
            {
                // initialize value
                DP[src][dest][len] = INF;

                // 1st base case
                if (!len && src == dest)
                    DP[src][dest][0] = 0;

                // 2nd base case
                if (len == 1 && g[src][dest] != INF)
                    DP[src][dest][1] = g[src][dest];

                if (len < 2) continue;
                // now solve for general cases

                // adjacents of src
                for (int adj = 0; adj < n; ++adj)
                {
                    if (adj != src && adj != dest &&
                        g[src][adj] != INF && DP[adj][dest][len-1] != INF)
                    {
                        DP[src][dest][len] = min(DP[src][dest][len],
                                                 g[src][adj] + DP[adj][dest][len-1]);
                    }
                }
            }
        }
    }

    return DP[a][b][k];
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    int m;
    cin >> n >> m;

    for (int t1 = 0; t1 < n; ++t1)
    {
        for (int t2 = 0; t2 < n; ++t2)
            g[t1][t2] = INF;

        g[t1][t1] = 0;
    }

    while (m)
    {
        --m;
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = c;
    }

    cout << shortestPath(0, n-1, n>>1) << '\n';


    return 0;
}
