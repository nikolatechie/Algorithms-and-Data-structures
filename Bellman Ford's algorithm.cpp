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


int n, m, src;
vi dist;
vector <tuple <int,int,int>> g;

void bellmanFord()
{
    dist.assign(n, INF);
    dist[src] = 0;

    for (int t1 = 1; t1 < n; ++t1)
    {
        // use a bool variable to optimize the second for loop

        for (int t2 = 0; t2 < m; ++t2)
        {
            int a = get<0>(g[t2]);
            int b = get<1>(g[t2]);
            int c = get<2>(g[t2]);
            dist[b] = min(dist[b], dist[a]+c);
            // if no improvements have been made, exit from these 2 for loops
        }
    }

    for (int t1 = 0; t1 < m; ++t1)
    {
        int a = get<0>(g[t1]);
        int b = get<1>(g[t1]);
        int c = get<2>(g[t1]);

        if (dist[b] > dist[a]+c)
        {
            cout << "Graph contains a negative cycle!\n";
            return;
        }
    }

    for (int t1 = 0; t1 < n; ++t1)
        cout << dist[t1] << ' ';
		
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    cin >> n >> m >> src;
    g.resize(m);

    for (int t1 = 0; t1 < m; ++t1)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[t1] = {a,b,c};
    }

    bellmanFord();



    return 0;
}
