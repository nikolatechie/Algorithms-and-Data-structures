// Range Minimum Query using 2D Sparse Table
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


const int N = 1000, LN = 10;
const int M = 1000, LM = 10;
int A[N][M], n, m;
int st[N][LN][M][LM];

void preprocess()
{
    // build a 1D sparse table for each row
    for (int row = 0; row < n; ++row)
    {
        // initialize the main values
        for (int col = 0; col < m; ++col)
            st[row][0][col][0] = A[row][col];

        for (int lenCol = 1; (1<<lenCol) <= m; ++lenCol)
        {
            for (int col = 0; col+(1<<lenCol)-1 < m; ++col)
                st[row][0][col][lenCol] = min(st[row][0][col][lenCol-1],
                                        st[row][0][col+(1<<(lenCol-1))][lenCol-1]);
        }
    }
    // now we have a sparse table for each row and we can calculate it for multiple rows, too
    for (int lenRow = 1; (1<<lenRow) <= n; ++lenRow)
    {
        for (int row = 0; row+(1<<lenRow)-1 < n; ++row)
        {
            for (int lenCol = 0; (1<<lenCol) <= m; ++lenCol)
            {
                for (int col = 0; col+(1<<lenCol)-1 < m; ++col)
                    st[row][lenRow][col][lenCol] = min(st[row][lenRow-1][col][lenCol],
                                                st[row+(1<<(lenRow-1))][lenRow-1][col][lenCol]);
            }
        }
    }
}

int Query(int &x1, int &y1, int &x2, int &y2)
{
    int kx = log2(x2-x1+1);
    int ky = log2(y2-y1+1);
    int M1 = min(st[x1][kx][y1][ky],st[x2-(1<<kx)+1][kx][y1][ky]);
    int M2 = min(st[x1][kx][y2-(1<<ky)+1][ky], st[x2-(1<<kx)+1][kx][y2-(1<<ky)+1][ky]);
    return min(M1,M2);
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    cin >> n >> m;

    for (int t1 = 0; t1 < n; ++t1)
    {
        for (int t2 = 0; t2 < m; ++t2)
            cin >> A[t1][t2];
    }

    preprocess();
    int q;
    cin >> q;

    while (q)
    {
        --q;
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        cout << Query(a,b,c,d) << '\n';
    }


    return 0;
}
