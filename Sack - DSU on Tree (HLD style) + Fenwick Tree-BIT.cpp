// Solution for Codeforces problem 375D using Sack and Fenwick Tree/BIT
#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;

using ci = const int;
using ld = long double;
using ll = long long;
using ull = unsigned long long;
using pii = pair <int,int>;
using pcc = pair <char,char>;
using pll = pair <ll,ll>;
using pss = pair <string,string>;
using vi = vector <int>;
using vb = vector <bool>;
using vpii = vector <pii>;
using vll = vector <ll>;
using vii = vi::iterator;

#define INF (0x3f3f3f3f)
#define MOD 1000000007
#define mt make_tuple
#define all(c) c.begin(), c.end()
#define ms(name,val) memset(name, val, sizeof (name))
#define np nullptr


ci N = (1e5)+5;
int n, ft[N], col[N], cnt[N], sz[N], sc[N], ans[N], skip;
vector <vi> g;
vector <vpii> qs;

void Update(int i, int val)
{
    for (; i < N; i += i&(-i))
        ft[i] += val;
}

int Query(int i)
{
    int res = 0;

    for (; i; i -= i&(-i))
        res += ft[i];

    return res;
}

int Query(int i, int j)
{
    return Query(j)-(i < 1 ? 0:Query(i-1));
}

void DFS(int x, int p)
{
    sz[x] = 1;

    for (ci &y: g[x])
    {
        if (y != p)
        {
            DFS(y, x);
            sz[x] += sz[y];

            if (sz[y] > sz[sc[x]])
                sc[x] = y;
        }
    }
}

void Add(int x, int p, int val)
{
    Update(cnt[col[x]]+1, -1);
    cnt[col[x]] += val;
    Update(cnt[col[x]]+1, 1);

    for (ci &y: g[x])
    {
        if (y != p && y != skip)
            Add(y, x, val);
    }
}

void DFS(int x, int p, bool keep)
{
    for (ci &y: g[x])
    {
        if (y != p && y != sc[x])
            DFS(y, x, 0);
    }

    if (sc[x])
        DFS(sc[x], x, 1), skip = sc[x];

    Add(x, p, 1);

    // now answer queries
    for (const pii &it: qs[x])
        ans[it.second] = Query(it.first+1, N-1);

    skip = 0;

    if (!keep)
        Add(x, p, -1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    int q;
    cin >> n >> q;
    g.resize(n+1);
    qs.resize(n+1);

    for (int t1 = 1; t1 <= n; ++t1)
        cin >> col[t1];

    for (int t1 = 1; t1 < n; ++t1)
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for (int t1 = 0; t1 < q; ++t1)
    {
        int v, k;
        cin >> v >> k;
        qs[v].push_back({k, t1});
    }

    DFS(1, -1);
    DFS(1, -1, 0);

    for (int t1 = 0; t1 < q; ++t1)
        cout << ans[t1] << ' ';

    cout << '\n';


    return 0;
}
