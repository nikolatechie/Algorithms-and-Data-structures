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


struct MinHeap
{
    int *h;
    int capacity;
    int heap_size;

    MinHeap(int cap)
    {
        heap_size = 0;
        capacity = cap;
        h = new int[cap];
    }

    int parent(int &i)
    {
        return (i-1)>>1;
    }

    int left(int &i)
    {
        return (i<<1)+1;
    }

    int right(int &i)
    {
        return (i<<1)+2;
    }

    void MinHeapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;

        if (l < heap_size && h[l] < h[i])
            smallest = l;

        if (r < heap_size && h[r] < h[smallest])
            smallest = r;

        if (smallest != i)
        {
            swap(h[i],h[smallest]);
            MinHeapify(smallest);
        }
    }

    void insertKey(int k)
    {
        if (heap_size == capacity)
        {
            cout << "Overflow!\n";
            return;
        }

        ++heap_size;
        int i = heap_size-1;
        h[i] = k;

        while (i && h[parent(i)] > h[i])
        {
            swap(h[i],h[parent(i)]);
            i = parent(i);
        }
    }

    void decreaseKey(int i, int newVal)
    {
        h[i] = newVal;

        while (i && h[parent(i)] > h[i])
        {
            swap(h[i],h[parent(i)]);
            i = parent(i);
        }
    }

    int getMin()
    {
        if (heap_size < 1) return INF;
        return h[0];
    }

    int extractMin()
    {
        if (heap_size <= 0) return INF;

        if (heap_size == 1)
        {
            --heap_size;
            return h[0];
        }

        int root = h[0];
        h[0] = h[heap_size-1];
        --heap_size;
        MinHeapify(0);
        return root;
    }

    void deleteKey(int i)
    {
        decreaseKey(i,-INF);
        extractMin();
    }
};


int main()
{
    ios_base::sync_with_stdio(0);


    MinHeap mh(11);
    mh.insertKey(3);
    mh.insertKey(2);
    mh.deleteKey(1);
    mh.insertKey(15);
    mh.insertKey(5);
    mh.insertKey(4);
    mh.insertKey(45);

    cout << mh.extractMin() << ' ';
    cout << mh.getMin() << ' ';
    mh.decreaseKey(2,1);
    cout << mh.getMin() << '\n';



    return 0;
}
