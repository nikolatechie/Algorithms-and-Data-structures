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


int n;
vector <int> et, lvl, fo, st;
vector <vector <int>> graf;

void eulerTour(int node, int l)
{
    et.push_back(node);
    lvl.push_back(l);

    for (int t1 = 0; t1 < graf[node].size(); ++t1)
    {
        int susjed = graf[node][t1];
        eulerTour(susjed,l+1);
        et.push_back(node);
        lvl.push_back(l);
    }
}

void Build(int node, int sl, int sr)
{
    if (sl == sr)
    {
        st[node] = sl;
        return;
    }

    int mid = (sl+sr)>>1, ln = node<<1, rn = ln|1;
    Build(ln, sl, mid);
    Build(rn, mid+1, sr);

    if (lvl[st[ln]] < lvl[st[rn]])
        st[node] = st[ln];
    else
        st[node] = st[rn];
}

int Query(int node, int sl, int sr, int l, int r)
{
    if (r < sl || l > sr) return -1;
    if (sl >= l && sr <= r) return st[node];

    int mid = (sl+sr)>>1, ln = node<<1, rn = ln|1;
    int A = Query(ln, sl, mid, l, r);
    int B = Query(rn, mid+1, sr, l, r);
    if (A == -1) return B;
    if (B == -1) return A;

    if (lvl[A] < lvl[B]) return A;
    return B;
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);


    int TC;
    cin >> TC;

    for (int tc = 1; tc <= TC; ++tc)
    {
        cin >> n;
        graf.clear();
        graf.resize(n+1);
        et.clear();
        lvl.clear();
        st.clear();
        et.push_back(-1);
        lvl.push_back(-1);

        for (int t1 = 1; t1 <= n; ++t1)
        {
            int x;
            cin >> x;

            if (x)
            {
                for (int t2 = 0; t2 < x; ++t2)
                {
                    int c;
                    cin >> c;
                    graf[t1].push_back(c);
                }
            }
        }

        eulerTour(1,1);
        int N = et.size()+10;
        st.resize(N<<2);
        N -= 11;
        fo.assign(n+1,-1);

        for (int t1 = 1; t1 <= N; ++t1)
            if (fo[et[t1]] == -1) fo[et[t1]] = t1;

        Build(1, 1, N);
        int q;
        cin >> q;
        cout << "Case " << tc << ":\n";

        while (q)
        {
            --q;
            int a, b;
            cin >> a >> b;
            a = fo[a];
            b = fo[b];
            if (a > b) swap(a,b);
            int ans = Query(1, 1, N, a, b);
            cout << et[ans] << '\n';
        }
    }



    return 0;
}
