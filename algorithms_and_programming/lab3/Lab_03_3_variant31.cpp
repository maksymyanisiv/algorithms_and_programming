// Lab_03_3_variant31.cpp
// Янісів Максим
// Лабораторна робота 3.3
// Функція задана графіком
// Варіант 31

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double x, R;    // вхідні параметри
    double y;       // результат
    
    cout << "========================================" << endl;
    cout << "       Variant 31 - Lab 3.3            " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Function defined by graph:" << endl;
    cout << "  y = x + 1 + R,              x < -1-R" << endl;
    cout << "  y = sqrt(R^2 - (x+1)^2),    -1-R <= x <= -1" << endl;
    cout << "  y = R,                      -1 < x <= 1" << endl;
    cout << "  y = R - (R+1)*(x-1),        1 < x <= 2" << endl;
    cout << "  y = -1,                     x > 2" << endl;
    cout << endl;
    
    cout << "Enter R: ";
    cin >> R;
    
    if (R <= 0) {
        cout << "Error: R must be positive!" << endl;
        cin.get();
        cin.get();
        return 1;
    }
    
    cout << "Enter x: ";
    cin >> x;
    cout << endl;
    
    // Обчислення функції за графіком
    if (x < -1 - R) {
        // Пряма під кутом 45°
        y = x + 1 + R;
    }
    else if (x <= -1) {
        // Дуга кола з центром (-1, 0) і радіусом R
        y = sqrt(R * R - (x + 1) * (x + 1));
    }
    else if (x <= 1) {
        // Горизонтальна лінія на рівні R
        y = R;
    }
    else if (x <= 2) {
        // Похила лінія від (1, R) до (2, -1)
        y = R - (R + 1) * (x - 1);
    }
    else {
        // Горизонтальна лінія на рівні -1
        y = -1;
    }
    
    cout << "========================================" << endl;
    cout << "Input:" << endl;
    cout << "  R = " << R << endl;
    cout << "  x = " << x << endl;
    cout << endl;
    cout << "Result:" << endl;
    cout << "  y = " << y << endl;
    cout << "========================================" << endl;
    
    cin.get();
    cin.get();
    return 0;
}

