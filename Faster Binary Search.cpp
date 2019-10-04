const int N = (1e5)+5;
int a[N];

int binarySearch(int x)
{
    int i, step;

    for (step = 1; step < N; step <<= 1);

    for (i = 0; step; step >>= 1)
    {
        if (i+step < N && x > a[i+step])
            i += step;
    }

    return i;
}
