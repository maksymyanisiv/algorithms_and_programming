// Lab_03_4_variant31.cpp
// Янісів Максим
// Лабораторна робота 3.4
// Визначення попадання точки в область
// Варіант 31

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double x, y, R;
    bool inQuarterCircle, inTriangle, inArea;
    
    cout << "========================================" << endl;
    cout << "       Variant 31 - Lab 3.4            " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Gray area consists of:" << endl;
    cout << "  1) Quarter circle (1st quadrant):" << endl;
    cout << "     x >= 0, y >= 0, x^2 + y^2 <= R^2" << endl;
    cout << "  2) Triangle (3rd quadrant):" << endl;
    cout << "     x <= 0, y <= 0, x + y >= -R" << endl;
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
    cout << "Enter y: ";
    cin >> y;
    cout << endl;
    
    // Перевірка чверті кола (перший квадрант)
    inQuarterCircle = (x >= 0) && (y >= 0) && (x * x + y * y <= R * R);
    
    // Перевірка трикутника (третій квадрант)
    inTriangle = (x <= 0) && (y <= 0) && (x + y >= -R);
    
    // Точка в сірій області, якщо вона в будь-якій з частин
    inArea = inQuarterCircle || inTriangle;
    
    cout << "========================================" << endl;
    cout << "Input:" << endl;
    cout << "  R = " << R << endl;
    cout << "  Point: (" << x << ", " << y << ")" << endl;
    cout << endl;
    cout << "Analysis:" << endl;
    cout << "  In quarter circle: " << (inQuarterCircle ? "Yes" : "No") << endl;
    cout << "  In triangle: " << (inTriangle ? "Yes" : "No") << endl;
    cout << endl;
    cout << "Result:" << endl;
    
    if (inArea) {
        cout << "  Point IS INSIDE the gray area" << endl;
    }
    else {
        cout << "  Point is OUTSIDE the gray area" << endl;
    }
    
    cout << "========================================" << endl;
    
    cin.get();
    cin.get();
    return 0;
}

