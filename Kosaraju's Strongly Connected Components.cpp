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
vb vis;
stack <int> S;
vector <vi> g, rg;

void DFS1(int node)
{
    vis[node] = 1;

    for (int &x: g[node])
        if (!vis[x]) DFS1(x);

    S.push(node);
}

void DFS2(int node)
{
    vis[node] = 1;
    cout << node << ' ';

    for (int &x: rg[node])
        if (!vis[x]) DFS2(x);
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    cin >> n >> m;
    g.resize(n);
    rg.resize(n);
    vis.resize(n);

    while (m)
    {
        --m;
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        rg[b].push_back(a);
    }

    for (int t1 = 0; t1 < n; ++t1)
        if (!vis[t1]) DFS1(t1);

    vis.assign(n, 0);

    while (!S.empty())
    {
        int x = S.top();
        S.pop();
        if (vis[x]) continue;
        DFS2(x);
        cout << '\n';
    }



    return 0;
}
