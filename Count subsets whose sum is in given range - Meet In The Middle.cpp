// Zadatak: Podskupovi

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


int n, n1, n2;
llint rangeA, rangeB, ans;
vector <llint> v, A, B;

void calculateSubarray(vector <llint> &x, int sz, int step)
{
    for (int t1 = 0; t1 < (1<<sz); ++t1)
    {
        llint sum = 0;

        for (int t2 = 0; t2 < sz; ++t2)
            if (t1&(1<<t2)) sum += v[t2+step];

        x.push_back(sum);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

	// counting subsets whose sum is
	// in the given range ...
    cin >> n >> rangeA >> rangeB;
    v.resize(n);
    n1 = (n>>1), n2 = n-n1;

    for (int t1 = 0; t1 < n; ++t1)
        cin >> v[t1];

    if (rangeA > rangeB)
    {
        cout << 0 << '\n';
        return 0;
    }

    calculateSubarray(A, n1, 0);
    calculateSubarray(B, n2, n1);
    sort(all(B));

    for (int t1 = 0; t1 < A.size(); ++t1)
    {
        int L = 0, R = B.size()-1, tmp1 = R+1;

        while (L <= R)
        {
            int M = (L+R)>>1;
            llint tmpSum = A[t1] + B[M];

            if (tmpSum < rangeA)
                L = M+1;
            else
            {
                if (tmpSum > rangeB)
                    R = M-1;
                else
                {
                    tmp1 = min(tmp1, M);
                    R = M-1;
                }
            }
        }

        if (tmp1 == B.size()) continue;
        int tmp2 = -1;
        L = 0, R = B.size()-1;

        while (L <= R)
        {
            int M = (L+R)>>1;
            llint tmpSum = A[t1] + B[M];

            if (tmpSum < rangeA)
                L = M+1;
            else
            {
                if (tmpSum > rangeB)
                    R = M-1;
                else
                {
                    tmp2 = max(tmp2, M);
                    L = M+1;
                }
            }
        }

        if (tmp2 != -1) ans += (tmp2-tmp1+1);
    }

    cout << ans << '\n';




    return 0;
}
