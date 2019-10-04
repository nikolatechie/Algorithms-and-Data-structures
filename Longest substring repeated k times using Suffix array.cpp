#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;

using ci = const int;
using ld = long double;
using llint = long long;
using ullint = unsigned long long;
using pii = pair <int,int>;
using pcc = pair <char,char>;
using pss = pair <string,string>;
using vi = vector <int>;
using vb = vector <bool>;
using vii = vi::iterator;

#define INF (1<<30)
#define MOD 1000000007
#define mp make_pair
#define mt make_tuple
#define all(c) c.begin(), c.end()
#define ms(name,val) memset(name, val, sizeof name)
#define np nullptr


ci NMAX = 100001;
int n, len;
string s;
int sa[NMAX], rnk[NMAX], tmp[NMAX], lcp[NMAX];

bool cmp(int i, int j)
{
    if (rnk[i] != rnk[j]) return (rnk[i] < rnk[j]);
    i += len, j += len;
    return (i < n && j < n) ? (rnk[i] < rnk[j]): (i > j);
}

void BuildSA()
{
    n = s.size();

    for (int i = 0; i < n; ++i)
        sa[i] = i, rnk[i] = s[i];

    for (len = 1;; len <<= 1)
    {
        sort(sa, sa+n, cmp);

        for (int i = 0; i < n-1; ++i)
            tmp[i+1] = tmp[i] + cmp(sa[i], sa[i+1]);

        for (int i = 0; i < n; ++i)
            rnk[sa[i]] = tmp[i];

        if (tmp[n-1] == n-1) break;
    }
}

void BuildLCP()
{
    for (int i = 0, k = 0; i < n; ++i)
    {
        if (rnk[i] != n-1)
        {
            for (int j = sa[rnk[i]+1]; max(i,j)+k < n && s[i+k]==s[j+k]; ++k);
            lcp[rnk[i]] = k;
            if (k) --k;
        }
    }
}

// longest substring that is repeated k times
int lenOfSubstring(int &k)
{
    if (k == 1) return n;

    int ans = 0;
    multiset <int> M;

    for (int i = 0; i < n; ++i)
    {
        if (i < k-1)
            M.insert(lcp[i]);
        else
        {
            ans = max(ans, *M.begin());
            M.erase(M.find(lcp[i-k+1]));
            M.insert(lcp[i]);
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    int k;
    cin >> k >> n >> s;
    BuildSA();
    BuildLCP();

    cout << lenOfSubstring(k) << '\n';



    return 0;
}
