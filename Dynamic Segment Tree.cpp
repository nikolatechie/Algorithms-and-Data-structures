Solution to SPOJ problem - HORRIBLE
#include <bits/stdc++.h>
using namespace std;

using llint = long long;
#define np nullptr

struct Node
{
    llint sum, lazy;
    Node *c[2];

    Node()
    {
        sum = lazy = 0;
        c[0] = c[1] = np;
    }
};

void pd(Node *x, int l, int r)
{
    if (x != np && x->lazy)
    {
        if (l != r)
        {
            if (x->c[0] == np) x->c[0] = new Node;
            if (x->c[1] == np) x->c[1] = new Node;
            x->c[0]->lazy += x->lazy;
            x->c[1]->lazy += x->lazy;
        }

        x->sum += (llint(r-l+1)*x->lazy);
        x->lazy = 0;
    }
}

inline llint sum(Node *&x)
{
    return (x == np) ? 0:x->sum;
}

Node* Add(Node *root, int sl, int sr, int &l, int &r, int &v)
{
    pd(root, sl, sr);
    if (sl > r || sr < l) return root;
    if (root == np) root = new Node;

    if (sl >= l && sr <= r)
    {
        root->lazy = v;
        pd(root, sl, sr);
        return root;
    }

    int mid = (sl+sr)>>1;
    root->c[0] = Add(root->c[0], sl, mid, l, r, v);
    root->c[1] = Add(root->c[1], mid+1, sr, l, r, v);
    root->sum = sum(root->c[0]) + sum(root->c[1]);
    return root;
}

llint Query(Node *root, int sl, int sr, int &l, int &r)
{
    if (root == np) return 0;
    if (sl > r || sr < l) return 0;
    pd(root, sl, sr);
    int mid = (sl+sr)>>1;
    if (sl >= l && sr <= r) return root->sum;

    return Query(root->c[0], sl, mid, l, r) +
        Query(root->c[1], mid+1, sr, l, r);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tc;
    cin >> tc;

    while (tc)
    {
        --tc;
        int n, q;
        cin >> n >> q;
        Node *root = np;

        while (q)
        {
            --q;
            bool opt;
            int a, b;
            cin >> opt >> a >> b;
            --a, --b;

            if (opt)
                cout << Query(root, 0, n-1, a, b) << '\n';
            else
            {
                int v;
                cin >> v;
                root = Add(root, 0, n-1, a, b, v);
            }
        }
    }


    return 0;
}
