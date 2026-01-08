// Lab_05_3_variant31.cpp
// Янісів Максим
// Лабораторна робота 5.3
// Табулювання функції з використанням допоміжних функцій
// Варіант 31

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
using namespace std;

// Рекурентне обчислення наступного доданка суми
// a_k = a_{k-1} * 4*x^2 / ((2k)*(2k-1))
double nextSumTerm(double prevTerm, int k, double x) {
    double x2 = x * x;
    return prevTerm * 4.0 * x2 / ((2.0 * k) * (2.0 * k - 1.0));
}

// Обчислення суми: sum(k=0..7) (2^(2k) * x^(2k)) / (2k)!
// з використанням рекурентного співвідношення
double calculateSum(double x) {
    double term = 1.0;  // a_0 = 1
    double sum = term;
    
    for (int k = 1; k <= 7; k++) {
        term = nextSumTerm(term, k, x);
        sum += term;
    }
    
    return sum;
}

// Функція j(x)
// j(x) = (sin(x) + 1) / (cos^2(x) + e^x),  якщо |x| >= 1
// j(x) = (1/cos(2x)) * sum(...),            якщо |x| < 1
double j(double x) {
    if (fabs(x) >= 1.0) {
        double sinx = sin(x);
        double cosx = cos(x);
        double ex = exp(x);
        return (sinx + 1.0) / (cosx * cosx + ex);
    }
    else {
        double cos2x = cos(2.0 * x);
        if (fabs(cos2x) < 1e-15) {
            return 0;  // захист від ділення на нуль
        }
        double sum = calculateSum(x);
        return sum / cos2x;
    }
}

// Основний вираз: j(k) + j^2(k-1) + 2*j(1)
double expression(double k) {
    double jk = j(k);
    double jk1 = j(k - 1.0);
    double j1 = j(1.0);
    
    return jk + jk1 * jk1 + 2.0 * j1;
}

// Виведення рядка таблиці
void printTableRow(double k, double result) {
    cout << "| " << setw(10) << fixed << setprecision(6) << k
         << " | " << setw(16) << setprecision(10) << result
         << " |" << endl;
}

// Виведення роздільника таблиці
void printTableSeparator() {
    cout << "+------------+------------------+" << endl;
}

// Виведення заголовка таблиці
void printTableHeader() {
    printTableSeparator();
    cout << "|     k      |     Result       |" << endl;
    printTableSeparator();
}

// Виведення таблиці значень
void printTable(double kStart, double kEnd, int n) {
    double dk = (kEnd - kStart) / n;
    
    cout << endl;
    cout << "Expression: j(k) + j^2(k-1) + 2*j(1)" << endl;
    cout << "where j(x) = (sin(x)+1)/(cos^2(x)+e^x), |x|>=1" << endl;
    cout << "      j(x) = (1/cos(2x))*sum(2^(2k)*x^(2k)/(2k)!), |x|<1" << endl;
    cout << endl;
    cout << "k from " << kStart << " to " << kEnd << ", n = " << n << " intervals" << endl;
    cout << "Step dk = " << dk << endl;
    cout << endl;
    
    printTableHeader();
    
    for (int i = 0; i <= n; i++) {
        double k = kStart + i * dk;
        double result = expression(k);
        printTableRow(k, result);
    }
    
    printTableSeparator();
}

// =====================================================
// UNIT TESTS
// =====================================================

const double EPSILON = 1e-9;

bool approxEqual(double a, double b, double eps = EPSILON) {
    return fabs(a - b) < eps;
}

void test_nextSumTerm() {
    cout << "Testing nextSumTerm() function..." << endl;
    
    double x = 0.5;
    double a0 = 1.0;
    
    // a_1 = 4*0.25/2 = 0.5 = 2^2 * 0.5^2 / 2! = 4*0.25/2 = 0.5 ✓
    double a1 = nextSumTerm(a0, 1, x);
    double expected1 = pow(2, 2) * pow(x, 2) / 2.0;  // 2! = 2
    assert(approxEqual(a1, expected1, 1e-10));
    cout << "  nextSumTerm(1, 1, 0.5) = " << a1 << " [PASS]" << endl;
    
    // a_2 = a_1 * 4*0.25 / (4*3) = 0.5 * 1/12 = 0.0416667
    // Expected: 2^4 * 0.5^4 / 4! = 16 * 0.0625 / 24 = 1/24 ≈ 0.0416667 ✓
    double a2 = nextSumTerm(a1, 2, x);
    double expected2 = pow(2, 4) * pow(x, 4) / 24.0;  // 4! = 24
    assert(approxEqual(a2, expected2, 1e-10));
    cout << "  nextSumTerm(a1, 2, 0.5) = " << a2 << " [PASS]" << endl;
    
    cout << "All nextSumTerm() tests PASSED!" << endl << endl;
}

void test_calculateSum() {
    cout << "Testing calculateSum() function..." << endl;
    
    // При x = 0: sum = 1 (тільки a_0 = 1, решта = 0)
    double sum0 = calculateSum(0);
    assert(approxEqual(sum0, 1.0));
    cout << "  calculateSum(0) = " << sum0 << " [PASS]" << endl;
    
    // Сума при x = 0.5 - порівняння з прямим обчисленням
    double sum05 = calculateSum(0.5);
    double expected = 0;
    for (int k = 0; k <= 7; k++) {
        expected += pow(2, 2*k) * pow(0.5, 2*k) / tgamma(2*k + 1);
    }
    assert(approxEqual(sum05, expected, 1e-8));
    cout << "  calculateSum(0.5) = " << sum05 << " [PASS]" << endl;
    
    cout << "All calculateSum() tests PASSED!" << endl << endl;
}

void test_j_function() {
    cout << "Testing j(x) function..." << endl;
    
    // Тест для |x| >= 1: j(2) = (sin(2)+1)/(cos^2(2)+e^2)
    double j2 = j(2.0);
    double expected2 = (sin(2.0) + 1.0) / (cos(2.0) * cos(2.0) + exp(2.0));
    assert(approxEqual(j2, expected2));
    cout << "  j(2) = " << j2 << " [PASS]" << endl;
    
    // Тест для |x| < 1: j(0.5)
    double j05 = j(0.5);
    double sum05 = calculateSum(0.5);
    double expected05 = sum05 / cos(1.0);
    assert(approxEqual(j05, expected05, 1e-8));
    cout << "  j(0.5) = " << j05 << " [PASS]" << endl;
    
    // Тест на границі: j(1) повинен використовувати першу формулу
    double j1 = j(1.0);
    double expected1 = (sin(1.0) + 1.0) / (cos(1.0) * cos(1.0) + exp(1.0));
    assert(approxEqual(j1, expected1));
    cout << "  j(1) = " << j1 << " [PASS]" << endl;
    
    // Тест j(-1)
    double jneg1 = j(-1.0);
    double expectedneg1 = (sin(-1.0) + 1.0) / (cos(-1.0) * cos(-1.0) + exp(-1.0));
    assert(approxEqual(jneg1, expectedneg1));
    cout << "  j(-1) = " << jneg1 << " [PASS]" << endl;
    
    cout << "All j(x) tests PASSED!" << endl << endl;
}

void test_expression() {
    cout << "Testing expression(k) function..." << endl;
    
    // expression(2) = j(2) + j^2(1) + 2*j(1)
    double result2 = expression(2.0);
    double j2 = j(2.0);
    double j1 = j(1.0);
    double expected2 = j2 + j1 * j1 + 2.0 * j1;
    assert(approxEqual(result2, expected2, 1e-8));
    cout << "  expression(2) = " << result2 << " [PASS]" << endl;
    
    cout << "All expression() tests PASSED!" << endl << endl;
}

void run_all_tests() {
    cout << "========================================" << endl;
    cout << "         RUNNING UNIT TESTS            " << endl;
    cout << "========================================" << endl << endl;
    
    test_nextSumTerm();
    test_calculateSum();
    test_j_function();
    test_expression();
    
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
    
    double kStart, kEnd;
    int n;
    
    cout << "========================================" << endl;
    cout << "       Variant 31 - Lab 5.3            " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Expression: j(k) + j^2(k-1) + 2*j(1)" << endl;
    cout << endl;
    cout << "j(x) = (sin(x)+1)/(cos^2(x)+e^x),      |x| >= 1" << endl;
    cout << "j(x) = (1/cos(2x))*SUM(2^2k*x^2k/(2k)!), |x| < 1" << endl;
    cout << "       (sum from k=0 to 7)" << endl;
    cout << endl;
    
    cout << "Enter k_start: ";
    cin >> kStart;
    cout << "Enter k_end: ";
    cin >> kEnd;
    cout << "Enter n (number of intervals): ";
    cin >> n;
    
    if (n <= 0) {
        cout << "Error: n must be positive!" << endl;
        return 1;
    }
    
    printTable(kStart, kEnd, n);
    
    cin.get();
    cin.get();
    return 0;
}

