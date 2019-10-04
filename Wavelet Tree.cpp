#include <bits/stdc++.h>
using namespace std;

typedef unsigned short usint;
typedef unsigned uint;
typedef long lint;
typedef short sint;
typedef long double ld;
typedef long long llint;
typedef unsigned long ulint;
typedef unsigned long long ullint;

#define INF (1<<30)
#define MOD 1000000007
#define mp make_pair
#define mt make_tuple
#define pii pair <int,int>
#define pcc pair <char,char>
#define pss pair <string,string>
#define all(c) c.begin(),c.end()
#define ms(name,val) memset(name, val, sizeof name)
#define np nullptr


int A[100001];

struct Node
{
    int mn, mx;
    vector <int> B;
    Node *c[2];

    Node(int _mn = INT_MAX, int _mx = INT_MIN)
    {
        mn = _mn;
        mx = _mx;
        c[0] = c[1] = np;
    }
};

void delTree(Node *&x)
{
    if (x == np) return;
    delTree(x->c[0]);
    delTree(x->c[1]);
    delete x;
}

inline void upd(Node *&x, int &v)
{
    if (x == np) return;
    x->mn = min(x->mn,v);
    x->mx = max(x->mx,v);
}

void Build(Node *&x, int *from, int *to)
{
    if (x->mn == x->mx || from >= to) return;
    x->B.push_back(0);
    int mid = (x->mn+x->mx)>>1;
    Node *L = new Node, *R = new Node;
    auto f = [mid](int &x) { return (x <= mid); };

    for (auto it = from; it != to; ++it)
    {
        x->B.push_back(x->B.back()+f(*it));
        if (*it <= mid) upd(L,*it); else upd(R,*it);
    }

    auto pivot = stable_partition(from, to, f);
    x->c[0] = L, x->c[1] = R;
    Build(x->c[0], from, pivot);
    Build(x->c[1], pivot, to);
    if (L->mn == INT_MAX) x->c[0] = np, delete L;
    if (R->mn == INT_MAX) x->c[1] = np, delete R;
}

int Frequency(Node *x, int L, int R, int &v) // return frequency of number 'v' in range [L,R]
{
    while (x != np)
    {
        if (v < x->mn || v > x->mx) return 0;
        if (x->mn == x->mx) return R-L;
        int mid = (x->mn+x->mx)>>1;

        if (v <= mid)
            L = x->B[L], R = x->B[R], x = x->c[0];
        else
            L -= x->B[L], R -= x->B[R], x = x->c[1];
    }

    return 0;
}

int LTE(Node *x, int L, int R, int &v) // returns count of numbers less than or equal to 'v' in range [L,R]
{
    if (L > R || v < x->mn) return 0;
    if (x->mx <= v) return R-L;
    return LTE(x->c[0], x->B[L], x->B[R], v)+LTE(x->c[1], L-x->B[L], R-x->B[R], v);
}

int Kth(Node *x, int L, int R, int k) // returns k-th number in range [L,R], aka k-th order statistic
{
    if (L > R) return 0;
    if (x->mn == x->mx) return x->mn;
    int cntLeft = x->B[R]-x->B[L];
    if (k <= cntLeft) return Kth(x->c[0], x->B[L], x->B[R], k);
    return Kth(x->c[1], L-x->B[L], R-x->B[R], k-cntLeft);
}

int main()
{
    ios_base::sync_with_stdio(0);


    int n, q;
    cin >> n;
    Node *root = new Node;

    for (int t1 = 1; t1 <= n; ++t1)
    {
        cin >> A[t1];
        upd(root,A[t1]);
    }

    Build(root, A+1, A+n+1);
    cin >> q;

    while (q)
    {
        --q;
        char c;
        int L, R, v;
        cin >> c;

        if (c == 'F')
        {
            cin >> v >> L >> R;
            cout << Frequency(root, L-1, R, v) << '\n';
        }
        else if (c == 'L')
        {
            cin >> v >> L >> R;
            cout << LTE(root, L-1, R, v) << '\n';
        }
        else if (c == 'K')
        {
            cin >> v >> L >> R;
            cout << Kth(root, L-1, R, v) << '\n';
        }
    }

    delTree(root), root = np;


    return 0;
}
