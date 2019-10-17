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
vi a, b;
vector <vi> DP;

void longestCommonSubsequence()
{
    DP.resize(n+1);

    for (int t1 = 0; t1 <= n; ++t1)
        DP[t1].resize(m+1);

    for (int t1 = 1; t1 <= n; ++t1)
    {
        for (int t2 = 1; t2 <= m; ++t2)
        {
            DP[t1][t2] = max(DP[t1-1][t2], DP[t1][t2-1]);
            
            if (a[t1-1] == b[t2-1])
                DP[t1][t2] = max(DP[t1][t2], (1 + DP[t1-1][t2-1]));
        }
    }

    vi ans;
    int x = n, y = m;

    while (x && y)
    {
        if (a[x-1] == b[y-1])
        {
            ans.push_back(a[x-1]);
            --x, --y;
        }
        else
        {
            if (DP[x][y-1] > DP[x-1][y])
                --y;
            else
                --x;
        }
    }

    for (int t1 = ans.size()-1; t1 >= 0; --t1)
        cout << ans[t1] << ' ';

    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    a.resize(n);
    b.resize(m);

    for (int t1 = 0; t1 < n; ++t1)
        cin >> a[t1];

    for (int t1 = 0; t1 < m; ++t1)
        cin >> b[t1];

    longestCommonSubsequence();

    return 0;
}
