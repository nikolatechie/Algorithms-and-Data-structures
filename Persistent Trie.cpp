// Solution of a Codechef problem - XRQRS
#include <bits/stdc++.h>
using namespace std;

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


const int M = 5e5+5;

struct Node
{
    int cnt = 0;
    Node *c[2] = {np,np};
};

vector <Node*> nodes;

void delTrie()
{
    for (int t1 = 0; t1 < nodes.size(); ++t1)
        delete nodes[t1];
}

int len;
Node *root[M];

Node* Insert(Node *old, int &x)
{
    Node *n = new Node;
    nodes.push_back(n);
    n->cnt = old->cnt+1;
    Node *temp = n;

    for (int lvl = 19; lvl > -1; --lvl)
    {
        bool b = x&(1<<lvl);
        temp->c[b^1] = old->c[b^1];
        temp->c[b] = new Node;
        nodes.push_back(temp->c[b]);
        temp = temp->c[b];
        old = old->c[b];
        temp->cnt = old->cnt+1;
    }

    return n;
}

int XOR_max(int &L, int &R, int &x)
{
    // Find a number 'ans' in range [L,R] such
    // that XOR of 'x' and 'ans' is max
    Node *rootL = root[L-1];
    Node *rootR = root[R];
    int ans = 0;

    for (int lvl = 19; lvl > -1; --lvl)
    {
        bool b = x&(1<<lvl);
        bool hasLeft = (rootL->c[0] != rootR->c[0]);
        bool hasRight = (rootL->c[1] != rootR->c[1]);

        if ((b && hasLeft) || (!b && hasRight))
        {
            if (!b) ans |= (1<<lvl);
            rootL = rootL->c[b^1];
            rootR = rootR->c[b^1];
        }
        else
        {
            if (b) ans |= (1<<lvl);
            rootL = rootL->c[b];
            rootR = rootR->c[b];
        }
    }

    return ans;
}

int LessThanOrEqualTo(int &L, int &R, int &x)
{
    Node *rootL = root[L-1];
    Node *rootR = root[R];
    int ans = 0;

    for (int lvl = 19; lvl > -1; --lvl)
    {
        bool b = x&(1<<lvl);
        if (b) ans += (rootR->c[0]->cnt - rootL->c[0]->cnt);
        rootL = rootL->c[b];
        rootR = rootR->c[b];
    }

    return ans + (rootR->cnt - rootL->cnt);
}

int Kth(int &L, int &R, int &k)
{
    Node *rootL = root[L-1];
    Node *rootR = root[R];
    int ans = 0;

    for (int lvl = 19; lvl > -1; --lvl)
    {
        int cntLeft = rootR->c[0]->cnt - rootL->c[0]->cnt;

        if (k <= cntLeft)
        {
            rootL = rootL->c[0];
            rootR = rootR->c[0];
        }
        else
        {
            k -= cntLeft;
            ans |= (1<<lvl);
            rootL = rootL->c[1];
            rootR = rootR->c[1];
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);


    int q;
    cin >> q;
    len = 1;
    root[0] = new Node;
    root[0]->c[0] = root[0]->c[1] = root[0];

    while (q)
    {
        --q;
        int type;
        cin >> type;

        if (!type)
        {
            int x;
            cin >> x;
            root[len] = Insert(root[len-1], x);
            ++len;
        }
        else if (type == 1)
        {
            int L, R, x;
            cin >> L >> R >> x;
            cout << XOR_max(L,R,x) << '\n';
        }
        else if (type == 2)
        {
            int k;
            cin >> k;
            len -= k;
        }
        else if (type == 3)
        {
            int L, R, x;
            cin >> L >> R >> x;
            cout << LessThanOrEqualTo(L,R,x) << '\n';
        }
        else
        {
            int L, R, k;
            cin >> L >> R >> k;
            cout << Kth(L,R,k) << '\n';
        }
    }

    delTrie(), delete root[0];



    return 0;
}
