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
#define np nullptr


inline int rnd()
{
    return (rand()<<15)|rand();
}

struct Node
{
    int key, pr, sz, cnt[4];
    Node *c[2];

    Node(int k = 0)
    {
        key = k;
        pr = rnd();
        sz = 1;
        memset(cnt, 0, sizeof cnt);
        cnt[k] = 1;
        c[0] = c[1] = np;
    }
};

Node *root[10000];

void delTreap(Node *&x)
{
    if (x == np) return;
    delTreap(x->c[0]);
    delTreap(x->c[1]);
    delete x;
}

inline int sz(Node *&x)
{
    return (x == np) ? 0:x->sz;
}

inline int cnt(Node *&x, int &i)
{
    return (x == np) ? 0:x->cnt[i];
}

int getv(char &c)
{
    if (c == 'A') return 0;
    if (c == 'G') return 1;
    if (c == 'T') return 2;
    return 3;
}

void upd(Node *&x)
{
    if (x == np) return;
    x->sz = 1+sz(x->c[0])+sz(x->c[1]);

    for (int t1 = 0; t1 < 4; ++t1)
        x->cnt[t1] = cnt(x->c[0],t1)+cnt(x->c[1],t1);

    ++x->cnt[x->key];
}

void Split(Node *x, Node *&L, Node *&R, int i)
{
    if (x == np)
        L = R = np;
    else
    {
        Node *cn = new Node;
        *cn = *x;

        if (i <= sz(cn->c[0]))
            Split(cn->c[0], L, cn->c[0], i), R = cn;
        else
            Split(cn->c[1], cn->c[1], R, i-sz(cn->c[0])-1), L = cn;

        upd(cn);
    }
}

void Merge(Node *&x, Node *L, Node *R)
{
    if (L == np || R == np)
        x = (L != np) ? L:R;
    else
    {
        Node *cn = new Node;

        if (L->pr > R->pr)
        {
            *cn = *L;
            Merge(cn->c[1], cn->c[1], R);
        }
        else
        {
            *cn = *R;
            Merge(cn->c[0], L, cn->c[0]);
        }

        x = cn;
    }

    upd(x);
}

void Cross(int id1, int id2, int k1, int k2, Node *&A, Node *&B)
{
    Node *a, *b, *c, *d;
    Split(root[id1], a, b, k1+1);
    Split(root[id2], c, d, k2+1);
    Merge(A, a, d);
    Merge(B, c, b);
}

void Mutate(Node *&root, int i, int v)
{
    if (root == np) return;
    Node *cn = new Node;
    *cn = *root;
    root = cn;

    if (i == sz(cn->c[0]))
        cn->key = v;
    else if (i < sz(cn->c[0]))
        Mutate(cn->c[0], i, v);
    else
        Mutate(cn->c[1], i-sz(cn->c[0])-1, v);

    upd(cn);
}

void Count(Node *x, int k1, int k2)
{
    Node *t1, *t2;
    Split(x, x, t2, k2+1);
    Split(x, x, t1, k1);

    for (int i = 0; i < 4; ++i)
        cout << cnt(t1,i) << ' ';
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);


    srand(time(0));
    int n, q, id1, id2, k1, k2;
    char m;
    string s;
    cin >> n;

    for (int t1 = 0; t1 < n; ++t1)
    {
        root[t1] = np;
        cin >> s;

        for (char &c: s)
            Merge(root[t1], root[t1], new Node(getv(c)));
    }

    int cv = n-1; // current version
    cin >> q;

    while (q)
    {
        --q;
        cin >> s;

        if (s[1] == 'R')
        {
            cin >> id1 >> id2 >> k1 >> k2;
            Cross(id1-1, id2-1, k1-1, k2-1, root[cv+1], root[cv+2]);
            cv += 2;
        }
        else if (s[0] == 'M')
        {
            cin >> id1 >> k1 >> m;
            Mutate(root[id1-1], k1-1, getv(m));
        }
        else
        {
            cin >> id1 >> k1 >> k2;
            Count(root[id1-1], k1-1, k2-1);
        }
    }





    return 0;
}
