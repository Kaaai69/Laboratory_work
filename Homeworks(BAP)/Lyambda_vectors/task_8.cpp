#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
using std::cout;

int main()
{
    std::vector<int> speed = {76, 142, 18, 125, 53, 0, 165, 88, 31, 154, 42, 97, 5, 138, 62, 117, 25, 168, 74, 12, 132, 48, 112, 19, 159, 85, 37, 121, 58, 7, 147, 69, 104, 29, 173, 82, 16, 135, 45, 1, 128, 51, 93, 23, 162, 78, 34, 115, 66, 14};
    auto sred = double(std::accumulate(speed.begin(), speed.end(), 0)) / speed.size();
    auto all_move = std::find(speed.begin(), speed.end(), 0);
    if (all_move != speed.end()){cout << "Двигался не всегда.\n";}
    else {cout << "Двигался всегда.\n";}

    cout << "Среднее значение скорости: " << sred << "\n";
    cout << "Превышение скорости: ";
    speed.erase(std::remove_if(speed.begin(), speed.end(), [](int x){return (x <= 120);}), speed.end());
    for (int x : speed) cout << x << " ";
    cout << "\n";

    cout << "Десять максимальных значений: ";
    std::sort(speed.begin(), speed.end(), std::greater<int>());
    std::for_each(speed.begin(), speed.begin() + 10, [](int x ){cout << x << " ";});
    cout << "\n";
    return 0;
}