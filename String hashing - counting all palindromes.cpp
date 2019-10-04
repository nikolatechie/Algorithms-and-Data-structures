// Solution involving string hashing and binary search
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
#define mt make_tuple
#define all(c) c.begin(), c.end()
#define ms(name,val) memset(name, val, sizeof name)
#define np nullptr


ci N = 1e5 + 5, m = 1e9 + 9;
int n, mp[150];
llint p[N], hpref[N], hsuf[N];
string s;

void calculateHash()
{
    mp['$'] = 27;

    for (char c = 'a'; c <= 'z'; ++c)
        mp[c] = (c-'a'+1);

    p[0] = 1, p[1] = 31;

    for (int t1 = 2; t1 <= n; ++t1)
        p[t1] = (p[t1-1] * p[1]) % m;

    hpref[0] = mp[s[0]];
    hsuf[n-1] = mp[s[n-1]];

    for (int t1 = 1; t1 < n; ++t1)
    {
        hpref[t1] = (hpref[t1-1] + mp[s[t1]]*p[t1]) % m;
        hsuf[n-t1-1] = (hsuf[n-t1] + mp[s[n-t1-1]]*p[t1]) % m;
    }
}

void getHash(llint &h1, llint &h2, ci &a, ci &b, ci &c, ci &d)
{
    h1 = (a == 0) ? hpref[b]: (hpref[b]+m-hpref[a-1]) % m;
    h2 = (d == n-1) ? hsuf[c]: (hsuf[c]+m-hsuf[d+1]) % m;
    int revDegree = n-d-1;

    if (revDegree < a)
        h2 = (h2 * p[a-revDegree]) % m;
    else if (revDegree > a)
        h1 = (h1 * p[revDegree-a]) % m;
}

int countPalindromes()
{
    int ans = 0;

    // t1 - middle index of palindrome
    for (int t1 = 1; t1 < n-1; ++t1)
    {
        int lenAns = 0, L = 0, R = min(t1, n-t1-1);

        // binary search for the length
        while (L <= R)
        {
            int M = (L+R)>>1;
            int a = min(t1-M, t1-1), b = t1-1, c = t1+1, d = max(t1+M, t1+1);
            llint h1, h2;
            getHash(h1, h2, a, b, c, d);

            if (h1 == h2)
            {
                lenAns = max(lenAns, M);
                L = M+1;
            }
            else R = M-1;
        }

        if (lenAns) ans += (lenAns>>1) + (s[t1]=='$');
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    string tmp_s;
    cin >> tmp_s;

    for (int t1 = 0; t1 < tmp_s.size(); ++t1)
    {
        s += tmp_s[t1];
        if (t1 < tmp_s.size()-1) s += '$';
    }

    n = s.size();
    calculateHash();
    cout << countPalindromes() << '\n';


    return 0;
}
