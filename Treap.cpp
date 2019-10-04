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
    int key, pr;
    Node *c[2];

    Node(int k = 0, int p = randNum())
    {
        key = k;
        pr = p;
        c[0] = c[1] = np;
    }
};

void deleteTreap(Node *x)
{
    if (x == np) return;
    deleteTreap(x->c[0]);
    deleteTreap(x->c[1]);
    delete x;
}

void inOrder(Node *&root, Node *x)
{
    if (x == np) return;
    inOrder(root, x->c[0]);
    cout << x->key << ' ';
    inOrder(root, x->c[1]);
    if (x == root) cout << '\n';
}

void Split(Node *root, int key, Node *&L, Node *&R)
{
    if (root == np)
        L = R = np;
    else if (key < root->key)
        Split(root->c[0], key, L, root->c[0]), R = root;
    else
        Split(root->c[1], key, root->c[1], R), L = root;
}

void Merge(Node *&root, Node *L, Node *R)
{
    if (L == np || R == np)
        root = (L != np) ? L:R;
    else if (L->pr > R->pr)
        Merge(L->c[1], L->c[1], R), root = L;
    else
        Merge(R->c[0], L, R->c[0]), root = R;
}

void Insert(Node *&root, Node *x)
{
    if (root == np)
    {
        root = x;
        return;
    }

    if (x->pr > root->pr)
    {
        Split(root, x->key, x->c[0], x->c[1]);
        root = x;
    }
    else Insert(root->c[x->key > root->key], x);
}

void Delete(Node *&root, int key)
{
    if (root == np) return;

    if (key == root->key)
        Merge(root, root->c[0], root->c[1]);
    else
        Delete(root->c[key > root->key], key);
}

Node* Union(Node *A, Node *B)
{
    if (A == np || B == np) return (A != np) ? A:B;
    if (B->pr > A->pr) swap(A,B);
    Node *L = np, *R = np;
    Split(B, A->key, L, R);
    A->c[0] = Union(A->c[0], L);
    A->c[1] = Union(A->c[1], R);
    return A;
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
        char c;
        int x;
        cin >> c >> x;

        if (c == 'i')
            Insert(root, new Node(x));
        else if (c == 'd')
            Delete(root, x);

        inOrder(root,root);
        --q;
    }

    deleteTreap(root);
    root = np;






    return 0;
}
