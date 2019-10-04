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


ci MAXN = (1 << 21);
string s;
int n, len;
int sa[MAXN], rnk[MAXN], tmp[MAXN], lcp[MAXN];

bool cmp(int i, int j)
{
    // sorting by rank 
    if (rnk[i] != rnk[j]) return (rnk[i] < rnk[j]);
    i += len, j += len;
    return (i < n && j < n) ? (rnk[i] < rnk[j]): (i > j);
}

void BuildSA(string &s)
{
    n = s.size();

    // assuming indices and ranks
    // of suffixes - initialization
    for (int i = 0; i < n; ++i)
        sa[i] = i, rnk[i] = s[i];

    for (len = 1;; len <<= 1)
    {
        sort(sa, sa+n, cmp);

        // find ranks of given suffixes
        for (int i = 0; i < n-1; ++i)
            tmp[i+1] = tmp[i] + cmp(sa[i], sa[i+1]);

        // set ranks for given suffixes
        for (int i = 0; i < n; ++i)
            rnk[sa[i]] = tmp[i];

        // if all suffixes are sorted, rank of
        // the last suffix will be equal to n-1
        if (tmp[n-1] == n-1) break;
    }
}

// lcp[i] - the longest common prefix of
// suffixes at indices sa[i] and sa[i+1]
void BuildLCP()
{
    for (int i = 0, k = 0; i < n; ++i)
    {
        if (rnk[i] != n-1)
        {
            for (int j = sa[rnk[i]+1]; max(i,j)+k < n && s[i+k] == s[j+k]; ++k);
            lcp[rnk[i]] = k;
            if (k) --k;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    cin >> s;
    BuildSA(s); // O(n log^2 n) complexity

    for (int i = 0; i < s.size(); ++i)
        cout << sa[i] << ' ';

    cout << '\n';
    BuildLCP(); // O(n) complexity

    for (int i = 0; i < s.size(); ++i)
        cout << lcp[i] << ' ';

    cout << '\n';



    return 0;
}
