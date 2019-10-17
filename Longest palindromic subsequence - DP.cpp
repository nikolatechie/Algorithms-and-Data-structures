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


int n;
string s;
vector <vi> DP;

void printLPS()
{
    string seq;
    int i = 0, j = n-1;

    while (i <= j)
    {
        if (s[i] == s[j])
        {
            seq += s[j];
            ++i, --j;
        }
        else
        {
            if (DP[i][j-1] > DP[i+1][j])
                --j;
            else
                ++i;
        }
    }

    int m = seq.size();

    if (DP[0][n-1] & 1)
    {
        if (m == 1)
            cout << seq << '\n';
        else
        {
            string add = string(1, seq[m-1]);
            seq.pop_back();
            string rseq = seq;
            reverse(all(rseq));
            cout << seq << add << rseq << '\n';
        }
    }
    else
    {
        string rseq = seq;
        reverse(all(rseq));
        cout << seq << rseq << '\n';
    }
}

int findLPS()
{
    n = s.size();
    DP.resize(n);

    for (int t1 = 0; t1 < n; ++t1)
    {
        DP[t1].resize(n);
        DP[t1][t1] = 1;
    }

    for (int topCol = 1; topCol < n; ++topCol)
    {
        for (int i = 0, j = topCol; j < n; ++i, ++j)
        {
            if (s[i] == s[j])
            {
                DP[i][j] = 2; // maximal if len of sequence is 2
                if (j > i+1) DP[i][j] += DP[i+1][j-1];
            }
            else DP[i][j] = max(DP[i][j-1], DP[i+1][j]);
            // maximum by:
            // 1) ignoring letter s[i]
            // 2) ignoring letter s[j]
        }
    }

    return DP[0][n-1];
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    cin >> s;
    cout << findLPS() << '\n';
    printLPS();



    return 0;
}
