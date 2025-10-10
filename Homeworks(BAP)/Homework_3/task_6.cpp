#include <iostream>
#include <algorithm>
#include <vector>
using std::cout;

int main()
{
    int a1 = 2;
    int b1 = 3;
    int a2 = 5;
    int b2 = -1;
    int c1 = 13;
    int c2 = 9;
    int det = (a1 * b2 - a2 * b1);
    int det1 = (c1 * b2 - c2 * b1);
    int det2 = (a1 * c2 - a2 * c1);
    cout << "x = " << (double(det1) / det) << ", y = " << (double(det2) / det1) << "\n";
    return 0;

}