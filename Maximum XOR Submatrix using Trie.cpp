#include <bits/stdc++.h>
using namespace std;

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


int nxt;
int A[10001][21];
int B[10001];
int T[10001*32][2];
// static binary trie

void Insert(int x)
{
    int root = 1; // can be set to 0, but then we have to set nxt to 1

    for (int i = 27; i > -1; --i)
    {
        bool b = (x&(1<<i));
        if (!T[root][b]) T[root][b] = nxt++;
        root = T[root][b];
    }
}

int Query(int &x)
{
    int ans = 0;
    int root = 1; // can be set to 0, but then we have to set nxt to 1

    for (int i = 27; i > -1; --i)
    {
        bool b = (x&(1<<i));

        if (T[root][b^1])
        {
            ans |= (1<<i);
            root = T[root][b^1];
        }
        else root = T[root][b];
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);


    int n, m, ans = 0;
    cin >> n >> m;

    for (int t1 = 1; t1 <= n; ++t1)
    {
        for (int t2 = 1; t2 <= m; ++t2)
        {
            cin >> A[t1][t2];
            A[t1][t2] ^= A[t1][t2-1];
        }
    }
	
    for (int L = 1; L <= m; ++L)
    {
        for (int R = L; R <= m; ++R)
        {
            memset(T, 0, sizeof T);
            nxt = 2;
            Insert(0);

            for (int t1 = 1; t1 <= n; ++t1)
            {
                B[t1] = A[t1][R]^A[t1][L-1]^B[t1-1];
                ans = max(ans,Query(B[t1]));
                Insert(B[t1]);
            }
        }
    }

    cout << ans << '\n';


    return 0;
}
