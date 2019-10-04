// Solution to SPOJ problem - COT
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
using vi = vector<int>;
using vii = vi::iterator;

#define INF (1<<30)
#define MOD 1000000007
#define mp make_pair
#define mt make_tuple
#define all(c) c.begin(),c.end()
#define ms(name,val) memset(name, val, sizeof name)
#define np nullptr


struct Node
{
    int s;
    Node *c[2];

    Node()
    {
        s = 0;
        c[0] = c[1] = np;
    }
};

const int N = 120000;
const int LN = 19; // try 18
Node *root[N], *nil;
int A[N], RM[N], link[N][LN], depth[N], n;
map <int,int> M;
vector <vector <int>> graf;

void Insert(Node *x, Node *&nx, int sl, int sr, int &i)
{
    nx = new Node;

    if (sl == sr)
    {
        nx->s = x->s + 1;
        return;
    }

    int mid = (sl+sr)>>1;

    if (i <= mid)
    {
        nx->c[1] = x->c[1];
        Insert(x->c[0], nx->c[0], sl, mid, i);
    }
    else
    {
        nx->c[0] = x->c[0];
        Insert(x->c[1], nx->c[1], mid+1, sr, i);
    }

    nx->s = nx->c[0]->s + nx->c[1]->s;
}

int Query(Node *a, Node *b, Node *c, Node *d, int sl, int sr, int k)
{
    if (sl == sr) return sl;

    int mid = (sl+sr)>>1;
    int cntLeft = a->c[0]->s + b->c[0]->s - c->c[0]->s - d->c[0]->s;

    if (k <= cntLeft)
        return Query(a->c[0], b->c[0], c->c[0], d->c[0], sl, mid, k);

    return Query(a->c[1], b->c[1], c->c[1], d->c[1], mid+1, sr, k-cntLeft);
}

void DFS(int cvor, int parent)
{
    link[cvor][0] = parent;
    depth[cvor] = (parent == -1) ? 1:depth[parent]+1;

    if (parent == -1)
        Insert(nil, root[cvor], 1, n, M[A[cvor]]);
    else
        Insert(root[parent], root[cvor], 1, n, M[A[cvor]]);

    for (int t1 = 0; t1 < graf[cvor].size(); ++t1)
        if (graf[cvor][t1] != parent)
            DFS(graf[cvor][t1], cvor);
}

int LCA(int a, int b)
{
    if (depth[b] > depth[a]) return LCA(b,a);

    for (int t1 = LN-1; t1 >= 0; --t1)
        if (depth[a]-(1<<t1) >= depth[b]) a = link[a][t1];

    if (a != b)
    {
        for (int t1 = LN-1; t1 >= 0; --t1)
            if (link[a][t1] != link[b][t1])
                a = link[a][t1],
                b = link[b][t1];

        a = link[a][0];
    }

    return a;
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    int q;
    cin >> n >> q;
    graf.resize(n+1);

    for (int t1 = 1; t1 <= n; ++t1)
    {
        cin >> A[t1];
        M[A[t1]];
    }

    int cnt = 1;

    for (auto &it: M)
    {
        it.second = cnt;
        RM[cnt] = it.first;
        ++cnt;
    }

    for (int t1 = 0; t1 < n-1; ++t1)
    {
        int a, b;
        cin >> a >> b;
        graf[a].push_back(b);
        graf[b].push_back(a);
    }

    nil = new Node, nil->c[0] = nil->c[1] = nil;
    ms(link, -1);
    DFS(1, -1);

    for (int lvl = 0; lvl < LN-1; ++lvl)
    {
        for (int x = 1; x <= n; ++x)
            if (link[x][lvl] != -1)
                link[x][lvl+1] = link[link[x][lvl]][lvl];
    }

    while (q)
    {
        --q;
        int a, b, k;
        cin >> a >> b >> k;
        int lca = LCA(a,b);
        cout << RM[Query(root[a], root[b], root[lca], (link[lca][0] == -1) ? nil:root[link[lca][0]], 1, n, k)] << '\n';
    }


    return 0;
}
