// Finding maximum sum of all increasing subsequences using Fenwick Tree/Binary Indexed Tree
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
using vi = vector<int>;
using vii = vi::iterator;

#define INF (1<<30)
#define MOD 1000000007
#define mp make_pair
#define mt make_tuple
#define all(c) c.begin(),c.end()
#define ms(name,val) memset(name, val, sizeof name)
#define np nullptr


const int N = 100001;
int n, A[N], ft[N];
map <int,int> M; // index compression

inline void Update(int i, int v)
{
    for (; i <= n; i += i&(-i))
		ft[i] = max(ft[i],v);
}

int Query(int i)
{
    int ans = 0;
    for (; i; i -= i&(-i)) ans = max(ans,ft[i]);
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    cin >> n;

    for (int t1 = 1; t1 <= n; ++t1)
    {
        cin >> A[t1];
        M[A[t1]];
    }

    int tempIndex = 0;

    for (auto &it: M)
        it.second = ++tempIndex;

    for (int t1 = 1; t1 <= n; ++t1)
    {
        int rangeMax = Query(M[A[t1]]-1);
        Update(M[A[t1]], rangeMax+A[t1]);
    }

    cout << Query(n) << '\n';


    return 0;
}
