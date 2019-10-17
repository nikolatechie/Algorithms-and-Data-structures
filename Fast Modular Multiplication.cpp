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


llint multiply(llint a, llint b, llint m)
{
    // if b is even, a*b = 2*(a*(b/2))
    // else, a*b = a + (a*(b-1))
    llint res = 0;

    a %= m;

    while (b)
    {
        if (b&1)
            res = (res + a) % m;

        a = (a<<1) % m;

        b >>= 1;
    }

    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    llint a, b, m;
    cin >> a >> b >> m;
    cout << multiply(a, b, m) << '\n';



    return 0;
}
