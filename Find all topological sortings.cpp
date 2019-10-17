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
using vii = vi::iterator;

#define INF (1<<30)
#define MOD 1000000007
#define mp make_pair
#define mt make_tuple
#define all(c) c.begin(), c.end()
#define ms(name,val) memset(name, val, sizeof name)
#define np nullptr


int n, m;
vi ans, inDegree;
vector <vi> graf;
vector <bool> vis;

void allTopSort()
{
    for (int t1 = 0; t1 < n; ++t1)
    {
        if (!inDegree[t1] && !vis[t1])
        {
            for (int t2 = 0; t2 < graf[t1].size(); ++t2)
                --inDegree[graf[t1][t2]];

            ans.push_back(t1);
            vis[t1] = 1;
            allTopSort();
            vis[t1] = 0;
            ans.pop_back();

            for (int t2 = 0; t2 < graf[t1].size(); ++t2)
                ++inDegree[graf[t1][t2]];
        }
    }

    if (ans.size() == n)
    {
        for (auto &it: ans) cout << it << ' ';
        cout << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    //cin.tie(0);

    cin >> n >> m;
    graf.resize(n);
    inDegree.resize(n);
    vis.resize(n);

    while (m)
    {
        --m;
        int a, b;
        cin >> a >> b;
        graf[a].push_back(b);
        ++inDegree[b];
    }

    allTopSort();



    return 0;
}
