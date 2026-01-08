// Lab_04_4_variant31.cpp
// Янісів Максим
// Лабораторна робота 4.4
// Варіант 31: Табулювання функції, заданої графічно
// 4 способи: while, do-while, for(x+=dx), for(x-=dx)
//
// Графік функції:
// 1. x ≤ -1:      y = x + R + 1  (лінія під 45°)
// 2. -1 < x ≤ 0:  y = √(R² - x²) (дуга кола, центр (0,0), радіус R)
// 3. 0 < x ≤ 1:   y = R          (горизонтальна лінія)
// 4. 1 < x ≤ 2:   y = R - (R+1)(x-1) = 2R+1 - (R+1)x (похила лінія)
// 5. x > 2:       y = -1         (горизонтальна лінія)

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
using namespace std;

const double EPSILON = 1e-9;

double F(double x, double R) {
    if (x <= -1.0 + EPSILON) {
        return x + R + 1.0;
    } else if (x <= 0.0 + EPSILON) {
        double val = R * R - x * x;
        if (val < 0) val = 0;
        return sqrt(val);
    } else if (x <= 1.0 + EPSILON) {
        return R;
    } else if (x <= 2.0 + EPSILON) {
        return 2.0 * R + 1.0 - (R + 1.0) * x;
    } else {
        return -1.0;
    }
}

string getRegion(double x) {
    if (x <= -1.0 + EPSILON) {
        return "x+R+1";
    } else if (x <= 0.0 + EPSILON) {
        return "sqrt(R^2-x^2)";
    } else if (x <= 1.0 + EPSILON) {
        return "R";
    } else if (x <= 2.0 + EPSILON) {
        return "2R+1-(R+1)x";
    } else {
        return "-1";
    }
}

// =====================================================
// СПОСІБ 1: while
// =====================================================
void tabulateWhile(double xStart, double xEnd, double dx, double R) {
    cout << "\n=== Спосіб 1: while ===" << endl;
    cout << "+----------+----------------+------------------+" << endl;
    cout << "|    x     |      y(x)      |     Формула      |" << endl;
    cout << "+----------+----------------+------------------+" << endl;
    
    double x = xStart;
    while (x <= xEnd + EPSILON) {
        double y = F(x, R);
        cout << "| " << setw(8) << fixed << setprecision(3) << x << " | ";
        cout << setw(14) << setprecision(6) << y << " | ";
        cout << setw(16) << getRegion(x) << " |" << endl;
        x += dx;
    }
    cout << "+----------+----------------+------------------+" << endl;
}

// =====================================================
// СПОСІБ 2: do-while
// =====================================================
void tabulateDoWhile(double xStart, double xEnd, double dx, double R) {
    cout << "\n=== Спосіб 2: do-while ===" << endl;
    cout << "+----------+----------------+------------------+" << endl;
    cout << "|    x     |      y(x)      |     Формула      |" << endl;
    cout << "+----------+----------------+------------------+" << endl;
    
    double x = xStart;
    if (x <= xEnd + EPSILON) {
        do {
            double y = F(x, R);
            cout << "| " << setw(8) << fixed << setprecision(3) << x << " | ";
            cout << setw(14) << setprecision(6) << y << " | ";
            cout << setw(16) << getRegion(x) << " |" << endl;
            x += dx;
        } while (x <= xEnd + EPSILON);
    }
    cout << "+----------+----------------+------------------+" << endl;
}

// =====================================================
// СПОСІБ 3: for (x += dx)
// =====================================================
void tabulateForInc(double xStart, double xEnd, double dx, double R) {
    cout << "\n=== Спосіб 3: for (x += dx) ===" << endl;
    cout << "+----------+----------------+------------------+" << endl;
    cout << "|    x     |      y(x)      |     Формула      |" << endl;
    cout << "+----------+----------------+------------------+" << endl;
    
    for (double x = xStart; x <= xEnd + EPSILON; x += dx) {
        double y = F(x, R);
        cout << "| " << setw(8) << fixed << setprecision(3) << x << " | ";
        cout << setw(14) << setprecision(6) << y << " | ";
        cout << setw(16) << getRegion(x) << " |" << endl;
    }
    cout << "+----------+----------------+------------------+" << endl;
}

// =====================================================
// СПОСІБ 4: for (x -= dx) - зворотній порядок
// =====================================================
void tabulateForDec(double xStart, double xEnd, double dx, double R) {
    cout << "\n=== Спосіб 4: for (x -= dx) [зворотній] ===" << endl;
    cout << "+----------+----------------+------------------+" << endl;
    cout << "|    x     |      y(x)      |     Формула      |" << endl;
    cout << "+----------+----------------+------------------+" << endl;
    
    for (double x = xEnd; x >= xStart - EPSILON; x -= dx) {
        double y = F(x, R);
        cout << "| " << setw(8) << fixed << setprecision(3) << x << " | ";
        cout << setw(14) << setprecision(6) << y << " | ";
        cout << setw(16) << getRegion(x) << " |" << endl;
    }
    cout << "+----------+----------------+------------------+" << endl;
}

// =====================================================
// UNIT TESTS
// =====================================================

void test_F() {
    cout << "Testing F(x, R)..." << endl;
    double R = 1.0;
    
    // Тест 1: x = -2 (область 1: x ≤ -1)
    double y1 = F(-2.0, R);
    double expected1 = -2.0 + 1.0 + 1.0;  // 0
    assert(fabs(y1 - expected1) < 1e-6);
    cout << "  F(-2, R=1) = " << y1 << " [x+R+1] PASS" << endl;
    
    // Тест 2: x = -1 (межа областей 1-2)
    double y2 = F(-1.0, R);
    double expected2 = -1.0 + 1.0 + 1.0;  // 1 = R
    assert(fabs(y2 - expected2) < 1e-6);
    cout << "  F(-1, R=1) = " << y2 << " [x+R+1] PASS" << endl;
    
    // Тест 3: x = -0.5 (область 2: дуга)
    double y3 = F(-0.5, R);
    double expected3 = sqrt(1.0 - 0.25);  // sqrt(0.75) ≈ 0.866
    assert(fabs(y3 - expected3) < 1e-6);
    cout << "  F(-0.5, R=1) = " << y3 << " [sqrt(R^2-x^2)] PASS" << endl;
    
    // Тест 4: x = 0 (межа областей 2-3)
    double y4 = F(0.0, R);
    double expected4 = R;  // 1
    assert(fabs(y4 - expected4) < 1e-6);
    cout << "  F(0, R=1) = " << y4 << " [sqrt(R^2-x^2)=R] PASS" << endl;
    
    // Тест 5: x = 0.5 (область 3: y = R)
    double y5 = F(0.5, R);
    double expected5 = R;  // 1
    assert(fabs(y5 - expected5) < 1e-6);
    cout << "  F(0.5, R=1) = " << y5 << " [R] PASS" << endl;
    
    // Тест 6: x = 1 (межа областей 3-4)
    double y6 = F(1.0, R);
    double expected6 = R;  // 1
    assert(fabs(y6 - expected6) < 1e-6);
    cout << "  F(1, R=1) = " << y6 << " [R] PASS" << endl;
    
    // Тест 7: x = 1.5 (область 4: похила лінія)
    double y7 = F(1.5, R);
    double expected7 = 2.0 * R + 1.0 - (R + 1.0) * 1.5;  // 3 - 3 = 0
    assert(fabs(y7 - expected7) < 1e-6);
    cout << "  F(1.5, R=1) = " << y7 << " [2R+1-(R+1)x] PASS" << endl;
    
    // Тест 8: x = 2 (межа областей 4-5)
    double y8 = F(2.0, R);
    double expected8 = 2.0 * R + 1.0 - (R + 1.0) * 2.0;  // 3 - 4 = -1
    assert(fabs(y8 - expected8) < 1e-6);
    cout << "  F(2, R=1) = " << y8 << " [2R+1-(R+1)x=-1] PASS" << endl;
    
    // Тест 9: x = 3 (область 5: y = -1)
    double y9 = F(3.0, R);
    double expected9 = -1.0;
    assert(fabs(y9 - expected9) < 1e-6);
    cout << "  F(3, R=1) = " << y9 << " [-1] PASS" << endl;
    
    cout << "All F() tests PASSED!" << endl << endl;
}

void run_all_tests() {
    cout << "========================================" << endl;
    cout << "         RUNNING UNIT TESTS            " << endl;
    cout << "========================================" << endl << endl;
    
    test_F();
    
    cout << "========================================" << endl;
    cout << "      ALL TESTS PASSED!                " << endl;
    cout << "========================================" << endl << endl;
}

// =====================================================
// MAIN PROGRAM
// =====================================================

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "--test") {
        run_all_tests();
        return 0;
    }
    
    cout << "========================================" << endl;
    cout << "       Варіант 31 - Lab 4.4            " << endl;
    cout << "  Функція, задана графічно             " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Графік функції y(x):" << endl;
    cout << "  x <= -1:      y = x + R + 1      (лінія 45°)" << endl;
    cout << "  -1 < x <= 0:  y = sqrt(R^2-x^2)  (дуга кола)" << endl;
    cout << "  0 < x <= 1:   y = R              (горизонталь)" << endl;
    cout << "  1 < x <= 2:   y = 2R+1-(R+1)x    (похила)" << endl;
    cout << "  x > 2:        y = -1             (горизонталь)" << endl;
    cout << endl;
    
    double R, xStart, xEnd, dx;
    
    cout << "Введіть R: ";
    cin >> R;
    cout << "Введіть X_поч: ";
    cin >> xStart;
    cout << "Введіть X_кін: ";
    cin >> xEnd;
    cout << "Введіть dX (крок): ";
    cin >> dx;
    
    if (dx <= 0) {
        cout << "Помилка: крок має бути додатним!" << endl;
        return 1;
    }
    
    if (xStart > xEnd) {
        swap(xStart, xEnd);
        cout << "(поміняно: xStart=" << xStart << ", xEnd=" << xEnd << ")" << endl;
    }
    
    cout << endl;
    cout << "Параметри: R=" << R << endl;
    cout << "Табулювання y(x) на [" << xStart << ", " << xEnd << "] з кроком " << dx << endl;
    
    // 4 способи табулювання
    tabulateWhile(xStart, xEnd, dx, R);
    tabulateDoWhile(xStart, xEnd, dx, R);
    tabulateForInc(xStart, xEnd, dx, R);
    tabulateForDec(xStart, xEnd, dx, R);
    
    cout << endl;
    cout << "========================================" << endl;
    cout << "Всі 4 методи дають однакові значення y(x)!" << endl;
    cout << "========================================" << endl;
    
    return 0;
}
