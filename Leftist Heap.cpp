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

#define INF ullint(2e9)
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
#define pllll pair <llint,llint>
#define pss pair <string,string>
#define pullull pair <ullint,ullint>


struct Node
{
    int val, dist; // dist(left) >= dist(right)
    Node *left, *right;

    Node(int &v, int d = 0, Node *l = nullptr, Node *r = nullptr)
    {
        val = v;
        dist = d;
        left = l;
        right = r;
    }
};

struct LeftistHeap
{
    Node *root;

    LeftistHeap()
    {
        root = nullptr;
    }

    void deleteHeap(Node *temp)
    {
        if (temp == nullptr) return;
        deleteHeap(temp->left);
        deleteHeap(temp->right);
        delete temp;
    }

    ~LeftistHeap()
    {
        deleteHeap(root);
        root = nullptr;
    }

    void print()
    {
        queue <pair <Node*,int>> Q;
        Q.push(mp(root,0));
        int td = 0;
        cout << '\n';

        while (!Q.empty())
        {
            Node *temp = Q.front().first;
            int d = Q.front().second;
            Q.pop();
            if (temp == nullptr) break;

            if (d != td)
            {
                td = d;
                cout << '\n';
            }

            cout << temp->val << ' ';

            if (temp->left != nullptr)
                Q.push(mp(temp->left,d+1));

            if (temp->right != nullptr)
                Q.push(mp(temp->right,d+1));
        }

        cout << '\n';
    }

    bool isEmpty()
    {
        return (root == nullptr);
    }

    int getMin()
    {
        if (isEmpty()) return INF;
        return root->val;
    }

    void deleteMin()
    {
        if (isEmpty()) return;
        Node *tempRoot = root;
        root = Merge(root->left,root->right);
        delete tempRoot;
    }

    int extractMin()
    {
        if (isEmpty()) return INF;
        int rootVal = root->val;
        deleteMin();
        return rootVal;
    }

    void swapChildren(Node *x)
    {
        swap(x->left,x->right);
    }

    void Insert(int x)
    {
        root = Merge(root, new Node(x));
    }

    void Merge(LeftistHeap &drugi)
    {
        if (this == &drugi) return;
        root = Merge(root, drugi.root);
        drugi.root = nullptr;
    }

    Node* Merge(Node *a, Node *b)
    {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
        if (b->val < a->val) swap(a,b);

        if (a->left == nullptr)
            a->left = b;
        else
        {
            a->right = Merge(a->right,b);

            if (a->left->dist < a->right->dist)
                swapChildren(a);

            a->dist = 1 + a->right->dist;
        }

        return a;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);


    LeftistHeap h;
    h.Insert(1);
    h.Insert(5);
    h.Insert(7);
    h.Insert(10);
    h.Insert(15);
    cout << h.extractMin() << '\n';
    h.print();




    return 0;
}
