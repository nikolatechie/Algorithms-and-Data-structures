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
 
#define INF ullint(1e9)
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
 
 
int cnt[100000]; // could have used unordered_map
 
int main()
{
    ios_base::sync_with_stdio(0);
 
    int q;
    cin >> q;
    priority_queue <int> maxHeap;
    priority_queue <int,vector<int>,greater<int>> minHeap;
 
    while (q)
    {
        int i;
        cin >> i;
 
        if (i == 1)
        {
            int x;
            cin >> x;
            ++cnt[x];
            maxHeap.push(x);
            minHeap.push(x);
        }
        else if (i == 2)
        {
            int x;
            cin >> x;
            if (!cnt[x])
                cout << -1 << '\n';
            else
                --cnt[x];
        }
        else if (i == 3)
        {
            while (!maxHeap.empty() && !cnt[maxHeap.top()])
                maxHeap.pop();
 
            if (maxHeap.empty())
                cout << -1 << '\n';
            else
                cout << maxHeap.top() << '\n';
        }
        else if (i == 4)
        {
            while (!minHeap.empty() && !cnt[minHeap.top()])
                minHeap.pop();
 
            if (minHeap.empty())
                cout << -1 << '\n';
            else
                cout << minHeap.top() << '\n';
        }
 
        --q;
    }
 
 
    return 0;
}
