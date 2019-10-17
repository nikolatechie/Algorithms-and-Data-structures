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

    if (val == 0) return 0; // collinear

    return (val < 0) ? -1: 1; // counterclockwise: clockwise
}

bool onSegment(Point p, Point q, Point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
            return 1;

    return 0;
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4) return 1;

    // Special cases:
    // p1, q1 and p2 are collinear and p2 lies on segment p1-q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return 1;

    // p1, q1 and q2 are collinear and q2 lies on segment p1-q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return 1;

    // p2, q2 and p1 are collinear and p1 lies on segment p2-q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return 1;

    // p2, q2 and q1 are collinear and q1 lies on segment p2-q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return 1;

    return 0; // doesn't fall in above cases
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    Point p1, q1, p2, q2;
    cin >> p1.x >> p1.y >> q1.x >> q1.y;
    cin >> p2.x >> p2.y >> q2.x >> q2.y;

    cout << ((doIntersect(p1, q1, p2, q2)) ? "Yes\n":"No\n");




    return 0;
}
