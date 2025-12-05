#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using std::cout;

int main()
{
    int numbers[] = {1, 10, 9, 8, 43, 98, 45, 22, 12};
    std::ofstream file("numbers.bin", std::ios::binary);
    file.write(reinterpret_cast<char*>(numbers), sizeof(numbers));
    file.close();
    std::ifstream infile("numbers.bin", std::ios::binary);
    if (!infile.is_open()){
        cout << "Лошпед\n";
    }
    infile.seekg(0, std::ios::end);
    size_t file_size = infile.tellg();
    infile.seekg(0, std::ios::beg);
    int* buffer = new int[file_size / sizeof(int)];
    infile.read(reinterpret_cast<char*>(buffer), sizeof(buffer));
    infile.close();
    delete[] buffer;
    return 0;

}