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


struct Point
{
    int x, y;
};

int n;
vector <Point> v;

/*
    Polygon area is half of this matrix's discriminant

    X0       Y0
    X1       Y1
    X2       Y2
        ...
    Xn-1   Yn-1

    (X0*Y1 - X1*Y0)...
*/

double polygonArea()
{
    double area = 0;

    for (int t1 = 0; t1 < n-1; ++t1)
        area += (v[t1].x*v[t1+1].y - v[t1+1].x*v[t1].y);

    area += (v[n-1].x*v[0].y - v[0].x*v[n-1].y);
    return fabs(area) / 2.0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    cin >> n;
    v.resize(n);

    for (int t1 = 0; t1 < n; ++t1)
        cin >> v[t1].x >> v[t1].y;

    cout << polygonArea() << '\n';




    return 0;
}
