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
using vii = vi::iterator;

#define INF (1<<30)
#define MOD 1000000007
#define mp make_pair
#define mt make_tuple
#define all(c) c.begin(), c.end()
#define ms(name,val) memset(name, val, sizeof name)
#define np nullptr


int n, m, s, t;
vi p;
vector <vi> g, gm;

bool BFS()
{
    queue <int> Q;
    vector <bool> vis(n, 0);
    p.assign(n, -1);
    Q.push(s);

    while (!Q.empty())
    {
        int node = Q.front();
        vis[node] = 1;
        Q.pop();

        for (int t1 = 0; t1 < g[node].size(); ++t1)
        {
            int x = g[node][t1];

            if (!vis[x] && gm[node][x] > 0)
            {
                Q.push(x);
                vis[x] = 1;
                p[x] = node;
            }
        }
    }

    return vis[t];
}

int maxFlow()
{
    int ans = 0;

    while (BFS())
    {
        int bottleneck = INF;

        for (int node = t; node != s; node = p[node])
            bottleneck = min(bottleneck, gm[p[node]][node]);

        ans += bottleneck;

        for (int node = t; node != s; node = p[node])
        {
            int par = p[node];
            gm[par][node] -= bottleneck;
            gm[node][par] += bottleneck;
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    cin >> n >> m;
    g.resize(n);
    gm.resize(n);

    for (int t1 = 0; t1 < n; ++t1)
        gm[t1].resize(n);

    while (m)
    {
        --m;
        int a, b, c;
        cin >> a >> b >> c;

        if (!gm[a][b])
        {
            g[a].push_back(b);
            gm[a][b] = c;
        }
        else gm[a][b] = c;
    }

    cin >> s >> t;
    cout << maxFlow() << '\n';


    return 0;
}
