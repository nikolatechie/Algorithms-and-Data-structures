// Dynamic programming solution
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


int n, m;
string a, b;
vector <vi> DP;

int longestCommonSubstring()
{
    int ans = 0;
    DP.resize(n);

    for (int t1 = 0; t1 < n; ++t1)
    {
        DP[t1].resize(m);
        DP[t1][0] = (a[t1] == b[0]);
    }

    for (int t2 = 0; t2 < m; ++t2)
        DP[0][t2] = (a[0] == b[t2]);

    for (int t1 = 1; t1 < n; ++t1)
    {
        for (int t2 = 1; t2 < m; ++t2)
        {
            if (a[t1] == b[t2])
            {
                DP[t1][t2] = 1 + DP[t1-1][t2-1];
                ans = max(ans, DP[t1][t2]);
            }
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    cin >> a >> b;
    n = a.size(), m = b.size();
    cout << longestCommonSubstring() << '\n';


    return 0;
}
