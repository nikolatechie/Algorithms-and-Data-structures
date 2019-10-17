#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;

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


int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector <vi> g(n);

    for (int t1 = 0; t1 < n; ++t1)
    {
        g[t1].assign(n, 10000000LL);
        g[t1][t1] = 0;
    }

    while (m)
    {
        --m;
        int a, b, c;
        cin >> a >> b >> c;
        if (c < g[a][b]) g[a][b] = g[b][a] = c;
    }

    for (int t1 = 0; t1 < n; ++t1)
    {
        for (int t2 = 0; t2 < n; ++t2)
        {
            for (int t3 = 0; t3 < n; ++t3)
            {
                if (g[t2][t3] > g[t2][t1]+g[t1][t3])
                    g[t2][t3] = g[t2][t1]+g[t1][t3];
            }
        }
    }

    for (int t1 = 0; t1 < n; ++t1)
    {
        cout << t1 << ":  ";
        for (int t2 = 0; t2 < n; ++t2)
            cout << g[t1][t2] << ' ';
        cout << '\n';
    }


    return 0;
}
