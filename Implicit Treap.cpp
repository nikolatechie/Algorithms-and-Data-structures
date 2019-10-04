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
	

inline int randNum()
{
    return (rand()<<15)|rand();
}

struct Node
{
    int key, pr, sz, sum, lazy, minv;
    bool rev;
    Node *c[2];

    Node(int k = 0, int p = randNum())
    {
        sum = minv = key = k;
        pr = p;
        sz = 1;
        rev = lazy = 0;
        c[0] = c[1] = np;
    }
};

void deleteTreap(Node *root)
{
    if (root == np) return;
    deleteTreap(root->c[0]);
    deleteTreap(root->c[1]);
    delete root;
}

void pushDown(Node *&root)
{
    if (root == np) return;

    if (root->lazy)
    {
        root->key += root->lazy;
        root->sum += (root->sz * root->lazy);
        if (root->c[0] != np) root->c[0]->lazy += root->lazy;
        if (root->c[1] != np) root->c[1]->lazy += root->lazy;
        root->lazy = 0;
    }

    if (root->rev)
    {
        root->rev = 0;
        swap(root->c[0], root->c[1]);
        if (root->c[0] != np) root->c[0]->rev ^= 1;
        if (root->c[1] != np) root->c[1]->rev ^= 1;
    }
}

inline int getSum(Node *&root)
{
    return (root == np) ? 0:root->sum;
}

inline int getMinv(Node *&root)
{
    return (root == np) ? INF:root->minv;
}

void updateRange(Node *&root)
{
    if (root == np) return;
    pushDown(root->c[0]);
    pushDown(root->c[1]);
    root->sum = root->key+getSum(root->c[0])+getSum(root->c[1]);
    root->minv = min(root->key, min(getMinv(root->c[0]),getMinv(root->c[1])));
}

inline int getSz(Node *&root)
{
    return (root == np) ? 0:root->sz;
}

inline void updateSz(Node *&root)
{
    if (root != np) root->sz = 1+getSz(root->c[0])+getSz(root->c[1]);
}

void inOrder(Node *&root, Node *x)
{
    if (x == np) return;
    pushDown(x);
    inOrder(root, x->c[0]);
    cout << x->key << ' ';
    inOrder(root, x->c[1]);
    updateRange(x);
    if (x == root) cout << '\n';
}

void Split(Node *root, Node *&L, Node *&R, int i)
{
    if (root == np) return void(L = R = np);
    pushDown(root);

    if (i <= getSz(root->c[0]))
    	// root->c[0] instead of R->c[0] because
    	// R = root is after the next splitting
        Split(root->c[0], L, root->c[0], i), R = root;
    else
        Split(root->c[1], root->c[1], R, i-getSz(root->c[0])-1), L = root;

    updateSz(root);
    updateRange(root);
}

void Merge(Node *&root, Node *L, Node *R)
{
    pushDown(L);
    pushDown(R);

    if (L == np || R == np)
        root = (L != np) ? L:R;
    else if (L->pr > R->pr)
        Merge(L->c[1], L->c[1], R), root = L;
    else
        Merge(R->c[0], L, R->c[0]), root = R;

    updateSz(root);
    updateRange(root);
}

void Insert(Node *&root, Node *x, int &i)
{
    if (i < 0 || (root != np && i > root->sz)) return;
    Node *L, *R;
    Split(root, L, R, i);
    Merge(root, L, x);
    Merge(root, root, R);
}

void Delete(Node *&root, int &i)
{
    if (root == np || i < 0 || i >= root->sz) return;
    Node *t1, *t2, *t3;
    Split(root, t1, t2, i);
    Split(t2, t2, t3, 1);
    Merge(root, t1, t3);
    delete t2;
}

void Reverse(Node *&root, int &L, int &R)
{
    if (root == np) return;
    Node *t1, *t2, *t3;
    Split(root, t1, t3, R+1);
    Split(t1, t1, t2, L);
    if (t2 != np) t2->rev ^= 1;
    Merge(t2, t2, t3);
    Merge(root, t1, t2);
}

void circularShift(Node *&root, int &L, int &R, int &t)
{
    if (root == np) return;
    t %= (R-L+1);
    if (!t || L==R) return;
    Node *t1, *t2, *t3, *t4;
    Split(root, t1, t4, R+1);
    Split(t1, t1, t2, L);
    Split(t2, t2, t3, R-L+1-t);
    Merge(t2, t2, t4);
    Merge(t1, t1, t3);
    Merge(root, t1, t2);
}

void Add(Node *&root, int &L, int &R, int &v)
{
    if (root == np) return;
    Node *t1, *t2, *t3;
    Split(root, t1, t3, R+1);
    Split(t1, t1, t2, L);
    if (t2 != np) t2->lazy += v;
    Merge(t2, t2, t3);
    Merge(root, t1, t2);
}

int sumQuery(Node *&root, int &L, int &R)
{
    if (root == np) return 0;
    Node *t1, *t2, *t3;
    Split(root, t1, t3, R+1);
    Split(t1, t1, t2, L);
    int ans = 0;
    if (t2 != np) ans = t2->sum;
    Merge(t2, t2, t3);
    Merge(root, t1, t2);
    return ans;
}

int minQuery(Node *&root, int &L, int &R)
{
    if (root == np) return INF;
    Node *t1, *t2, *t3;
    Split(root, t1, t3, R+1);
    Split(t1, t1, t2, L);
    int ans = INF;
    if (t2 != np) ans = t2->minv;
    Merge(t2, t2, t3);
    Merge(root, t1, t2);
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);


    int q;
    cin >> q;
    srand(time(0));
    Node *root = np;

    while (q)
    {
        string c;
        cin >> c;

        if (c[0] == 'i')
        {
            int x, i;
            cin >> x >> i;
            Insert(root, new Node(x), i);
        }
        else if (c[0] == 'm' && c[1] == 'e')
        {
            int x;
            cin >> x;
            Merge(root, root, new Node(x));
        }
        else if (c[0] == 'd')
        {
            int i;
            cin >> i;
            Delete(root, i);
        }
        else if (c[0] == 'r')
        {
            int L, R;
            cin >> L >> R;
            Reverse(root, L, R);
        }
        else if (c[0] == 'c')
        {
            int L, R, t;
            cin >> L >> R >> t;
            circularShift(root, L, R, t);
        }
        else if (c[0] == 'a')
        {
            int L, R, v;
            cin >> L >> R >> v;
            Add(root, L, R, v);
        }
        else if (c[0] == 's')
        {
            int L, R;
            cin >> L >> R;
            cout << sumQuery(root, L, R) << '\n';
        }
        else if (c[0] == 'm')
        {
            int L, R;
            cin >> L >> R;
            cout << minQuery(root, L, R) << '\n';
        }

        inOrder(root,root);
        --q;
    }

    deleteTreap(root);
    root = np;


    return 0;
}
