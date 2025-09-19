
// оператор using для импортирования либо целового пространства имен, либо элемента в этом пространстве
#include <iostream>

namespace firstspace
{
int fisrt_a = 100;
}

using std :: cout;
using std :: endl;
using byte_8 = unsigned char;

int main(){
    cout << firstspace :: fisrt_a << endl;
    byte_8 ch;
    cout << "Hi, guys\n";
    return 0;

    
}

