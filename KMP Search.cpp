// KMP algorithm for pattern searching in O(n+m)
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


int n, m;
string t, p;
vi tmp;

void buildArray()
{
    tmp.resize(m);
    int i = 0, j = 1;

    while (j < m)
    {
        while (i > 0 && p[i] != p[j])
            i = tmp[i-1];

        if (p[i] == p[j])
        {
            tmp[j] = i+1;
            ++i, ++j;
        }
        else ++j;
    }
}

void KMP_Search()
{
    int i = 0, j = 0;

    while (i < n)
    {
        while (j > 0 && t[i] != p[j])
            j = tmp[j-1];

        if (t[i] == p[j])
        {
            ++i;
            ++j;

            if (j == m)
                cout << i-m << '\n';
        }
        else ++i;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    cin >> t >> p;
    n = t.size();
    m = p.size();
    buildArray();
    KMP_Search();



    return 0;
}
