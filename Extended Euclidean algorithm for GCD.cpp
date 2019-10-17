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


int gcdExtended(int a, int b, int &x, int &y)
{
    if (!a)
    {
        x = 0, y = 1;
        return b;
    }

    int x1, y1;
    int gcd = gcdExtended(b%a, a, x1, y1);

    y = x1;
    x = (gcd - b*y) / a;
    // x = y1 - x1*(b/a);

    return gcd;
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    int a, b, x, y;
    cin >> a >> b;
    cout << gcdExtended(a, b, x, y) << '\n';
    cout << x << ' ' << y << '\n';



    return 0;
}
