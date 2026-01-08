// Lab_04_2_variant31.cpp
// Янісів Максим
// Лабораторна робота 4.2
// Варіант 31: Табулювання функції y(x) на інтервалі [X_поч, X_кін] з кроком dX
// 4 способи: while, do-while, for(x+=dx), for(x-=dx)
//
// y = 2|13-x| - f(x), де:
//   f(x) = e^|x-5|,           якщо x ≤ -1
//   f(x) = sin²(x³) - 1,      якщо -1 < x < 1  
//   f(x) = cos|x| / (1+sin²x), якщо x ≥ 1

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
using namespace std;

const double EPSILON = 1e-9;

// Обчислення функції f(x) за умовою
double f(double x) {
    if (x <= -1.0) {
        return exp(fabs(x - 5.0));
    } else if (x < 1.0) {
        double sinx3 = sin(x * x * x);
        return sinx3 * sinx3 - 1.0;
    } else {
        double sinx = sin(x);
        return cos(fabs(x)) / (1.0 + sinx * sinx);
    }
}

// Обчислення y(x)
double y(double x) {
    return 2.0 * fabs(13.0 - x) - f(x);
}

// =====================================================
// СПОСІБ 1: while (…) { … }
// =====================================================
void tabulateWhile(double xStart, double xEnd, double dx) {
    cout << "\n=== Method 1: while ===" << endl;
    cout << "+------------+----------------------+" << endl;
    cout << "|     x      |         y(x)         |" << endl;
    cout << "+------------+----------------------+" << endl;
    
    double x = xStart;
    while (x <= xEnd + EPSILON) {
        cout << "| " << setw(10) << fixed << setprecision(4) << x 
             << " | " << setw(20) << setprecision(10) << y(x) << " |" << endl;
        x += dx;
    }
    cout << "+------------+----------------------+" << endl;
}

// =====================================================
// СПОСІБ 2: do { … } while (…);
// =====================================================
void tabulateDoWhile(double xStart, double xEnd, double dx) {
    cout << "\n=== Method 2: do-while ===" << endl;
    cout << "+------------+----------------------+" << endl;
    cout << "|     x      |         y(x)         |" << endl;
    cout << "+------------+----------------------+" << endl;
    
    double x = xStart;
    if (x <= xEnd + EPSILON) {
        do {
            cout << "| " << setw(10) << fixed << setprecision(4) << x 
                 << " | " << setw(20) << setprecision(10) << y(x) << " |" << endl;
            x += dx;
        } while (x <= xEnd + EPSILON);
    }
    cout << "+------------+----------------------+" << endl;
}

// =====================================================
// СПОСІБ 3: for (x += dx) - від початку до кінця
// =====================================================
void tabulateForInc(double xStart, double xEnd, double dx) {
    cout << "\n=== Method 3: for (x += dx) ===" << endl;
    cout << "+------------+----------------------+" << endl;
    cout << "|     x      |         y(x)         |" << endl;
    cout << "+------------+----------------------+" << endl;
    
    for (double x = xStart; x <= xEnd + EPSILON; x += dx) {
        cout << "| " << setw(10) << fixed << setprecision(4) << x 
             << " | " << setw(20) << setprecision(10) << y(x) << " |" << endl;
    }
    cout << "+------------+----------------------+" << endl;
}

// =====================================================
// СПОСІБ 4: for (x -= dx) - від кінця до початку
// =====================================================
void tabulateForDec(double xStart, double xEnd, double dx) {
    cout << "\n=== Method 4: for (x -= dx) [reverse] ===" << endl;
    cout << "+------------+----------------------+" << endl;
    cout << "|     x      |         y(x)         |" << endl;
    cout << "+------------+----------------------+" << endl;
    
    for (double x = xEnd; x >= xStart - EPSILON; x -= dx) {
        cout << "| " << setw(10) << fixed << setprecision(4) << x 
             << " | " << setw(20) << setprecision(10) << y(x) << " |" << endl;
    }
    cout << "+------------+----------------------+" << endl;
}

// =====================================================
// UNIT TESTS
// =====================================================

bool approxEqual(double a, double b, double eps = 1e-6) {
    return fabs(a - b) < eps;
}

void test_f() {
    cout << "Testing f(x)..." << endl;
    
    // x ≤ -1: f(x) = e^|x-5|
    double f_neg2 = f(-2.0);
    double expected_neg2 = exp(fabs(-2.0 - 5.0));  // e^7
    assert(approxEqual(f_neg2, expected_neg2));
    cout << "  f(-2) = e^7 = " << f_neg2 << " [PASS]" << endl;
    
    // -1 < x < 1: f(x) = sin²(x³) - 1
    double f_0 = f(0.0);
    double expected_0 = sin(0.0) * sin(0.0) - 1.0;  // -1
    assert(approxEqual(f_0, expected_0));
    cout << "  f(0) = sin²(0) - 1 = " << f_0 << " [PASS]" << endl;
    
    double f_05 = f(0.5);
    double sin_cube = sin(0.5 * 0.5 * 0.5);
    double expected_05 = sin_cube * sin_cube - 1.0;
    assert(approxEqual(f_05, expected_05));
    cout << "  f(0.5) = sin²(0.125) - 1 = " << f_05 << " [PASS]" << endl;
    
    // x ≥ 1: f(x) = cos|x| / (1 + sin²x)
    double f_2 = f(2.0);
    double sin2 = sin(2.0);
    double expected_2 = cos(2.0) / (1.0 + sin2 * sin2);
    assert(approxEqual(f_2, expected_2));
    cout << "  f(2) = cos(2)/(1+sin²(2)) = " << f_2 << " [PASS]" << endl;
    
    cout << "All f(x) tests PASSED!" << endl << endl;
}

void test_y() {
    cout << "Testing y(x) = 2|13-x| - f(x)..." << endl;
    
    double y_0 = y(0.0);
    double expected_y0 = 2.0 * fabs(13.0 - 0.0) - f(0.0);
    assert(approxEqual(y_0, expected_y0));
    cout << "  y(0) = 2*13 - (-1) = " << y_0 << " [PASS]" << endl;
    
    double y_5 = y(5.0);
    double expected_y5 = 2.0 * fabs(13.0 - 5.0) - f(5.0);
    assert(approxEqual(y_5, expected_y5));
    cout << "  y(5) = " << y_5 << " [PASS]" << endl;
    
    cout << "All y(x) tests PASSED!" << endl << endl;
}

void run_all_tests() {
    cout << "========================================" << endl;
    cout << "         RUNNING UNIT TESTS            " << endl;
    cout << "========================================" << endl << endl;
    
    test_f();
    test_y();
    
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
    cout << "       Variant 31 - Lab 4.2            " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Function: y = 2|13-x| - f(x)" << endl;
    cout << "where:" << endl;
    cout << "  f(x) = e^|x-5|,           if x <= -1" << endl;
    cout << "  f(x) = sin^2(x^3) - 1,    if -1 < x < 1" << endl;
    cout << "  f(x) = cos|x|/(1+sin^2x), if x >= 1" << endl;
    cout << endl;
    
    double xStart, xEnd, dx;
    
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
    cout << "Tabulating y(x) on [" << xStart << ", " << xEnd << "] with step " << dx << endl;
    
    // 4 способи табулювання
    tabulateWhile(xStart, xEnd, dx);
    tabulateDoWhile(xStart, xEnd, dx);
    tabulateForInc(xStart, xEnd, dx);
    tabulateForDec(xStart, xEnd, dx);
    
    cout << endl;
    cout << "========================================" << endl;
    cout << "All 4 methods show the same y(x) values!" << endl;
    cout << "========================================" << endl;
    
    return 0;
}
