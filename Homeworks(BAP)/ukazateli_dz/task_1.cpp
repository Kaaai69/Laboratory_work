#include <iostream>
#include <algorithm>

using std::cout;

void swap_Pointers(int **a, int **b){
    int* c = *a; // разыменовали указатель на указатель, теперь он указывает на адрес переменной, а не указателя
    *a = *b;
    *b = c;
}

int main()
{
    int x, y;
    int *p1 = &x;
    int *p2 = &y;
    cout << *p1 << " " << *p2 << "\n";
    swap_Pointers(&p1, &p2);
    cout << *p1 << " " << *p2 << "\n";
}