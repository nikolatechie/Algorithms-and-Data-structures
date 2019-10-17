// Fast Fibonacci for very large numbers in O(log n)
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
#define mt make_tuple
#define all(c) c.begin(), c.end()
#define ms(name,val) memset(name, val, sizeof name)
#define np nullptr


llint m = 1e9 + 9;
map <llint,llint> F;

llint f(llint n)
{
    if (F.find(n) != F.end()) return F[n];
    llint k = (n>>1);

    if (n&1) // e.g. n = 5
        return F[n] = (f(k-1)*f(k) + f(k)*f(k+1)) % m; // 1223
    else // e.g. n = 4
        return F[n] = (f(k-1)*f(k-1) + f(k)*f(k)) % m; // 1122
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    int q;
    cin >> q;
    F[0] = F[1] = 1;

    while (q)
    {
        --q;
        llint n;
        cin >> n;
        cout << f(n) << '\n';
    }


    return 0;
}
