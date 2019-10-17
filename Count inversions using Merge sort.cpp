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
vi a;
llint ans;

void mergeSort(int l, int r)
{
    if (l >= r) return;

    int m = (l+r)>>1;
    mergeSort(l, m);
    mergeSort(m+1, r);

    int n1 = m-l+1;
    int n2 = r-m;
    vi L(n1), R(n2);

    for (int t1 = 0; t1 < n1; ++t1)
        L[t1] = a[l+t1];

    for (int t1 = 0; t1 < n2; ++t1)
        R[t1] = a[m+1+t1];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] > R[j])
        {
            a[k] = R[j];
            ans += (n1-i);
            ++j;
        }
        else
        {
            a[k] = L[i];
            ++i;
        }

        ++k;
    }

    while (i < n1)
    {
        a[k] = L[i];
        ++i, ++k;
    }

    while (j < n2)
    {
        a[k] = R[j];
        ++j, ++k;
    }
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
        a.clear();
        a.resize(n);

        for (int t1 = 0; t1 < n; ++t1)
            cin >> a[t1];

        ans = 0;
        mergeSort(0, n-1);
        cout << ans << '\n';
    }


    return 0;
}
