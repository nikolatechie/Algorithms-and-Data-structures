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

int orientation(Point &p1, Point &p2, Point &p3)
{
    // (x2-x1)/(y2-y1); (x3-x2)/(y3-y2)
    int val = (p2.y - p1.y) * (p3.x - p2.x)
            - (p2.x - p1.x) * (p3.y - p2.y);

    if (val == 0) return 0;

    return (val < 0) ? -1:1;
}

void convexHull(vector <Point> v, int n)
{
    if (n < 3) return;
    vector <Point> hull;
    int l = 0;

    // find the leftmost point
    for (int t1 = 1; t1 < n; ++t1)
        if (v[t1].x < v[l].x) l = t1;

    int p = l, q;

    do
    {
        hull.push_back(v[p]);

        q = (p+1)%n; // choose a random next point

        for (int t1 = 0; t1 < n; ++t1)
        {
            // counterclockwise direction
            if (orientation(v[p], v[t1], v[q]) == -1)
                q = t1;
        }

        p = q;
    }
    while (p != l);

    cout << '\n';
    for (int t1 = 0; t1 < hull.size(); ++t1)
        cout << hull[t1].x << ' ' << hull[t1].y << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    int n;
    cin >> n;
    vector <Point> v(n);

    for (int t1 = 0; t1 < n; ++t1)
        cin >> v[t1].x >> v[t1].y;

    convexHull(v, n);




    return 0;
}
