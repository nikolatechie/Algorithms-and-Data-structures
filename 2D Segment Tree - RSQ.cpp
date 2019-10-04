// Range Sum Query using 2D Segment Tree
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


const int N = 1025, M = N;
int A[N][M];
int n, m;
vector <vector <int>> st;

void BuildNode(int &_node, int &_sl, int node, int sl, int sr)
{
    if (sl == sr)
    {
        st[_node][node] = A[_sl][sl];
        return;
    }

    int mid = (sl+sr)>>1, ln = node<<1, rn = ln|1;
    BuildNode(_node, _sl, ln, sl, mid);
    BuildNode(_node, _sl, rn, mid+1, sr);
    st[_node][node] = st[_node][ln] + st[_node][rn]; // combine two inner nodes
}

void Combine(int &node)
{
    int ln = node<<1, rn = ln|1;

    for (int t1 = 0; t1 < st[node].size(); ++t1)
        st[node][t1] = st[ln][t1] + st[rn][t1];
}

void Build(int node, int sl, int sr)
{
    st[node].resize((m<<2)+5);

    if (sl == sr)
    {
        BuildNode(node, sl, 1, 0, m-1);
        return;
    }

    int mid = (sl+sr)>>1, ln = node<<1, rn = ln|1;
    Build(ln, sl, mid);
    Build(rn, mid+1, sr);
    Combine(node);
}

int QueryNode(int &_node, int node, int sl, int sr, int &l, int &r)
{
    if (sl > r || sr < l) return 0;
    if (sl >= l && sr <= r) return st[_node][node];

    int mid = (sl+sr)>>1;
    return QueryNode(_node, node<<1, sl, mid, l, r) +
        QueryNode(_node, (node<<1)|1, mid+1, sr, l, r);
}

int Query(int node, int sl, int sr, int &x1, int &y1, int &x2, int &y2)
{
    if (sl > x2 || sr < x1) return 0;
    if (sl >= x1 && sr <= x2) return QueryNode(node, 1, 0, m-1, y1, y2);

    int mid = (sl+sr)>>1;
    return Query(node<<1, sl, mid, x1, y1, x2, y2) +
        Query((node<<1)|1, mid+1, sr, x1, y1, x2, y2);
}

void UpdateNode(int &_node, int &y, int &v, int node, int sl, int sr)
{
    if (sl == sr)
    {
        st[_node][node] = v;
        return;
    }

    int mid = (sl+sr)>>1, ln = node<<1, rn = ln|1;

    if (y <= mid)
        UpdateNode(_node, y, v, ln, sl, mid);
    else
        UpdateNode(_node, y, v, rn, mid+1, sr);

    st[_node][node] = st[_node][ln] + st[_node][rn];
}

void Update(int node, int sl, int sr, int &x, int &y, int &v)
{
    if (sl == sr)
    {
        UpdateNode(node, y, v, 1, 0, n-1); // update inner node
        return;
    }

    int mid = (sl+sr)>>1, ln = node<<1, rn = ln|1;

    if (x <= mid)
        Update(ln, sl, mid, x, y, v);
    else
        Update(rn, mid+1, sr, x, y, v);

    Combine(node);
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    cin >> n >> m;
    st.resize((n<<2)+5);

    for (int t1 = 0; t1 < n; ++t1)
    {
        for (int t2 = 0; t2 < m; ++t2)
            cin >> A[t1][t2];
    }

    Build(1, 0, n-1);

    int q;
    cin >> q;

    while (q)
    {
        --q;
        int opt;
        cin >> opt;

        if (opt == 1)
        {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            cout << Query(1, 0, n-1, a, b, c, d) << '\n';
        }
        else
        {
            int a, b, v;
            cin >> a >> b >> v;
            Update(1, 0, n-1, a, b, v);
        }
    }


    return 0;
}
