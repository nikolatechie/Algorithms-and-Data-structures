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


int median(int *x, int n)
{
    if (n&1) return x[n>>1];
    return (x[n>>1] + x[(n>>1)-1])>>1;
}

int getMedian(int *a, int *b, int n)
{
    if (n <= 0) return -1;
    if (n == 1) return (a[0] + b[0])>>1;
    if (n == 2) return (max(a[0],b[0])+min(a[1],b[1]))>>1;

    int m1 = median(a, n);
    int m2 = median(b, n);

    if (m1 == m2)
        return m1;

    if (m1 < m2)
    {
        if (n % 2 == 0)
            return getMedian(a + n/2 - 1, b, n - n/2 + 1);

        return getMedian(a + n/2, b, n- n/2);
    }

    if (n % 2 == 0)
        return getMedian(b + n/2 - 1, a, n - n/2 + 1);

    return getMedian(b + n/2, a, n - n/2);
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    int a[] = {1, 2, 3, 6};
    int b[] = {4, 6, 8, 10};
    int n = 4;

    cout << getMedian(a, b, n) << '\n';



    return 0;
}
