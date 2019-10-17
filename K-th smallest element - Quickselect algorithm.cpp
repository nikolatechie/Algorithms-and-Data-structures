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

int Partition(int l, int r)
{
    int x = v[r], i = l;

    for (int j = l; j < r; ++j)
    {
        if (v[j] <= x)
        {
            swap(v[i], v[j]);
            ++i;
        }
    }

    swap(v[i], v[r]);

    return i;
}

int kthSmallest(int l, int r, int k)
{
    if (k >= 1 && k <= r-l+1)
    {
        int i = Partition(l, r);

        if (k-1 == i-l) return v[i];
        if (k-1 < i-l) return kthSmallest(l, i-1, k);
        return kthSmallest(i+1, r, k-i+l-1);
    }

    return INF;
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    int k;
    cin >> n >> k;
    v.resize(n);

    for (int t1 = 0; t1 < n; ++t1)
        cin >> v[t1];

    cout << kthSmallest(0, n-1, k) << '\n';



    return 0;
}
