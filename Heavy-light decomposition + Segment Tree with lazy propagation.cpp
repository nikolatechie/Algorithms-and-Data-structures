// Solution for a Codeforces problem 191C
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


ci N = 100005, LN = 18;
int n;
vector <vi> g;
vector <pii> edge;
int posInBase[N], ptr, base[N];
int depth[N], sz[N], link[N][LN], nodes[N], childID[N], ans[N];
int chainNo, chain[N], chainHead[N], chainSz[N], chainPos[N];
int st[N<<2], lazy[N<<2];

void DFS(int x, int p, int d)
{
    link[x][0] = p;
    depth[x] = d;
    sz[x] = 1;

    for (ci &y: g[x])
    {
        if (y != p)
        {
            DFS(y, x, d+1);
            sz[x] += sz[y];
        }
    }
}

void HLD(int x)
{
    if (chainHead[chainNo] == -1) chainHead[chainNo] = x;
    chain[x] = chainNo;
    chainPos[x] = chainSz[chainNo]++;
    nodes[ptr] = x;
    posInBase[x] = ptr++;

    int sc = -1;

    for (ci &y: g[x])
    {
        if (y != link[x][0])
        {
            if (sc == -1 || sz[sc] < sz[y]) sc = y;
        }
    }

    if (sc != -1)
        HLD(sc);

    for (ci &y: g[x])
    {
        if (y != link[x][0] && y != sc)
        {
            ++chainNo;
            HLD(y);
        }
    }
}

int LCA(int a, int b)
{
    if (depth[a] < depth[b]) return LCA(b, a); // or just swap

    for (int lvl = LN-1; lvl >= 0; --lvl)
        if (depth[a]-(1<<lvl) >= depth[b]) a = link[a][lvl];

    if (a != b)
    {
        for (int lvl = LN-1; lvl >= 0; --lvl)
        {
            if (link[a][lvl] != link[b][lvl])
                a = link[a][lvl],
                b = link[b][lvl];
        }

        a = link[a][0];
    }

    return a;
}

void pd(int node, int sl, int sr)
{
    if (lazy[node])
    {
        if (sl != sr)
            lazy[node<<1] += lazy[node],
            lazy[(node<<1)|1] += lazy[node];

        st[node] += (sr-sl+1)*lazy[node];
        lazy[node] = 0;
    }
}

void ST_Add(int node, int sl, int sr, int l, int r, int v)
{
    if (sl > sr || l > r) return;
    pd(node, sl, sr);
    if (sl > r || sr < l) return;

    if (sl >= l && sr <= r)
    {
        lazy[node] += v;
        pd(node, sl, sr);
        return;
    }

    int mid = (sl+sr)>>1;
    ST_Add(node<<1, sl, mid, l, r, v);
    ST_Add((node<<1)|1, mid+1, sr, l, r, v);
    st[node] = st[node<<1] + st[(node<<1)|1];
}

void UpChain(int x, int lca)
{
    if (x == lca) return;
    int xchain, lchain = chain[lca];

    while (1)
    {
        xchain = chain[x];

        if (xchain == lchain)
        {
            if (x == lca) return;
            ST_Add(1, 0, n-1, posInBase[lca]+1, posInBase[x], 1);
            return;
        }
        else
        {
            ST_Add(1, 0, n-1, posInBase[chainHead[xchain]], posInBase[x], 1);
            x = chainHead[xchain];
            x = link[x][0];
        }
    }
}

void Add(int a, int b)
{
    if (a == b) return;
    int lca = LCA(a, b);
    UpChain(a, lca);
    UpChain(b, lca);
}

void fillBase(int node, int sl, int sr)
{
    pd(node, sl, sr);

    if (sl == sr)
    {
        base[sl] = st[node];
        return;
    }

    int mid = (sl+sr)>>1;
    fillBase(node<<1, sl, mid);
    fillBase((node<<1)|1, mid+1, sr);
    st[node] = st[node<<1] + st[(node<<1)|1];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    g.resize(n), edge.resize(n);

    for (int t1 = 0; t1 < n-1; ++t1)
    {
        int a, b;
        cin >> a >> b;
        --a, --b;
        edge[t1] = {a, b};
        g[a].push_back(b);
        g[b].push_back(a);
    }

    ms(link, -1);
    ms(chainHead, -1);
    DFS(0, -1, 0);
    HLD(0);

    for (int lvl = 0; lvl < LN-1; ++lvl)
    {
        for (int x = 0; x < n; ++x)
        {
            if (link[x][lvl] != -1)
                link[x][lvl+1] = link[link[x][lvl]][lvl];
        }
    }

    int q;
    cin >> q;

    while (q)
    {
        --q;
        int a, b;
        cin >> a >> b;
        --a, --b;
        Add(a, b);
    }

    fillBase(1, 0, n-1);

    for (int t1 = 0; t1 < n-1; ++t1)
    {
        if (depth[edge[t1].first] > depth[edge[t1].second])
            swap(edge[t1].first, edge[t1].second);

        childID[edge[t1].second] = t1;
    }

    for (int t1 = 0; t1 < n; ++t1)
        ans[childID[nodes[t1]]] = base[t1];

    for (int t1 = 0; t1 < n-1; ++t1)
        cout << ans[t1] << ' ';

    cout << '\n';



    return 0;
}
