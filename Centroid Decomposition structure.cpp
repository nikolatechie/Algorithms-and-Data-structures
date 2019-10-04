struct CentroidDecomposition
{
    vector <set <int>> g;
    vi parent, sz;

    CentroidDecomposition(vector <set <int>> &_g): g(_g)
    {
        int n = g.size();
        parent.resize(n);
        sz.resize(n);
        Build(0, -1);
    }

    void Build(int x, int p)
    {
        int n = findSz(x, p);
        int centroid = findCentroid(x, p, n);
        if (p == -1) p = centroid;
        parent[centroid] = p;
        set <int>::iterator it = g[centroid].begin();

        for (; !g[centroid].empty();)
        {
            int y = *it;
            g[centroid].erase(it);
            g[y].erase(centroid);
            Build(y, centroid);
            it = g[centroid].begin();
        }
    }

    int findSz(int x, int p)
    {
        sz[x] = 1;

        for (auto y: g[x])
            if (y != p) sz[x] += findSz(y, x);

        return sz[x];
    }

    int findCentroid(int x, int p, int n)
    {
        for (auto y: g[x])
            if (y != p && sz[y] > n/2) return findCentroid(y, x, n);

        return x;
    }
};
