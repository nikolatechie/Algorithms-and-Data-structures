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


int power(int x, int n, int m)
{
    int res = 1;
    x %= m; // if it is already greater

    while (n)
    {
        if (n&1)
            res = (res*x)%m;

        n >>= 1;
        x = (x*x)%m;
    }

    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    int x, n, m;
    cin >> x >> n >> m;
    cout << power(x, n, m) << '\n';



    return 0;
}
