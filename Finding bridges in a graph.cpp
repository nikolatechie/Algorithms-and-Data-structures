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


int n, m;
vi disc, low;
vector <vi> g;

void DFS(int node, int p)
{
    static int time = 0;
    disc[node] = low[node] = ++time;

    for (int &x: g[node])
    {
        if (!disc[x])
        {
            DFS(x, node);
            low[node] = min(low[node], low[x]);

            if (low[x] > disc[node])
                cout << node << ' ' << x << '\n';
        }
        else if (x != p)
            low[node] = min(low[node], disc[x]);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    cin >> n >> m;
    g.resize(n);
    disc.resize(n);
    low.resize(n);

    while (m)
    {
        --m;
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for (int t1 = 0; t1 < n; ++t1)
        if (!disc[t1]) DFS(t1, -1);



    return 0;
}
