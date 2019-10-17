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


const int MX = 10001;
int n, s, w[MX], v[MX], DP[MX];

int solve(int myW, int myV)
{
    if (myW < 0) return -INF;
    if (!myW) return myV;
    if (DP[myW]) return DP[myW];
    int ans = -INF;

    for (int t1 = 0; t1 < n; ++t1)
        ans = max(ans, solve(myW-w[t1], myV+v[t1]));

    return (DP[myW] = ans);
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    cin >> n >> s;

    for (int t1 = 0; t1 < n; ++t1)
        cin >> w[t1] >> v[t1];

    cout << solve(s, 0) << '\n';



    return 0;
}
