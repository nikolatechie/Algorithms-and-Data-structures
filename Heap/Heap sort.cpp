#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned short usint;
typedef unsigned uint;
typedef long lint;
typedef short sint;
typedef long double ld;
typedef unsigned long ulint;
typedef unsigned long long ullint;
typedef long long llint;
 
#define INF ullint(2e9)
#define MOD 1000000007
#define mp make_pair
#define mt make_tuple
#define pii pair <int,int>
#define pib pair <int,bool>
#define pll pair <long,long>
#define pcc pair <char,char>
#define pui pair <uint,uint>
#define pul pair <ulint,ulint>
#define pff pair <float,float>
#define pllll pair <llint,llint>
#define pss pair <string,string>
#define pullull pair <ullint,ullint>
// inline funkcije
 
 
struct MaxHeap
{
    int *h;
    int n;
 
    MaxHeap(int _n)
    {
        n = _n;
        h = new int[n];
    }
 
    ~MaxHeap()
    {
        delete []h;
    }
 
    void read()
    {
        for (int t1 = 0; t1 < n; ++t1)
            cin >> h[t1];
    }
 
    void maxHeapify(int i, int &en)
    {
        int l = (i<<1)+1;
        int r = l+1;
        int veci = i;
 
        if (l < en && h[l] > h[i])
            veci = l;
 
        if (r < en && h[r] > h[veci])
            veci = r;
 
        if (veci != i)
        {
            swap(h[i],h[veci]);
            maxHeapify(veci,en);
        }
    }
 
    void heapSort()
    {
        // construct max heap first
        for (int i = (n>>1)-1; i >= 0; --i)
            maxHeapify(i,n);
 
        for (int i = n-1; i; --i)
        {
            // put the root of binary heap at the 'end' of the array
            swap(h[0],h[i]);
            // find the nax largest element
            maxHeapify(0,i);
        }
    }
 
    void print()
    {
        cout << '\n';
        for (int t1 = 0; t1 < n; ++t1)
            cout << h[t1] << ' ';
        cout << '\n';
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
 
    int n;
    cin >> n;
 
    MaxHeap mh(n);
    mh.read();
    mh.heapSort();
    mh.print();
 
 
 
 
    return 0;
}
