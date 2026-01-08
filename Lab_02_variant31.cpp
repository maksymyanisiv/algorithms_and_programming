// Lab_02_variant31.cpp
// Янісів Максим
// Лабораторна робота 2.1
// Лінійні програми.
// Варіант 31
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double alpha;  // вхідний параметр (кут в радіанах)
    double z1;     // результат обчислення 1-го виразу
    double z2;     // результат обчислення 2-го виразу
    
    cout << "Variant 31" << endl;
    cout << "z1 = (1 - 2*sin^2(alpha)) / (1 + sin(2*alpha))" << endl;
    cout << "z2 = (1 - tg(alpha)) / (1 + tg(alpha))" << endl;
    cout << endl;
    
    cout << "alpha (in radians) = "; 
    cin >> alpha;
    
    // z1 = (1 - 2*sin^2(alpha)) / (1 + sin(2*alpha))
    z1 = (1 - 2 * sin(alpha) * sin(alpha)) / (1 + sin(2 * alpha));
    
    // z2 = (1 - tg(alpha)) / (1 + tg(alpha))
    z2 = (1 - tan(alpha)) / (1 + tan(alpha));
    
    cout << endl;
    cout << "z1 = " << z1 << endl;
    cout << "z2 = " << z2 << endl;
    
    // Перевірка: z1 має дорівнювати z2 (тригонометрична тотожність)
    cout << endl;
    cout << "Verification: z1 - z2 = " << z1 - z2 << endl;
    
    cin.get();
    cin.get();
    return 0;
}

