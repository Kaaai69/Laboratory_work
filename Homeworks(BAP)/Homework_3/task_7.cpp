#include <iostream>
#include <algorithm>
#include <vector>
using std::cout;

int main()
{
    int a1 = 1;
    int b1 = 1;
    int c1 = 1;
    int h1 = 6;
    int a2 = 2;
    int b2 = -1;
    int c2 = 3;
    int h2 = 14;
    int a3 = -1;
    int b3 = 4;
    int c3 = -1;
    int h3 = 2;
    int det = (a1 * b2 * c3 + b1 * c2 * a3 + a2 * b3 * c1 - a3 * b2 * c1 - b3 * c2 * a1 - a2 * b1 * c3);
    int det1 = (h1 * b2 * c3 + b1 * c2 * h3 + h2 * b3 * c1 - h3 * b2 * c1 - b3 * c2 * h1 - h2 * b1 * c3);
    int det2 = (a1 * h2 * c3 + h1 * c2 * a3 + a2 * h3 * c1 - a3 * h2 * c1 - h3 * c2 * a1 - a2 * h1 * c3);
    int det3 = (a1 * b2 * h3 + b1 * h2 * a3 + a2 * b3 * h1 - a3 * b2 * h1 - b3 * h2 * a1 - a2 * b1 * h3);
    cout << "x = " << (double(det1) / det) << ", y = " << (double(det2) / det1) << ", z = " << (double(det3) / det1) << "\n";
    return 0;

}