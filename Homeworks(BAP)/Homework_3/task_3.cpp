#include <iostream>
#include <algorithm>
#include <vector>
using std::cout;

int main()
{
    int line, column;
    cout << "Введите количество строк и столбцов матрицы(в указанном порядке): ";
    std::cin >> line >> column;
    int array[line][column];
    cout << "\nВведите элементы матрицы по строкам:\n";

    for (int i = 0; i < line; i++){
        for (int j = 0; j < column; j++){
            std::cin >> array[i][j];
        }
    }
    std::vector<std::string> itog(line * column, std::string("NONE"));
     for (const auto& word : itog){
        cout << word << " ";
    }
    cout << '\n';
    for (int i = 0; i < line; i++){
        // для строк и столбцов (максимум)
        int maxi_s = 0;
        int index_maxi_s = 0;
        int index_maxi_c = 0;
        
        int maxi_scol = 0;
        int index_maxi_scol = 0;
        int index_maxi_ccol = 0;
        // для строк и столбцов (минимум)
        int mini_s = 1000;
        int index_mini_s = 1000;
        int index_mini_c = 0;

        int mini_scol = 1000;
        int index_mini_scol = 0;
        int index_mini_ccol = 0;
        for (int j = 0; j < column; j++){
            if (array[i][j] > maxi_s){
                maxi_s = array[i][j];
                index_maxi_s = i;
                index_maxi_c = j;
            }
            if (array[j][i] > maxi_scol){
                maxi_scol = array[j][i];
                index_maxi_scol = j;
                index_maxi_ccol = i;
            }
            if (array[i][j] < mini_s){
                mini_s = array[i][j];
                index_mini_s = i;
                index_mini_c = j;
            }
            if (array[j][i] < mini_scol){
                mini_scol = array[j][i];
                index_mini_scol = j;
                index_mini_ccol = i;
            }
        }
        if (mini_s == maxi_scol and index_mini_s == index_maxi_scol and index_mini_c == index_maxi_ccol){
            std::string str1 = std::to_string(index_mini_s);
            std::string str2 = std::to_string(index_mini_c);
            std::string s1("A");
            itog.insert(itog.begin() + index_mini_c + mini_s, s1 + str1 + str2);
            cout << "A" << mini_s;
        }
        if (maxi_s == mini_scol and index_maxi_s == index_mini_scol and index_maxi_c == index_mini_ccol){
            std::string str1 = std::to_string(index_maxi_s);
            std::string str2 = std::to_string(index_maxi_c);
            std::string s1("A");
            itog.insert(itog.begin() + index_maxi_c + maxi_s, s1 + str1 + str2);
        }

    }
    return 0;
}