// RSQ using 2D Fenwick Tree/Binary Indexed Tree
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
using vi = vector<int>;
using vii = vi::iterator;

#define INF (1<<30)
#define MOD 1000000007
#define mp make_pair
#define mt make_tuple
#define all(c) c.begin(),c.end()
#define ms(name,val) memset(name, val, sizeof name)
#define np nullptr


const int N = 1025;
int n, ft[N][N];

inline void yUpdate(int &x, int y, int v)
{
    for (; y <= n; y += y&(-y)) ft[x][y] += v;
}

void Update(int x, int y, int v)
{
    for (; x <= n; x += x&(-x)) yUpdate(x, y, v);
}

int yQuery(int &x, int y)
{
    int ans = 0;
    for (; y; y -= y &(-y)) ans += ft[x][y];
    return ans;
}

int Query(int x, int y)
{
    int ans = 0;
    for (; x; x -= x&(-x)) ans += yQuery(x, y);
    return ans;
}

int Sum(int x1, int y1, int x2, int y2)
{
    return (Query(x2,y2) - Query(x2,y1-1) - Query(x1-1,y2) + Query(x1-1,y1-1));
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tc;
    cin >> tc;

    while (tc)
    {
        --tc;
        cin >> n;
        ms(ft,0);

        while (1)
        {
            string op;
            cin >> op;
            if (op[0] == 'E') break;

            int x1, y1;
            cin >> x1 >> y1;
            ++x1, ++y1;

            if (op[1] == 'E') // set value
            {
                int v;
                cin >> v;
                int curVal = Sum(x1,y1,x1,y1);
                Update(x1, y1, v - curVal);
            }
            else // range sum query
            {
                int x2, y2;
                cin >> x2 >> y2;
                ++x2, ++y2;
                cout << Sum(x1,y1,x2,y2) << '\n';
            }
        }

        cout << '\n';
    }


    return 0;
}
