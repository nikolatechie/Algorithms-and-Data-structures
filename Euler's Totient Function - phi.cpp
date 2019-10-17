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


// returns count of numbers in
// range [1, n] which are relatively
// prime to n -> gcd(t1, n) = 1
int phi(int n)
{
    int res = n;

    // consider all prime factors of n and
    // subtract their multiples from result
    // e.g. n = 10
    // 1 2 3 4 5 6 7 8 9 10
    // we will check 2, and since 10 can be
    // divided by 2, we subtract 2, 4, 6, 8
    // and 10 from the result, that is res/n
    for (int p = 2; p*p <= n; ++p)
    {
        if (n % p == 0)
        {
            res -= (res / p);
            while (n % p == 0) n /= p;
        }
    }

    if (n > 1)
        res -= (res / n);

    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    for (int t1 = 1; t1 <= 10; ++t1)
        cout << phi(t1) << '\n';



    return 0;
}
