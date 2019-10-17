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


int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    string s;
    cin >> s;
    int n = s.size();
    vector <vi> DP(n, vi(n, 0));

    for (int len = 1; len < n; ++len)
    {
        for (int i = 0; i+len < n; ++i)
        {
            int j = i+len;

            if (s[i] == s[j])
                DP[i][j] = DP[i+1][j-1];
            else
                DP[i][j] = 1 + min(DP[i][j-1], DP[i+1][j]);
        }
    }

    cout << DP[0][n-1] << '\n';


    return 0;
}
