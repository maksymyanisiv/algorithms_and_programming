// Lab_04_3_variant31.cpp
// Янісів Максим
// Лабораторна робота 4.3
// Варіант 31: Табулювання функції F(x) на інтервалі [X_поч, X_кін] з кроком dX
// 4 способи: while, do-while, for(x+=dx), for(x-=dx)
//
// F = { a*x² + b/c,        при x < 1 і c ≠ 0
//     { (x-a)/(x-c)²,      при x > 1.5 і c = 0
//     { x²/c²,             в інших випадках
//
// де a, b, c – дійсні числа

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
using namespace std;

const double EPSILON = 1e-9;

// Структура для зберігання параметрів
struct Params {
    double a, b, c;
};

// Перевірка чи число близьке до нуля
bool isZero(double val) {
    return fabs(val) < EPSILON;
}

// Обчислення функції F(x, a, b, c)
double F(double x, const Params& p) {
    if (x < 1.0 && !isZero(p.c)) {
        // x < 1 і c ≠ 0: F = a*x² + b/c
        return p.a * x * x + p.b / p.c;
    } else if (x > 1.5 && isZero(p.c)) {
        // x > 1.5 і c = 0: F = (x-a)/(x-c)² = (x-a)/x² (бо c=0)
        double denom = (x - p.c) * (x - p.c);
        if (isZero(denom)) {
            return NAN;  // ділення на нуль
        }
        return (x - p.a) / denom;
    } else {
        // в інших випадках: F = x²/c²
        if (isZero(p.c)) {
            return NAN;  // ділення на нуль
        }
        return (x * x) / (p.c * p.c);
    }
}

// Визначення області функції для виведення
string getRegion(double x, const Params& p) {
    if (x < 1.0 && !isZero(p.c)) {
        return "ax^2 + b/c";
    } else if (x > 1.5 && isZero(p.c)) {
        return "(x-a)/(x-c)^2";
    } else {
        return "x^2/c^2";
    }
}

// =====================================================
// СПОСІБ 1: while (…) { … }
// =====================================================
void tabulateWhile(double xStart, double xEnd, double dx, const Params& p) {
    cout << "\n=== Method 1: while ===" << endl;
    cout << "+------------+----------------------+------------------+" << endl;
    cout << "|     x      |         F(x)         |     Region       |" << endl;
    cout << "+------------+----------------------+------------------+" << endl;
    
    double x = xStart;
    while (x <= xEnd + EPSILON) {
        double fx = F(x, p);
        cout << "| " << setw(10) << fixed << setprecision(4) << x << " | ";
        if (isnan(fx)) {
            cout << setw(20) << "undefined";
        } else {
            cout << setw(20) << setprecision(8) << fx;
        }
        cout << " | " << setw(16) << getRegion(x, p) << " |" << endl;
        x += dx;
    }
    cout << "+------------+----------------------+------------------+" << endl;
}

// =====================================================
// СПОСІБ 2: do { … } while (…);
// =====================================================
void tabulateDoWhile(double xStart, double xEnd, double dx, const Params& p) {
    cout << "\n=== Method 2: do-while ===" << endl;
    cout << "+------------+----------------------+------------------+" << endl;
    cout << "|     x      |         F(x)         |     Region       |" << endl;
    cout << "+------------+----------------------+------------------+" << endl;
    
    double x = xStart;
    if (x <= xEnd + EPSILON) {
        do {
            double fx = F(x, p);
            cout << "| " << setw(10) << fixed << setprecision(4) << x << " | ";
            if (isnan(fx)) {
                cout << setw(20) << "undefined";
            } else {
                cout << setw(20) << setprecision(8) << fx;
            }
            cout << " | " << setw(16) << getRegion(x, p) << " |" << endl;
            x += dx;
        } while (x <= xEnd + EPSILON);
    }
    cout << "+------------+----------------------+------------------+" << endl;
}

// =====================================================
// СПОСІБ 3: for (x += dx)
// =====================================================
void tabulateForInc(double xStart, double xEnd, double dx, const Params& p) {
    cout << "\n=== Method 3: for (x += dx) ===" << endl;
    cout << "+------------+----------------------+------------------+" << endl;
    cout << "|     x      |         F(x)         |     Region       |" << endl;
    cout << "+------------+----------------------+------------------+" << endl;
    
    for (double x = xStart; x <= xEnd + EPSILON; x += dx) {
        double fx = F(x, p);
        cout << "| " << setw(10) << fixed << setprecision(4) << x << " | ";
        if (isnan(fx)) {
            cout << setw(20) << "undefined";
        } else {
            cout << setw(20) << setprecision(8) << fx;
        }
        cout << " | " << setw(16) << getRegion(x, p) << " |" << endl;
    }
    cout << "+------------+----------------------+------------------+" << endl;
}

// =====================================================
// СПОСІБ 4: for (x -= dx) - зворотній порядок
// =====================================================
void tabulateForDec(double xStart, double xEnd, double dx, const Params& p) {
    cout << "\n=== Method 4: for (x -= dx) [reverse] ===" << endl;
    cout << "+------------+----------------------+------------------+" << endl;
    cout << "|     x      |         F(x)         |     Region       |" << endl;
    cout << "+------------+----------------------+------------------+" << endl;
    
    for (double x = xEnd; x >= xStart - EPSILON; x -= dx) {
        double fx = F(x, p);
        cout << "| " << setw(10) << fixed << setprecision(4) << x << " | ";
        if (isnan(fx)) {
            cout << setw(20) << "undefined";
        } else {
            cout << setw(20) << setprecision(8) << fx;
        }
        cout << " | " << setw(16) << getRegion(x, p) << " |" << endl;
    }
    cout << "+------------+----------------------+------------------+" << endl;
}

// =====================================================
// UNIT TESTS
// =====================================================

void test_F() {
    cout << "Testing F(x, a, b, c)..." << endl;
    
    // Тест 1: x < 1, c ≠ 0 → F = ax² + b/c
    Params p1 = {2.0, 6.0, 3.0};  // a=2, b=6, c=3
    double f1 = F(0.5, p1);       // x=0.5 < 1
    double expected1 = 2.0 * 0.25 + 6.0 / 3.0;  // 0.5 + 2 = 2.5
    assert(fabs(f1 - expected1) < 1e-6);
    cout << "  F(0.5) with c!=0, x<1: " << f1 << " = " << expected1 << " [PASS]" << endl;
    
    // Тест 2: x > 1.5, c = 0 → F = (x-a)/(x-c)² = (x-a)/x²
    Params p2 = {1.0, 5.0, 0.0};  // c=0
    double f2 = F(2.0, p2);       // x=2.0 > 1.5
    double expected2 = (2.0 - 1.0) / (2.0 * 2.0);  // 1/4 = 0.25
    assert(fabs(f2 - expected2) < 1e-6);
    cout << "  F(2.0) with c=0, x>1.5: " << f2 << " = " << expected2 << " [PASS]" << endl;
    
    // Тест 3: інший випадок → F = x²/c²
    Params p3 = {1.0, 2.0, 2.0};  // c=2
    double f3 = F(1.2, p3);       // 1 ≤ x ≤ 1.5, c≠0
    double expected3 = (1.2 * 1.2) / (2.0 * 2.0);  // 1.44/4 = 0.36
    assert(fabs(f3 - expected3) < 1e-6);
    cout << "  F(1.2) other case: " << f3 << " = " << expected3 << " [PASS]" << endl;
    
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
    cout << "       Variant 31 - Lab 4.3            " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Function F(x, a, b, c):" << endl;
    cout << "  F = a*x^2 + b/c,      if x < 1 and c != 0" << endl;
    cout << "  F = (x-a)/(x-c)^2,    if x > 1.5 and c = 0" << endl;
    cout << "  F = x^2/c^2,          otherwise" << endl;
    cout << endl;
    
    Params p;
    double xStart, xEnd, dx;
    
    cout << "Enter parameters a, b, c: ";
    cin >> p.a >> p.b >> p.c;
    
    cout << "Enter X_start: ";
    cin >> xStart;
    cout << "Enter X_end: ";
    cin >> xEnd;
    cout << "Enter dX (step): ";
    cin >> dx;
    
    if (dx <= 0) {
        cout << "Error: step must be positive!" << endl;
        return 1;
    }
    
    if (xStart > xEnd) {
        swap(xStart, xEnd);
        cout << "(swapped: xStart=" << xStart << ", xEnd=" << xEnd << ")" << endl;
    }
    
    cout << endl;
    cout << "Parameters: a=" << p.a << ", b=" << p.b << ", c=" << p.c << endl;
    cout << "Tabulating F(x) on [" << xStart << ", " << xEnd << "] with step " << dx << endl;
    
    // 4 способи табулювання
    tabulateWhile(xStart, xEnd, dx, p);
    tabulateDoWhile(xStart, xEnd, dx, p);
    tabulateForInc(xStart, xEnd, dx, p);
    tabulateForDec(xStart, xEnd, dx, p);
    
    cout << endl;
    cout << "========================================" << endl;
    cout << "All 4 methods show the same F(x) values!" << endl;
    cout << "========================================" << endl;
    
    return 0;
}
