#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;

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


int n, N, LN;
vector <int> et, depth, fo;
vector <vector <int>> graf, st;

void DFS(int node, int d)
{
    et.push_back(node);
    depth.push_back(d);
    if (fo[node] == -1) fo[node] = et.size()-1;

    for (int t1 = 0; t1 < graf[node].size(); ++t1)
    {
        int susjed = graf[node][t1];
        DFS(susjed,d+1);
        et.push_back(node);
        depth.push_back(d);
    }
}

void preprocess()
{
    N = et.size();
    LN = log2(N)+1;
    st.resize(N);

    for (int t1 = 0; t1 < N; ++t1)
    {
        st[t1].resize(LN);
        st[t1][0] = et[t1];
    }

    for (int t2 = 1; (1<<t2) <= N; ++t2)
    {
        for (int t1 = 0; t1+(1<<t2)-1 < N; ++t1)
        {
            int L = st[t1][t2-1];
            int R = st[t1+(1<<(t2-1))][t2-1];

            if (depth[fo[L]] <= depth[fo[R]])
                st[t1][t2] = L;
            else
                st[t1][t2] = R;
        }
    }
}

int LCA(int &a, int &b)
{
    if (a == b) return a;
    if (fo[a] > fo[b]) swap(a,b);
    int fa = fo[a], fb = fo[b];
    int k = log2(fb-fa+1);

    if (depth[fo[st[fa][k]]] < depth[fo[st[fb-(1<<k)+1][k]]]) return st[fa][k];
    return st[fb-(1<<k)+1][k];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    fo.assign(n,-1);
    graf.resize(n);

    for (int t1 = 0; t1 < n-1; ++t1)
    {
        int a, b;
        cin >> a >> b;
        graf[a].push_back(b); // assuming that (parent[b] == a)
    }

    DFS(0,0);
    preprocess();
    int q;
    cin >> q;

    while (q)
    {
        --q;
        int a, b;
        cin >> a >> b;
        cout << LCA(a,b) << '\n';
    }



    return 0;
}
