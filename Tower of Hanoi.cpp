#pragma GCC optimize("O3")
#include <iostream>
using namespace std;

void hanojske_kule(int brojDiskova, char saStuba, char naStub, char pomocniStub)
{
    if (brojDiskova > 1) hanojske_kule(brojDiskova-1, saStuba, pomocniStub, naStub);
    cout << brojDiskova << saStuba << naStub << '\n';
    if (brojDiskova > 1) hanojske_kule(brojDiskova-1, pomocniStub, naStub, saStuba);
}

int main()
{
    ios_base::sync_with_stdio(0);


    int brojDiskova;
    cin >> brojDiskova;

    hanojske_kule(brojDiskova, 'A', 'C', 'B');



    return 0;
}
