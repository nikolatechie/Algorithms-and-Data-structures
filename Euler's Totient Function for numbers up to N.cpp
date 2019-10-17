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


void eulerTotientFunction(ci &n)
{
    vector <llint> phi(n+1);

    for (int t1 = 0; t1 <= n; ++t1)
        phi[t1] = t1;

    for (int p = 2; p <= n; ++p)
    {
        if (phi[p] == p)
        {
            phi[p] = p-1; // for prime numbers

            // phi[n] = n * (1 - 1/p)
            // where p is every prime factor of n

            for (int i = p<<1; i <= n; i += p)
                phi[i] = (phi[i]/p) * (p-1);
        }
    }

    for (int t1 = 1; t1 <= n; ++t1)
        cout << t1 << " ->  " << phi[t1] << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    int n;
    cin >> n;
    eulerTotientFunction(n);


    return 0;
}
