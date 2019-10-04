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


int n, m;
string t, p;
llint M = 1e9+9, P = 31;

llint getHashVal()
{
    llint p_pow = 1;
    llint hashVal = 0;

    for (int t1 = 0; t1 < m; ++t1)
    {
        hashVal = (hashVal + (p[t1]-'a'+1)*p_pow) % M;
        p_pow = (p_pow * P) % M;
    }

    return hashVal;
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    cin >> t >> p;
    n = t.size(), m = p.size();
    llint phash = getHashVal();
    llint whash = 0, p_pow = 1;

    for (int t1 = 0; t1 < m; ++t1)
    {
        whash = (whash + (t[t1]-'a'+1)*p_pow) % M;
        if (t1 < m-1) p_pow = (p_pow * P) % M;
    }

    if (whash==phash) cout << 0 << '\n';

    for (int t1 = m; t1 < n; ++t1)
    {
        whash = (whash - (t[t1-m]-'a'+1)) % M;
        whash = (whash / P) % M;
        whash = (whash + (t[t1]-'a'+1)*p_pow) % M;
        if (whash==phash) cout << t1-m+1 << '\n';
    }


    return 0;
}
