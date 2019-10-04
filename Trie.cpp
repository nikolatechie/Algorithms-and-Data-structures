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


struct Node
{
    char key;
    bool end;
    map <char,Node*> c;

    Node(char k = '$', bool e = 0)
    {
        key = k;
        this->end = e;
    }
};

vector <Node*> nodes; // helps to delete a Trie
inline void deleteTrie()
{
    for (int t1 = 0; t1 < nodes.size(); ++t1) delete nodes[t1];
}

void Insert(Node *root, string &s)
{
    map <char,Node*> *temp = &root->c;

    for (int t1 = 0; t1 < s.size(); ++t1)
    {
        map <char,Node*>::iterator it = temp->find(s[t1]);

        if (it == temp->end())
        {
            Node *n = new Node(s[t1]);
            nodes.push_back(n);
            (*temp)[s[t1]] = n;
            temp = &n->c;
            root = n;
        }
        else
            temp = &it->second->c, root = it->second;
    }

    root->end = 1;
}

bool prefixSearch(Node *&x, string &s)
{
    map <char,Node*> *temp = &x->c;

    for (int t1 = 0; t1 < s.size(); ++t1)
    {
        map <char,Node*>::iterator it = temp->find(s[t1]);
        if (it == temp->end()) return 0;
        temp = &it->second->c;
    }

    return 1;
}

bool stringSearch(Node *x, string &s)
{
    map <char,Node*> *temp = &x->c;

    for (int t1 = 0; t1 < s.size(); ++t1)
    {
        map <char,Node*>::iterator it = temp->find(s[t1]);
        if (it == temp->end()) return 0;
        temp = &it->second->c, x = it->second;
    }

    return (x->end);
}

bool Delete(Node *x, string &s, int lvl, int len)
{
    if (x != np)
    {
        if (lvl == len) // base case
        {
            if (x->end)
            {
                x->end = 0; // unmark leaf node
                return (x->c.empty()); // delete if it's empty
            }
        }
        else // recursive case
        {
            char index = s[lvl];
            if (x->c.find(index) != x->c.end() && Delete(x->c[index], s, lvl+1, len))
            {
                x->c.erase(index); // unlink last marked node
                return (x->c.empty() && !x->end);
                // recursively climb up and delete eligible nodes
            }
        }
    }

    return 0;
}

inline void Delete(Node *&x, string &s)
{
    if (!s.empty()) Delete(x, s, 0, s.size());
}

bool Print(Node *&x, map <char,Node*> *temp, string s)
{
    if (x == np) return 1;

    for (auto &it: x->c)
    {
        s += it.first;
        bool b = Print(it.second, &it.second->c, s);
        if (b) cout << s << '\n';
        s.pop_back();
    }

    return (x->end);
}

int main()
{
    ios_base::sync_with_stdio(0);


    int n;
    cin >> n;
    Node *root = new Node;

    for (int t1 = 0; t1 < n; ++t1)
    {
        string s;
        cin >> s;
        Insert(root,s);
    }

    cout << '\n', Print(root, &root->c, ""), cout << '\n';
    int q;
    cin >> q;

    while (q)
    {
        --q;
        int opt;
        string s;
        cin >> opt >> s;

        if (!opt)
            Insert(root,s);
        else if (opt == 1)
            cout << prefixSearch(root,s) << '\n';
        else if (opt == 2)
            cout << stringSearch(root,s) << '\n';
        else if (opt == 3)
            Delete(root, s, 0, s.size());
        else
            Print(root, &root->c, ""), cout << '\n';
    }

    deleteTrie(), delete root, root = np;


    return 0;
}
