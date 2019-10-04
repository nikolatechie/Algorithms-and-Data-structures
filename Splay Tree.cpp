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



struct Node
{
	int val;
    Node *left, *right;
 
    Node(int &v, Node *l = nullptr, Node *r = nullptr)
    {
        val = v;
        left = l;
        right = r;
    }
};
 
struct SplayTree
{
    Node *root;
 
    SplayTree()
    {
        root = nullptr;
    }
 
    void deleteST(Node *temp)
    {
        if (temp == nullptr) return;
        deleteST(temp->left);
        deleteST(temp->right);
        delete temp;
    }
 
    ~SplayTree()
    {
        deleteST(root);
        root = nullptr;
    }
 
    Node *leftRotate(Node *y)
    {
        Node *x = y->right;
        Node *T = x->left;
 
        y->right = T;
        x->left = y;
 
        return x;
    }
 
    Node *rightRotate(Node *x)
    {
        Node *y = x->left;
        Node *T = y->right;
 
        x->left = T;
        y->right = x;
 
        return y;
    }
 
    Node* Splay(Node *temp, int &v)
    {
        if (temp == nullptr || temp->val == v) return temp;
 
        if (v < temp->val)
        {
            if (temp->left == nullptr) return temp; // last visited node
 
            if (v < temp->left->val)
            {
                // Zig-Zig - LL case
                temp->left->left = Splay(temp->left->left,v);
                temp = rightRotate(temp);
            }
            else
            {
                // Zig-Zag - LR case
                temp->left->right = Splay(temp->left->right,v);
 
                if (temp->left->right != nullptr)
                    temp->left = leftRotate(temp->left);
            }
 
            if (temp->left != nullptr) temp = rightRotate(temp);
            return temp;
        }
        else
        {
            if (temp->right == nullptr) return temp; // last visited node
 
            if (v < temp->right->val)
            {
                // Zag-Zig - RL case
                temp->right->left = Splay(temp->right->left,v);
 
                if (temp->right->left != nullptr)
                    temp->right = rightRotate(temp->right);
            }
            else
            {
                // Zag-Zag - RR case
                temp->right->right = Splay(temp->right->right,v);
                temp = leftRotate(temp);
            }
 
            if (temp->right != nullptr) temp = leftRotate(temp);
            return temp;
        }
 
        return temp;
    }
 
    Node* Search(int v)
    {
        root = Splay(root,v);
        return root;
    }
 
    void Insert(int v)
    {
        if (root == nullptr)
        {
            root = new Node(v);
            return;
        }
 
        root = Splay(root,v);
        if (root->val == v) return; // already exists
        Node *temp = new Node(v);
 
        if (v < root->val)
        {
            temp->left = root->left;
            root->left = nullptr;
            temp->right = root;
        }
        else
        {
            temp->right = root->right;
            root->right = nullptr;
            temp->left = root;
        }
 
        root = temp;
    }
 
    void Remove(int v)
    {
        if (root == nullptr) return;
        root = Splay(root,v);
        if (root->val != v) return; // value not found
        // Merge(root->left,root->right) - additional solution
 
        Node *T1 = root->left;
        Node *T2 = root->right;
        delete root;
 
        if (T1 == nullptr)
        {
            root = T2;
            return;
        }
 
        T1 = Splay(T1,v);
        T1->right = T2;
        root = T1;
    }
 
    void Merge(SplayTree *ST)
    {
        if (ST->root == nullptr) return;
 
        if (root == nullptr)
        {
            root = ST->root;
            ST->root = nullptr;
            return;
        }
 
        // every element in this tree is
        // smaller than every element in ST
        root = Splay(root,ST->root->val);
        root->right = ST->root;
        ST->root = nullptr;
    }
 
    pair <Node*,Node*> Split(int v)
    {
        if (root == nullptr) return {nullptr,nullptr};
        root = Splay(root,v);
        Node *T1 = nullptr, *T2 = nullptr;
 
        if (v >= root->val)
        {
            T2 = root->right;
            root->right = nullptr;
            T1 = root;
        }
        else
        {
			T1 = root->left;
            root->left = nullptr;
            T2 = root;
        }

        return {T1,T2};
    }
};

int main()
{
    ios_base::sync_with_stdio(0);

    SplayTree st1;



    return 0;
}
