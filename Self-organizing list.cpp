// Self organizing list is a data structure where a node becomes a head node after searching it
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


struct SOL
{
    int val;
    SOL *next;

    SOL()
    {
        val = 0;
        next = nullptr;
    }
};

void ispis(SOL *head)
{
    cout << '\n';
    SOL *temp = head;

    while (temp != nullptr)
    {
        cout << temp->val << ' ';
        temp = temp->next;
    }

    cout << '\n';
}

SOL* createNew(int &x)
{
    SOL *novi = new SOL;
    novi->val = x;
    novi->next = nullptr;
    return novi;
}

SOL* ubaci(SOL *head, int &x)
{
    if (head == nullptr)
        return createNew(x);

    head->next = ubaci(head->next,x);
    return head;
}

SOL* trazi(SOL *head, int &x)
{
    if (head == nullptr || head->next == nullptr) return nullptr;
    if (head->next->val == x) return head;

    return trazi(head->next,x);
}

void oslobodi(SOL *head)
{
    if (head == nullptr) return;
    oslobodi(head->next);
    delete head;
}

int main()
{
    ios_base::sync_with_stdio(0);


    SOL *head = nullptr;

    int n;
    cin >> n;

    for (int t1 = 0; t1 < n; ++t1)
    {
        int x;
        cin >> x;
        head = ubaci(head,x);
    }

    ispis(head);
    int q;
    cin >> q;

    while (q--)
    {
        int a;
        cin >> a;

        if (a == 2)
            ispis(head);
        else
        {
            int x;
            cin >> x;
            SOL *f = trazi(head,x);
            if (f != nullptr)
            {
                SOL *cp = f->next;
                f->next = cp->next;
                cp->next = head;
                head = cp;
            }
        }
    }

    oslobodi(head);


    return 0;
}
