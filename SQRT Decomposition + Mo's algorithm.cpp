// Count of pairs in range [L,R] whose XOR is equal to K - Codeforces problem 617E
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


int n, m, k, sz;

struct Query
{
    int l, r, i;

    bool operator()(const Query &q1, const Query &q2) const
    {
        int q1b = q1.l/sz;
        int q2b = q2.l/sz;
        if (q1b != q2b) return (q1b < q2b);
        return (q1.r < q2.r);
    }
};

vector <int> A, pref;
vector <llint> qans;
vector <Query> Q;
int cnt[1<<20];
llint ans;

void Insert(int v)
{
    ans += cnt[v^k];
    ++cnt[v];
}

void Remove(int v)
{
    --cnt[v];
    ans -= cnt[v^k];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    sz = ceil(sqrt(n));
    A.resize(n);
    pref.resize(n+1);
    qans.resize(m);
    Q.resize(m);

    for (int t1 = 0; t1 < n; ++t1)
        cin >> A[t1];

    for (int t1 = 1; t1 <= n; ++t1)
        pref[t1] = pref[t1-1] ^ A[t1-1];

    for (int t1 = 0; t1 < m; ++t1)
    {
        cin >> Q[t1].l >> Q[t1].r;
        --Q[t1].l;
        Q[t1].i = t1;
    }

    sort(all(Q),Query());
    int lcur = 0, rcur = 0;

    for (int t1 = 0; t1 < m; ++t1)
    {
        int L = Q[t1].l, R = Q[t1].r;

        while (lcur < L) Remove(pref[lcur]), ++lcur;
        while (lcur > L) Insert(pref[lcur-1]), --lcur;
        while (rcur <= R) Insert(pref[rcur]), ++rcur;
        while (rcur > R+1) Remove(pref[rcur-1]), --rcur;

        qans[Q[t1].i] = ans;
    }

    for (auto &it: qans)
        cout << it << '\n';


    return 0;
}
