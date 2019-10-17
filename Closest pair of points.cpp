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

    inline bool operator()(const Point &a, const Point &b) const
    {
        return (a.x < b.x);
    }
};

double dist(Point a, Point &b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) +
            (a.y - b.y) * (a.y - b.y));
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    int n;
    cin >> n;
    vector <Point> p(n);

    for (int t1 = 0; t1 < n; ++t1)
        cin >> p[t1].x >> p[t1].y;

    // sort by ascending x
    sort(all(p), Point());

    int left = 0; // for sweep line
    double ans = INF;
    set <Point, Point> S;
    S.insert(p[0]);

    for (int t1 = 1; t1 < n; ++t1)
    {
        // if point at index left + current min distance
        // doesn't reach the current point, then delete it
        while (left < t1 && (p[left].x + ans) < p[t1].x)
            S.erase(p[left++]);

        set <Point,Point>::iterator it;
        it = S.lower_bound(Point{p[t1].x - ans, p[t1].y - ans});
        // find all points which can be reached from the
        // current point within the minimal current distance

        // and try to update the answer
        for (; it != S.end(); ++it)
            ans = min(ans, dist(*it, p[t1]));

        // add current point to the set
        S.insert(p[t1]);
    }

    cout << ans << '\n';





    return 0;
}
