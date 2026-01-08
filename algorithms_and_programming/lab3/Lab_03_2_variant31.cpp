// Lab_03_2_variant31.cpp
// Янісів Максим
// Лабораторна робота 3.2
// Розгалужені програми
// Варіант 31

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double a, b, c, x;  // вхідні параметри
    double F1;          // результат (скорочена форма)
    double F2;          // результат (повна форма)
    bool error1 = false, error2 = false;
    
    cout << "========================================" << endl;
    cout << "       Variant 31 - Lab 3.2            " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "F = a*x^2 + b/c,      if x < 1 and c != 0" << endl;
    cout << "F = (x-a)/(x-c)^2,    if x > 1.5 and c = 0" << endl;
    cout << "F = x^2/c^2,          otherwise" << endl;
    cout << endl;
    
    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;
    cout << "Enter c: ";
    cin >> c;
    cout << "Enter x: ";
    cin >> x;
    cout << endl;
    
    // =====================================================
    // СПОСІБ 1: Скорочена форма (if без else)
    // =====================================================
    cout << "--- Method 1: Short form (if only) ---" << endl;
    
    F1 = 0;
    
    // Умова 1: x < 1 і c != 0
    if (x < 1 && c != 0) {
        F1 = a * x * x + b / c;
    }
    
    // Умова 2: x > 1.5 і c = 0
    if (x > 1.5 && c == 0) {
        if (x == 0) {
            cout << "Error: division by zero (x = 0)" << endl;
            error1 = true;
        }
        if (x != 0) {
            F1 = (x - a) / ((x - c) * (x - c));
        }
    }
    
    // Умова 3: в інших випадках
    if (!((x < 1 && c != 0) || (x > 1.5 && c == 0))) {
        if (c == 0) {
            cout << "Error: division by zero (c = 0)" << endl;
            error1 = true;
        }
        if (c != 0) {
            F1 = (x * x) / (c * c);
        }
    }
    
    if (!error1) {
        cout << "F1 = " << F1 << endl;
    }
    cout << endl;
    
    // =====================================================
    // СПОСІБ 2: Повна форма (if-else)
    // =====================================================
    cout << "--- Method 2: Full form (if-else) ---" << endl;
    
    // Умова 1: x < 1 і c != 0
    if (x < 1 && c != 0) {
        F2 = a * x * x + b / c;
    }
    // Умова 2: x > 1.5 і c = 0
    else if (x > 1.5 && c == 0) {
        if (x == 0) {
            cout << "Error: division by zero (x = 0)" << endl;
            error2 = true;
        }
        else {
            F2 = (x - a) / ((x - c) * (x - c));
        }
    }
    // Умова 3: в інших випадках
    else {
        if (c == 0) {
            cout << "Error: division by zero (c = 0)" << endl;
            error2 = true;
        }
        else {
            F2 = (x * x) / (c * c);
        }
    }
    
    if (!error2) {
        cout << "F2 = " << F2 << endl;
    }
    cout << endl;
    
    // =====================================================
    // Перевірка збігу результатів
    // =====================================================
    cout << "========================================" << endl;
    cout << "Verification:" << endl;
    
    if (!error1 && !error2) {
        cout << "F1 = " << F1 << endl;
        cout << "F2 = " << F2 << endl;
        cout << "Difference: F1 - F2 = " << F1 - F2 << endl;
        
        if (F1 == F2) {
            cout << "Results MATCH!" << endl;
        }
        else {
            cout << "Results DO NOT match!" << endl;
        }
    }
    else {
        cout << "Cannot compare due to errors." << endl;
    }
    cout << "========================================" << endl;
    
    cin.get();
    cin.get();
    return 0;
}

