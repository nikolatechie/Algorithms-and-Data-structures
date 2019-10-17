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


int n1, n2, m;
vi connect;
vector <vi> g;
vector <bool> vis;

bool solve(int node)
{
    vis[node] = 1;

    for (int t1 = 0; t1 < g[node].size(); ++t1)
    {
        int x = g[node][t1];

        if (connect[x] == -1 || (!vis[connect[x]] && solve(connect[x])))
        {
            connect[x] = node;
            return 1;
        }
    }

    return 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    cin >> n1 >> n2 >> m;
    g.resize(n1);
    connect.assign(n2, -1);
    int ans = 0;

    while (m)
    {
        --m;
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    for (int t1 = 0; t1 < n1; ++t1)
    {
        vis.assign(n1, 0);
        ans += solve(t1);
    }

    cout << ans << '\n';

    for (int t1 = 0; t1 < n2; ++t1)
        cout << connect[t1] << ' ' << t1 << '\n';



    return 0;
}
