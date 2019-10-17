// Dynamic programming solution
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


int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();
    vector <vi> DP(n+1, vi(m+1, 0));

    for (int t1 = 0; t1 <= n; ++t1)
    {
        for (int t2 = 0; t2 <= m; ++t2)
        {
            if (!t1)
                DP[t1][t2] = t2;
            else if (!t2)
                DP[t1][t2] = t1;
            else if (a[t1-1] == b[t2-1])
                DP[t1][t2] = 1 + DP[t1-1][t2-1];
            else
                DP[t1][t2] = 1 + min(DP[t1-1][t2], DP[t1][t2-1]);
        }
    }

    cout << "\nShortest common supersequence:\n";
    cout << "Length: " << DP[n][m] << '\n';
    cout << "Sequence: ";
    string seq;
    int x = n, y = m;

    while (x && y)
    {
        if (a[x-1] == b[y-1])
        {
            seq.push_back(b[y-1]);
            --x, --y;
        }
        else if (DP[x-1][y] < DP[x][y-1])
        {
            seq.push_back(a[x-1]);
            --x;
        }
        else
        {
            seq.push_back(b[y-1]);
            --y;
        }
    }

    while (x)
    {
        seq.push_back(a[x-1]);
        --x;
    }

    while (y)
    {
        seq.push_back(b[y-1]);
        --y;
    }

    reverse(all(seq));
    cout << seq << '\n';



    return 0;
}
