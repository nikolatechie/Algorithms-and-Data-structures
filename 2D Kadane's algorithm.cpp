// Submatrix with largest sum using 2D Kadane's algorithm
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


const int MX = 1001;
int n, m;
int M[MX][MX], tmp[MX];
int maxSum, topRow, bottomRow, leftCol, rightCol;

void copyColumn(int &col)
{
    for (int t1 = 0; t1 < n; ++t1)
        tmp[t1] = M[t1][col];
}

void addColumn(int &col)
{
    for (int t1 = 0; t1 < n; ++t1)
        tmp[t1] += M[t1][col];
}

void Kadane1D(int &L, int &R)
{
    int mxSum = 0, tmpSum = 0;
    int top = 0, bottom = 0;
    int topLocal = 0, bottomLocal = 0;

    for (int t1 = 0; t1 < n; ++t1)
    {
        tmpSum += tmp[t1];

        if (tmpSum < 0)
        {
            tmpSum = 0;
            topLocal = t1+1;
        }
        else if (tmpSum > mxSum)
        {
            mxSum = tmpSum;
            bottomLocal = t1;
            top = topLocal, bottom = bottomLocal;
        }
    }

    if (mxSum > maxSum)
    {
        maxSum = mxSum;
        topRow = top;
        bottomRow = bottom;
        leftCol = L;
        rightCol = R;
    }
}

void Kadane2D()
{
    for (int L = 0; L < m; ++L)
    {
        copyColumn(L);
        Kadane1D(L, L);

        for (int R = L+1; R < m; ++R)
        {
            addColumn(R);
            Kadane1D(L, R);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    cin >> n >> m;

    for (int t1 = 0; t1 < n; ++t1)
        for (int t2 = 0; t2 < m; ++t2)
            cin >> M[t1][t2];

    Kadane2D();
    cout << "Max sum = " << maxSum << '\n';
    printf("Rectangle coordinates: (%d,%d), (%d,%d)\n", topRow, leftCol, bottomRow, rightCol);



    return 0;
}
