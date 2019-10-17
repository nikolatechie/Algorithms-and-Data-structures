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

    int n, m, s;
    cin >> n >> m >> s;
    vector <vector <pii>> g(n);

    for (int t1 = 0; t1 < m; ++t1)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b,c});
        g[b].push_back({a,c});
    }

    set <pii> S; // dist, node
    S.insert({0, s});

    for (int t1 = 0; t1 < n; ++t1)
        if (t1 != s) S.insert({INF, t1});

    vb vis(n, 0);
    vi p(n, -1), dist(n, INF);
    dist[s] = 0;

    for (int t1 = 0; t1 < n-1; ++t1)
    {
        int node = S.begin()->second;
        int ndist = S.begin()->first;
        S.erase(S.begin());
        vis[node] = 1;

        for (int t2 = 0; t2 < g[node].size(); ++t2)
        {
            int x = g[node][t2].first;
            int y = g[node][t2].second;
            if (vis[x]) continue;

            if (dist[x] > ndist+y)
            {
                S.erase({dist[x], x});
                dist[x] = ndist+y;
                S.insert({dist[x], x});
                p[x] = node; // for finding the path
            }
        }
    }

    cout << '\n';

    for (int t1 = 0; t1 < n; ++t1)
    {
        cout << dist[t1] << " ->  ";
        int node = t1;

        while (node != -1)
        {
            cout << node << ' ';
            node = p[node];
        }

        cout << '\n';
    }


    return 0;
}
