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


int n;
vi v;

int maxGCDpair()
{
    int high = 0;

    // finding the greatest element
    for (int t1 = 0; t1 < n; ++t1)
        high = max(high, v[t1]);

    // storing count of divisors
    // i.e. potential GCDs
    vi divCnt(high+1, 0);

    for (int t1 = 0; t1 < n; ++t1)
    {
        for (int t2 = 1; t2 <= sqrt(v[t1]); ++t2)
        {
            if (v[t1] % t2 == 0)
            {
                ++divCnt[t2];
                if (t2 != v[t1]/t2) ++divCnt[v[t1]/t2];
            }
        }
    }

    // if at least two numbers
    // have t1 as their factor
    // then it is their GCD
    for (int t1 = high; t1; --t1)
        if (divCnt[t1] > 1) return t1;

    return 1;
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    cin >> n;
    v.resize(n);

    for (int t1 = 0; t1 < n; ++t1)
        cin >> v[t1];

    cout << maxGCDpair() << '\n';



    return 0;
}
