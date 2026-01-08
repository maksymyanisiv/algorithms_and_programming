// Lab_05_2_variant31.cpp
// Янісів Максим
// Лабораторна робота 5.2
// Обчислення ряду Тейлора (Arcth x)
// Варіант 31

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
using namespace std;

// Рекурентне обчислення наступного доданка ряду
// a_n = a_{n-1} * (2n-1) / ((2n+1) * x^2)
double nextTerm(double prevTerm, int n, double x) {
    double x2 = x * x;
    return prevTerm * (2.0 * n - 1.0) / ((2.0 * n + 1.0) * x2);
}

// Обчислення суми ряду Тейлора для Arcth(x) з заданою точністю
// Повертає суму ряду, кількість доданків через параметр count
double taylorSum(double x, double eps, int& count) {
    if (fabs(x) <= 1) {
        count = 0;
        return 0;
    }
    
    double term = 1.0 / x;  // a_0 = 1/x
    double sum = term;
    count = 1;
    
    while (fabs(term) >= eps) {
        term = nextTerm(term, count, x);
        sum += term;
        count++;
        
        if (count > 1000) break;  // захист від зациклення
    }
    
    return sum;
}

// Точне значення Arcth(x) = 0.5 * ln((x+1)/(x-1)), |x| > 1
double arcthExact(double x) {
    if (fabs(x) <= 1) return 0;
    return 0.5 * log((x + 1.0) / (x - 1.0));
}

// Виведення рядка таблиці
void printTableRow(double x, double exact, double taylor, int count) {
    cout << "| " << setw(8) << fixed << setprecision(4) << x
         << " | " << setw(14) << setprecision(10) << exact
         << " | " << setw(14) << taylor
         << " | " << setw(6) << count << " |" << endl;
}

// Виведення роздільника таблиці
void printTableSeparator() {
    cout << "+----------+----------------+----------------+--------+" << endl;
}

// Виведення заголовка таблиці
void printTableHeader() {
    printTableSeparator();
    cout << "|    x     |   Arcth(x)     |   Taylor Sum   | Terms  |" << endl;
    printTableSeparator();
}

// Виведення таблиці значень
void printTable(double xmin, double xmax, double dx, double eps) {
    cout << endl;
    cout << "Taylor series: Arcth(x) = 1/x + 1/(3x^3) + 1/(5x^5) + ..." << endl;
    cout << "Condition: |x| > 1" << endl;
    cout << "Precision (eps): " << scientific << eps << fixed << endl;
    cout << endl;
    
    printTableHeader();
    
    for (double x = xmin; x <= xmax + dx/2; x += dx) {
        if (fabs(x) <= 1) {
            cout << "| " << setw(8) << setprecision(4) << x
                 << " |  (|x| <= 1, undefined)              |" << endl;
            continue;
        }
        
        int count;
        double taylor = taylorSum(x, eps, count);
        double exact = arcthExact(x);
        
        printTableRow(x, exact, taylor, count);
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

void test_nextTerm() {
    cout << "Testing nextTerm() function..." << endl;
    
    double x = 2.0;
    double a0 = 1.0 / x;  // 0.5
    
    // a_1 = 1/(3*x^3) = 1/(3*8) = 1/24 ≈ 0.0416667
    double a1 = nextTerm(a0, 1, x);
    assert(approxEqual(a1, 1.0 / 24.0, 1e-10));
    cout << "  nextTerm(a0, 1, 2) = " << a1 << " [PASS]" << endl;
    
    // a_2 = 1/(5*x^5) = 1/(5*32) = 1/160 = 0.00625
    double a2 = nextTerm(a1, 2, x);
    assert(approxEqual(a2, 1.0 / 160.0, 1e-10));
    cout << "  nextTerm(a1, 2, 2) = " << a2 << " [PASS]" << endl;
    
    cout << "All nextTerm() tests PASSED!" << endl << endl;
}

void test_arcthExact() {
    cout << "Testing arcthExact() function..." << endl;
    
    // arcth(2) = 0.5 * ln(3/1) = 0.5 * ln(3) ≈ 0.5493061443
    double result2 = arcthExact(2.0);
    double expected2 = 0.5 * log(3.0);
    assert(approxEqual(result2, expected2));
    cout << "  arcthExact(2) = " << result2 << " [PASS]" << endl;
    
    // arcth(3) = 0.5 * ln(4/2) = 0.5 * ln(2) ≈ 0.3465735903
    double result3 = arcthExact(3.0);
    double expected3 = 0.5 * log(2.0);
    assert(approxEqual(result3, expected3));
    cout << "  arcthExact(3) = " << result3 << " [PASS]" << endl;
    
    // arcth(-2) = 0.5 * ln(-1/-3) = 0.5 * ln(1/3) = -0.5 * ln(3) ≈ -0.5493061443
    double resultNeg2 = arcthExact(-2.0);
    double expectedNeg2 = -0.5 * log(3.0);
    assert(approxEqual(resultNeg2, expectedNeg2));
    cout << "  arcthExact(-2) = " << resultNeg2 << " [PASS]" << endl;
    
    cout << "All arcthExact() tests PASSED!" << endl << endl;
}

void test_taylorSum() {
    cout << "Testing taylorSum() function..." << endl;
    
    int count;
    double eps = 1e-10;
    
    // Порівняння з точним значенням для x = 2
    double taylor2 = taylorSum(2.0, eps, count);
    double exact2 = arcthExact(2.0);
    assert(approxEqual(taylor2, exact2, 1e-8));
    cout << "  taylorSum(2, 1e-10) = " << taylor2 << ", terms: " << count << " [PASS]" << endl;
    
    // Порівняння з точним значенням для x = 5
    double taylor5 = taylorSum(5.0, eps, count);
    double exact5 = arcthExact(5.0);
    assert(approxEqual(taylor5, exact5, 1e-8));
    cout << "  taylorSum(5, 1e-10) = " << taylor5 << ", terms: " << count << " [PASS]" << endl;
    
    // Для x = 0.5 (|x| < 1) має повернути 0
    double taylor05 = taylorSum(0.5, eps, count);
    assert(taylor05 == 0 && count == 0);
    cout << "  taylorSum(0.5, eps) = 0, terms: 0 [PASS] (|x| <= 1)" << endl;
    
    cout << "All taylorSum() tests PASSED!" << endl << endl;
}

void run_all_tests() {
    cout << "========================================" << endl;
    cout << "         RUNNING UNIT TESTS            " << endl;
    cout << "========================================" << endl << endl;
    
    test_nextTerm();
    test_arcthExact();
    test_taylorSum();
    
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
    
    double xmin, xmax, dx, eps;
    
    cout << "========================================" << endl;
    cout << "       Variant 31 - Lab 5.2            " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Arcth(x) = sum(1/((2n+1)*x^(2n+1))), n=0..inf" << endl;
    cout << "         = 1/x + 1/(3x^3) + 1/(5x^5) + ..." << endl;
    cout << "Condition: |x| > 1" << endl;
    cout << endl;
    
    cout << "Enter xmin (|xmin| > 1): ";
    cin >> xmin;
    cout << "Enter xmax: ";
    cin >> xmax;
    cout << "Enter dx (step): ";
    cin >> dx;
    cout << "Enter eps (precision): ";
    cin >> eps;
    
    if (dx <= 0) {
        cout << "Error: dx must be positive!" << endl;
        return 1;
    }
    
    printTable(xmin, xmax, dx, eps);
    
    cin.get();
    cin.get();
    return 0;
}

