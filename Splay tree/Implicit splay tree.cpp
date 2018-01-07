#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned short usint;
typedef unsigned uint;
typedef long lint;
typedef short sint;
typedef long double ld;
typedef unsigned long ulint;
typedef unsigned long long ullint;
typedef long long llint;
 
#define INF ullint(1e9)
#define MOD 1000000007
#define mp make_pair
#define mt make_tuple
#define pii pair <int,int>
#define pib pair <int,bool>
#define pll pair <long,long>
#define pcc pair <char,char>
#define pui pair <uint,uint>
#define pul pair <ulint,ulint>
#define pff pair <float,float>
#define p2ll pair <llint,llint>
#define pss pair <string,string>
#define p2ull pair <ullint,ullint>
// inline funkcije
 
 
 
const int N_MAX = 1e5;
int A[N_MAX];
 
struct Node
{
    int val, sum, sz;
    bool tag;
    Node *c[2], *p;
 
    Node()
    {
        val = sum = sz = tag = 0;
        // pointers are still undefined
    }
};
 
Node *root, *nil;
 
void treeInit()
{
    nil = new Node;
    nil->c[0] = nil->c[1] = nil->p = nil;
    root = nil;
}
 
void pushDown(Node *x)
{
    if (x == nil) return;
 
    if (x->tag)
    {
        x->tag = 0;
        swap(x->c[0], x->c[1]);
        if (x->c[0] != nil) x->c[0]->tag ^= 1;
        if (x->c[1] != nil) x->c[1]->tag ^= 1;
    }
}
 
void inOrder(Node *x)
{
    if (x == nil) return;
    pushDown(x);
    inOrder(x->c[0]);
    cout << x->val << ' ';
    inOrder(x->c[1]);
    if (x == root) cout << '\n';
}
 
void inRevOrder(Node *x)
{
    if (x == nil) return;
    pushDown(x);
    inRevOrder(x->c[1]);
    cout << x->val << ' ';
    inRevOrder(x->c[0]);
    if (x == root) cout << '\n';
}
 
void deleteST(Node *x)
{
    if (x == nil) return;
    deleteST(x->c[0]);
    deleteST(x->c[1]);
    delete x;
}
 
void setLink(Node *x, Node *y, bool d)
{
    // we aren't changing any nil's variables
    if (x != nil) x->c[d] = y;
    if (y != nil) y->p = x;
}
 
void update(Node *x)
{
    if (x == nil) return;
    x->sz = x->c[0]->sz + x->c[1]->sz + 1;
    x->sum = x->c[0]->sum + x->c[1]->sum + x->val;
    // if x's children are nil, their sz/sum is equal to 0
}
 
Node* buildTree(int L, int R)
{
    // building the most balanced Splay Tree
    if (L > R) return nil;
 
    int M = (L+R)>>1;
    Node *x = new Node;
    x->val = A[M];
    x->p = nil; // for root node
    setLink(x, buildTree(L,M-1), 0);
    setLink(x, buildTree(M+1,R), 1);
    update(x);
    return x;
}
 
inline bool getDir(Node *x, Node *y)
{
    return (x->c[0] == y) ? 0:1;
}
 
void rotate(Node *x, bool &d)
{
    if (x == nil) return;
 
    Node *y = x->c[d];
    Node *z = x->p;
    setLink(x, y->c[d^1], d);
    setLink(y, x, d^1);
    setLink(z, y, getDir(z,x));
    update(x);
    update(y);
}
 
void splay(Node *x)
{
    if (x == nil) return;
 
    while (x->p != nil)
    {
        Node *y = x->p;
        Node *z = y->p;
        bool dy = getDir(y,x);
        bool dz = getDir(z,y);
 
        if (z == nil)
            rotate(y,dy);
        else if (dy == dz)
            rotate(z,dz), rotate(y,dy);
        else
            rotate(y,dy), rotate(z,dz);
    }
}
 
Node* kth(Node *x, int k)
{
    if (x == nil) return nullptr;
 
    while (pushDown(x), x->c[0]->sz != k)
    {
        if (k < x->c[0]->sz)
            x = x->c[0];
        else
            k -= (x->c[0]->sz+1), x = x->c[1];
    }
 
    splay(x);
    return x;
}
 
Node* Merge(Node *x, Node *y)
{
    if (x == nil) return y;
 
    x = kth(x, x->sz-1);
    setLink(x,y,1);
    update(x);
    return x;
}
 
void Split(Node *x, int i, Node *&n1, Node *&n2)
{
    if (x == nil)
    {
        n1 = n2 = nil;
        return;
    }
 
    if (i < 0)
        n1 = nil, n2 = x;
    else
    {
        n1 = kth(x, i);
        n2 = n1->c[1];
        n1->c[1] = n2->p = nil;
        update(n1);
    }
}
 
void Insert(int &v)
{
    if (root == nil)
    {
        root = new Node;
        root->val = v;
        root->c[0] = root->c[1] = root->p = nil;
        update(root);
    }
    else
    {
        root = kth(root, root->sz-1);
        Node *x = new Node;
        x->val = v;
        x->c[0] = x->c[1] = nil;
        setLink(root, x, 1);
        update(x);
        update(root);
    }
}
 
void Delete(int &k)
{
    if (root == nil) return;
 
    root = kth(root,k);
    Node *L = root->c[0];
    Node *R = root->c[1];
    L->p = R->p = nil;
    delete root;
 
    if (L == nil)
    {
        root = R;
        return;
    }
 
    root = L;
    root = kth(root, root->sz-1);
    setLink(root, R, 1);
    update(root);
}
 
void Reverse(int &L, int &R)
{
    Node *n1, *n2, *n3;
    Split(root, R, n1, n3);
    Split(n1, L-1, n1, n2);
    n2->tag ^= 1;
    root = Merge(Merge(n1,n2),n3);
}
 
void Set(int &i, int &x)
{
    root = kth(root, i);
    root->val = x;
    update(root);
}
 
int Query(int &L, int &R)
{
    Node *n1, *n2, *n3;
    Split(root, R, n1, n3);
    Split(n1, L-1, n1, n2);
    int ans = n2->sum;
    root = Merge(Merge(n1,n2),n3);
    return ans;
}
 
void printNil()
{
    cout << nil->val << ' ' << nil->sum << ' ' << nil->sz << ' ' << nil->tag << '\n';
}
 
int main()
{
    ios_base::sync_with_stdio(0);
 
 
    int n;
    cin >> n;
 
    for (int t1 = 0; t1 < n; ++t1)
        cin >> A[t1];
 
    treeInit();
    root = buildTree(0, n-1);
    inOrder(root);
    inRevOrder(root);
    cout << '\n';
 
    int q;
    cin >> q;
 
    while (q)
    {
        char type;
        cin >> type;
 
        if (type == '1')
            inOrder(root);
        else if (type == '2')
            inRevOrder(root);
        else if (type == 'N')
            printNil();
        else
        {
            int x;
            cin >> x;
 
            if (type == 'I')
                Insert(x);
            else if (type == 'D')
                Delete(x);
            else
            {
                int y;
                cin >> y;
 
                if (type == 'R')
                    Reverse(x,y);
                else if (type == 'S')
                    Set(x,y);
                else if (type == 'Q')
                    cout << Query(x,y) << '\n';
            }
        }
 
        --q;
    }
 
    deleteST(root);
    delete nil;
    root = nil = nullptr;
 
 
    return 0;
}
