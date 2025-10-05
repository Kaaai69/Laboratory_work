#include <iostream>
#include <vector>
using std::cout;

int main()
{
    int line, column = 2;
    cout << "Введите количество сторон многоульника: ";
    std::cin >> line;
    int figura[line][column];
    int proverka[1][column];
    for (int iter = 0; iter < line; iter++){
        for (int cl = 0; cl < column - 1; cl++){
            cout << "Введите координаты " << iter + 1 << " точки: ";
            std::cin >> figura[iter][cl] >> figura[iter][cl + 1];
            cout << "\n";
        }
    }


     for (int iter = 0; iter < 1; iter++){
        for (int cl = 0; cl < column - 1; cl++){
            cout << "Введите координаты точки: ";
            std::cin >> proverka[iter][cl] >> proverka[iter][cl + 1];
            cout << "\n";
        }
    }
    // выше фигуры
    int counter1 = 0;
    for (int k = 0; k < 1; k++){
        int prover = proverka[k][k + 1];
        for (int i = 0; i < line; i++){
            for (int j = 0; j < column - 1; j++){
                if (proverka[k][k] > figura[i][j]){
                    counter1++;
                }
            }
        }
    }


    int counter2 = 0;
    for (int k = 0; k < 1; k++){
        int prover = proverka[k][k + 1];
        for (int i = 0; i < line; i++){
            for (int j = 0; j < column - 1; j++){
                if (proverka[k][k] < figura[i][j]){
                    counter2++;
                }
            }
        }
    }


    int counter3 = 0;
    for (int k = 0; k < 1; k++){
        int prover = proverka[k][k + 1];
        for (int i = 0; i < line; i++){
            for (int j = 0; j < column - 1; j++){
                if (proverka[k][k + 1] > figura[i][j + 1]){
                    counter3++;
                }
            }
        }
    }


    int counter4 = 0;
    for (int k = 0; k < 1; k++){
        int prover = proverka[k][k + 1];
        for (int i = 0; i < line; i++){
            for (int j = 0; j < column - 1; j++){
                if (proverka[k][k + 1] < figura[i][j + 1]){
                    counter4++;
                }
            }
        }
    }
    if (counter2 == line){
        cout << "Точка находится ниже фигуры\n";
    }
    else if (counter1 == line){
        cout << "Точка находится выше фигуры\n";
    }
    else if (counter3 == line){
        cout << "Точка находится правее фигуры\n";
    }
    else if (counter4 == line){
        cout << "Точка находится левее фигуры\n";
    }
    std :: vector<int> numbers_x;
    std :: vector<int> numbers_y;
    int lopi = 1;
    int array[lopi][lopi];
    if (counter1 != line){
        double minim = 1000.0;
        for (int j = 0; j < 1; j++){
        int x = proverka[j][j];
        int y = proverka[j][j + 1];
        for (int iter = 0 ; iter < line; iter++){
            for (int i = 0; i < column - 1; i++){
                double s = pow(((figura[iter][i] - x) * (figura[iter][i] - x)) + ((figura[iter][i + 1] - y) * (figura[iter][i + 1] - y)), 0.5);
                if (s != 0 and s < minim){
                    minim = s;
                    numbers_x.emplace_back(figura[iter][i]);
                    numbers_y.emplace_back(figura[iter][i + 1]);
                }
            }
        }

        }

        int jop = numbers_x.back();
        int jops = numbers_y.back();
        //std :: vector<int> numbers_x_x = {jop};
        //std :: vector<int> numbers_y_y = {jops};
        double minimum = 1000;
        int mon_x = 1000;
        int mon_y = 1000;
        for (int j = 0; j < 1; j++){
        int x = proverka[j][j];
        int y = proverka[j][j + 1];
        for (int iter = 0 ; iter < line; iter++){
            for (int i = 0; i < column - 1; i++){
                double s = pow(((figura[iter][i] - x) * (figura[iter][i] - x)) + ((figura[iter][i + 1] - y) * (figura[iter][i + 1] - y)), 0.5);
                if (s != 0 and s < minimum and figura[iter][i] != jop and figura[iter][i + 1] != jops){
                    minim = s;
                    mon_x = figura[iter][i];
                    mon_y = figura[iter][i + 1];
                }
            }
        }
        array[0][0] = mon_x; 
        array[0][1] = mon_y;
        }
    }
    cout << numbers_x.back() << " " << array[0][0] << "" << array[0][1] << "\n";
    if (numbers_x.back() > array[0][0] and numbers_y.back() > array[0][1]){
        cout << "Точка лежит вне фигуры\n";
    }
    else if (array[0][0] > numbers_x.back() and array[0][1] > numbers_y.back()){
        cout << "Точка лежит вне фигуры\n";
    }
    else{
        cout << "Точка лежит внутри фигуры\n";
    }
    return 0;

}