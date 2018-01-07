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



struct Node
{
    int val, h;
    Node *left, *right;

    Node()
    {
        val = h = 0;
        left = right = nullptr;
    }
};

struct AVL
{
    Node *root;

    AVL()
    {
        root = nullptr;
    }

    void deleteAVL(Node *temp)
    {
        if (temp == nullptr) return;
        deleteAVL(temp->left);
        deleteAVL(temp->right);
        delete temp;
    }

    ~AVL()
    {
        deleteAVL(root);
        root = nullptr;
    }

    void inOrder(Node *temp)
    {
        if (temp == nullptr) return;
        inOrder(temp->left);
        cout << temp->val << ' ';
        inOrder(temp->right);
        if (temp == root) cout << '\n';
    }

    void levelOrder()
    {
        queue <pair <Node*,int>> Q;
        Q.push({root,0});
        int lvl = 0;

        while (!Q.empty())
        {
            Node *n = Q.front().first;
            int l = Q.front().second;
            Q.pop();
            if (n == nullptr) break;

            if (l != lvl)
            {
                lvl = l;
                cout << '\n';
            }

            cout << n->val << ' ';

            if (n->left != nullptr) Q.push({n->left,l+1});
            if (n->right != nullptr) Q.push({n->right,l+1});
        }

        cout << '\n';
    }

    int height(Node *temp)
    {
        if (temp == nullptr) return -1;
        return temp->h;
    }

    int getBalance(Node *temp)
    {
        return height(temp->left)-height(temp->right);
    }

    Node* rightRotate(Node *x)
    {
        Node *y = x->left;
        Node *z = y->right;

        x->left = z;
        y->right = x;

        x->h = 1 + max(height(x->left),height(x->right));
        y->h = 1 + max(height(y->left),height(y->right));

        return y;
    }

    Node* leftRotate(Node *y)
    {
        Node *x = y->right;
        Node *z = x->left;

        y->right = z;
        x->left = y;

        y->h = 1 + max(height(y->left),height(y->right));
        x->h = 1 + max(height(x->left),height(x->right));

        return x;
    }

    Node* newNode(int *x)
    {
        Node *n = new Node;
        n->val = *x;
        return n;
    }

    void Insert(int x)
    {
        root = Insert(root,x);
    }

    Node* Insert(Node *temp, int &x)
    {
        if (temp == nullptr) return newNode(&x);

        if (x < temp->val)
            temp->left = Insert(temp->left,x);
        else if (x > temp->val)
            temp->right = Insert(temp->right,x);
        else
            return temp;

        temp->h = 1 + max(height(temp->left),height(temp->right));
        int balance = getBalance(temp);

        // LL
        if (balance > 1 && x < temp->left->val)
            return rightRotate(temp);

        // RR
        if (balance < -1 && x > temp->right->val)
            return leftRotate(temp);

        // LR
        if (balance > 1 && x > temp->left->val)
        {
            temp->left = leftRotate(temp->left);
            return rightRotate(temp);
        }

        // RL
        if (balance < -1 && x < temp->right->val)
        {
            temp->right = rightRotate(temp->right);
            return leftRotate(temp);
        }

        return temp; // no rotations needed
    }

    bool Search(int x)
    {
        Node *temp = root;

        while (temp != nullptr)
        {
            if (temp->val == x) return 1;

            if (x < temp->val)
                temp = temp->left;
            else
                temp = temp->right;
        }

        return 0;
    }

    Node* leftmost(Node *temp)
    {
        while (temp->left != nullptr) temp = temp->left;
        return temp;
    }

    void Delete(int x)
    {
        root = Delete(root,x);
    }

    Node* Delete(Node *temp, int x)
    {
        if (temp == nullptr) return temp;

        if (x < temp->val)
            temp->left = Delete(temp->left,x);
        else if (x > temp->val)
            temp->right = Delete(temp->right,x);
        else
        {
            if (temp->left == nullptr || temp->right == nullptr)
            {
                // 0 or 1 child
                Node *c = (temp->left == nullptr) ? temp->right:temp->left;

                if (c == nullptr)
                {
                    delete temp;
                    return nullptr;
                }
                else
                {
                    delete temp;
                    return c;
                }
            }
            else
            {
                // 2 children
                Node *l = leftmost(temp->right);
                temp->val = l->val;
                temp->right = Delete(temp->right,l->val);
            }
        }

        temp->h = 1 + max(height(temp->left),height(temp->right));
        int balance = getBalance(temp);

        // LL
        if (balance > 1 && getBalance(temp->left) >= 0)
            return rightRotate(temp);

        // RR
        if (balance < -1 && getBalance(temp->right) <= 0)
            return leftRotate(temp);

        // LR
        if (balance > 1 && getBalance(temp->left) < 0)
        {
            temp->left = leftRotate(temp->left);
            return rightRotate(temp);
        }

        // RL
        if (balance < -1 && getBalance(temp->right) > 0)
        {
            temp->right = rightRotate(temp->right);
            return leftRotate(temp);
        }

        return temp;
    }

    Node* createFromArray(vector <int> &ans, int L, int R, Node *temp)
    {
        if (L > R) return nullptr;

        int M = (L+R)>>1;
        temp = newNode(&ans[M]);
        temp->left = createFromArray(ans,L,M-1,temp->left);
        temp->right = createFromArray(ans,M+1,R,temp->right);
        return temp;
    }

    void getInorder(Node *temp, vector<int> &v)
    {
        if (temp == nullptr) return;
        getInorder(temp->left,v);
        v.push_back(temp->val);
        getInorder(temp->right,v);
    }

    void mergeByTraversing(AVL &t2)
    {
        vector <int> v1, v2, ans;
        getInorder(root,v1);
        t2.getInorder(t2.root,v2);
        t2.deleteAVL(t2.root);
        t2.root = nullptr;
        int a = 0, b = 0, prev = INF;

        while (a < v1.size() && b < v2.size())
        {
            if (v1[a] <= v2[b])
            {
                if (v1[a] != prev)
                {
                    ans.push_back(v1[a]);
                    prev = ans.back();
                }
                ++a;
            }
            else
            {
                if (v2[b] != prev)
                {
                    ans.push_back(v2[b]);
                    prev = ans.back();
                }
                ++b;
            }
        }

        while (a < v1.size())
        {
            if (v1[a] != prev)
            {
                ans.push_back(v1[a]);
                prev = ans.back();
            }
            ++a;
        }

        while (b < v2.size())
        {
            if (v2[b] != prev)
            {
                ans.push_back(v2[b]);
                prev = ans.back();
            }
            ++b;
        }

        deleteAVL(root);
        root = nullptr;
        root = createFromArray(ans, 0, ans.size()-1, root);
    }

    void Merge(AVL &t2)
    {
        // Merging 2 AVL trees by assuming that
        // every element in the first tree is
        // smaller than every element in the second tree
        if (t2.root == nullptr) return;
        Node *newRoot = leftmost(t2.root);
        int newRootVal = newRoot->val;
        newRoot = newNode(&newRootVal);
        newRoot->left = root;
        newRoot->right = t2.root;
        t2.root = nullptr;
        root = newRoot;
        root->right = Delete(root->right,newRootVal);

        root->h = 1 + max(height(root->left),height(root->right));
        int balance = getBalance(root);

        // LL
        if (balance > 1 && getBalance(root->left) >= 0)
            root = rightRotate(root);

        // RR
        if (balance < -1 && getBalance(root->right) <= 0)
            root = leftRotate(root);

        // LR
        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            root = rightRotate(root);
        }

        // RL
        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            root = leftRotate(root);
        }
    }

    pair <Node*,Node*> Split(int x)
    {
        if (root == nullptr) return {nullptr,nullptr};
        vector <int> v, manji, veci;
        getInorder(root,v);

        for (int t1 = 0; t1 < v.size(); ++t1)
        {
            if (v[t1] < x)
                manji.push_back(v[t1]);
            else
                veci.push_back(v[t1]);
        }

        Node *prvi = createFromArray(manji,0,manji.size()-1,prvi);
        Node *drugi = createFromArray(veci,0,veci.size()-1,drugi);
        return {prvi,drugi};
    }
};

int main()
{
    ios_base::sync_with_stdio(0);


    AVL t1;
    t1.Insert(14);
    t1.Insert(10);
    t1.Insert(5);
    t1.Insert(1);
    t1.Insert(2);
    //t1.levelOrder();

    AVL t2;
    t2.Insert(100);
    t2.Insert(50);
    t2.Insert(150);
    t2.Insert(20);
    t2.Insert(200);
    //t2.levelOrder();

    t1.Merge(t2);
    //t1.inOrder(t1.root);
    //t1.levelOrder();
    //t2.inOrder(t2.root); // empty tree
    //t2.levelOrder(); // empty tree

    pair <Node*,Node*> pr = t1.Split(120);
    t1.root = pr.first;
    t2.root = pr.second;
    t1.inOrder(t1.root);
    t1.levelOrder();
    t2.inOrder(t2.root);
    t2.levelOrder();





    return 0;
}
