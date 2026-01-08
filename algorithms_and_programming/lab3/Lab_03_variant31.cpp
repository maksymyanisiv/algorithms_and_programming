// Lab_03_variant31.cpp
// Янісів Максим
// Лабораторна робота 3.1
// Розгалужені програми
// Варіант 31

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double x;       // вхідний аргумент
    double y1;      // результат (скорочена форма)
    double y2;      // результат (повна форма)
    double f;       // допоміжна змінна для внутрішньої функції
    
    cout << "========================================" << endl;
    cout << "       Variant 31 - Lab 3.1            " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "y = 2*|13-x| - f(x), where:" << endl;
    cout << "  f(x) = e^|x-5|,           if x <= -1" << endl;
    cout << "  f(x) = sin^2(x^3) - 1,    if -1 < x < 1" << endl;
    cout << "  f(x) = cos|x|/(1+sin^2x), if x >= 1" << endl;
    cout << endl;
    
    cout << "Enter x: ";
    cin >> x;
    cout << endl;
    
    // =====================================================
    // СПОСІБ 1: Скорочена форма (if без else)
    // =====================================================
    cout << "--- Method 1: Short form (if only) ---" << endl;
    
    double f1 = 0;
    
    if (x <= -1) {
        f1 = exp(fabs(x - 5));
    }
    if (x > -1 && x < 1) {
        f1 = sin(x * x * x) * sin(x * x * x) - 1;
    }
    if (x >= 1) {
        f1 = cos(fabs(x)) / (1 + sin(x) * sin(x));
    }
    
    y1 = 2 * fabs(13 - x) - f1;
    
    cout << "f(x) = " << f1 << endl;
    cout << "y1 = " << y1 << endl;
    cout << endl;
    
    // =====================================================
    // СПОСІБ 2: Повна форма (if-else)
    // =====================================================
    cout << "--- Method 2: Full form (if-else) ---" << endl;
    
    double f2;
    
    if (x <= -1) {
        f2 = exp(fabs(x - 5));
    }
    else if (x < 1) {
        f2 = sin(x * x * x) * sin(x * x * x) - 1;
    }
    else {
        f2 = cos(fabs(x)) / (1 + sin(x) * sin(x));
    }
    
    y2 = 2 * fabs(13 - x) - f2;
    
    cout << "f(x) = " << f2 << endl;
    cout << "y2 = " << y2 << endl;
    cout << endl;
    
    // =====================================================
    // Перевірка збігу результатів
    // =====================================================
    cout << "========================================" << endl;
    cout << "Verification:" << endl;
    cout << "y1 = " << y1 << endl;
    cout << "y2 = " << y2 << endl;
    cout << "Difference: y1 - y2 = " << y1 - y2 << endl;
    
    if (y1 == y2) {
        cout << "Results MATCH!" << endl;
    }
    else {
        cout << "Results DO NOT match!" << endl;
    }
    cout << "========================================" << endl;
    
    cin.get();
    cin.get();
    return 0;
}
