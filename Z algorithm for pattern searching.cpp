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


vi Z;
int n;
string txt, pat, s;

void Build()
{
    Z.resize(n);
    Z[0] = n;
    int L = 0, R = 0;

    for (int t1 = 1; t1 < n; ++t1)
    {
        if (t1 > R)
        {
            L = R = t1;

            while (R < n && s[R-L] == s[R]) ++R;
            Z[t1] = R-L;
            --R;
        }
        else
        {
            int k = t1-L;

            if (Z[k] < R-t1+1)
                Z[t1] = Z[k];
            else
            {
                L = t1;

                while (R < n && s[R-L] == s[R]) ++R;
                Z[t1] = R-L;
                --R;
            }
        }
    }
}

void Search()
{
    if (pat.size() > txt.size()) return;
    s = pat + '$' + txt;
    n = s.size();
    Build();

    for (int t1 = 0; t1 < n; ++t1)
    {
        if (Z[t1] == pat.size())
            cout << "Occurence found at index " << t1-pat.size()-1 << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    getline(cin, txt);
    getline(cin, pat);
    Search();



    return 0;
}
