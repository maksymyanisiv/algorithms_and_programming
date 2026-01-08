// Lab_04_1_variant31.cpp
// Янісів Максим
// Лабораторна робота 4.1
// Варіант 31: Обчислити добуток П(i=1..15) (sin²i + cos²(1/i)) / i²
// 4 способи: while, do-while, for(n++), for(n--)

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
using namespace std;

const int N = 15;
const double EPSILON = 1e-15;

// Обчислення одного члена добутку
double term(int i) {
    double sini = sin(static_cast<double>(i));
    double cosi_inv = cos(1.0 / i);
    return (sini * sini + cosi_inv * cosi_inv) / (i * i);
}

// =====================================================
// СПОСІБ 1: while (…) { … }
// =====================================================
double productWhile(int n) {
    double product = 1.0;
    int i = 1;
    while (i <= n) {
        product *= term(i);
        i++;
    }
    return product;
}

// =====================================================
// СПОСІБ 2: do { … } while (…);
// =====================================================
double productDoWhile(int n) {
    if (n < 1) return 1.0;
    
    double product = 1.0;
    int i = 1;
    do {
        product *= term(i);
        i++;
    } while (i <= n);
    return product;
}

// =====================================================
// СПОСІБ 3: for (…; …; n++) { … }
// =====================================================
double productForInc(int n) {
    double product = 1.0;
    for (int i = 1; i <= n; i++) {
        product *= term(i);
    }
    return product;
}

// =====================================================
// СПОСІБ 4: for (…; …; n--) { … }
// =====================================================
double productForDec(int n) {
    double product = 1.0;
    for (int i = n; i >= 1; i--) {
        product *= term(i);
    }
    return product;
}

// =====================================================
// UNIT TESTS
// =====================================================

bool approxEqual(double a, double b, double eps = EPSILON) {
    return fabs(a - b) < eps;
}

void test_term() {
    cout << "Testing term(i)..." << endl;
    
    // term(1) = (sin²(1) + cos²(1)) / 1
    double t1 = term(1);
    double expected1 = (sin(1.0) * sin(1.0) + cos(1.0) * cos(1.0)) / 1.0;
    assert(approxEqual(t1, expected1));
    cout << "  term(1) = " << t1 << " [PASS]" << endl;
    
    // term(2) = (sin²(2) + cos²(0.5)) / 4
    double t2 = term(2);
    double expected2 = (sin(2.0) * sin(2.0) + cos(0.5) * cos(0.5)) / 4.0;
    assert(approxEqual(t2, expected2));
    cout << "  term(2) = " << t2 << " [PASS]" << endl;
    
    cout << "All term() tests PASSED!" << endl << endl;
}

void test_all_methods() {
    cout << "Testing all 4 methods produce same result..." << endl;
    
    double r1 = productWhile(N);
    double r2 = productDoWhile(N);
    double r3 = productForInc(N);
    double r4 = productForDec(N);
    
    cout << "  Method 1 (while):      " << scientific << setprecision(15) << r1 << endl;
    cout << "  Method 2 (do-while):   " << r2 << endl;
    cout << "  Method 3 (for i++):    " << r3 << endl;
    cout << "  Method 4 (for i--):    " << r4 << endl;
    
    assert(approxEqual(r1, r2));
    assert(approxEqual(r2, r3));
    assert(approxEqual(r3, r4));
    
    cout << "All 4 methods produce SAME result! [PASS]" << endl << endl;
}

void test_small_n() {
    cout << "Testing with small n values..." << endl;
    
    // n = 1
    double t1 = term(1);
    assert(approxEqual(productWhile(1), t1));
    assert(approxEqual(productDoWhile(1), t1));
    assert(approxEqual(productForInc(1), t1));
    assert(approxEqual(productForDec(1), t1));
    cout << "  n = 1: All methods match [PASS]" << endl;
    
    // n = 3
    double expected3 = term(1) * term(2) * term(3);
    assert(approxEqual(productWhile(3), expected3));
    assert(approxEqual(productDoWhile(3), expected3));
    assert(approxEqual(productForInc(3), expected3));
    assert(approxEqual(productForDec(3), expected3));
    cout << "  n = 3: All methods match [PASS]" << endl;
    
    cout << "All small n tests PASSED!" << endl << endl;
}

void run_all_tests() {
    cout << "========================================" << endl;
    cout << "         RUNNING UNIT TESTS            " << endl;
    cout << "========================================" << endl << endl;
    
    test_term();
    test_small_n();
    test_all_methods();
    
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
    cout << "       Variant 31 - Lab 4.1            " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Formula: Product(i=1.." << N << ") (sin^2(i) + cos^2(1/i)) / i^2" << endl;
    cout << endl;
    cout << "4 loop methods: while, do-while, for(i++), for(i--)" << endl;
    cout << endl;
    
    // Обчислення 4-ма способами
    double r1 = productWhile(N);
    double r2 = productDoWhile(N);
    double r3 = productForInc(N);
    double r4 = productForDec(N);
    
    // Виведення результатів
    cout << "+---------------------------------------------+" << endl;
    cout << "| Method              | Result                |" << endl;
    cout << "+---------------------------------------------+" << endl;
    cout << "| 1. while            | " << setw(21) << scientific << setprecision(12) << r1 << " |" << endl;
    cout << "| 2. do-while         | " << setw(21) << r2 << " |" << endl;
    cout << "| 3. for (i++)        | " << setw(21) << r3 << " |" << endl;
    cout << "| 4. for (i--)        | " << setw(21) << r4 << " |" << endl;
    cout << "+---------------------------------------------+" << endl;
    cout << endl;
    
    // Перевірка збігу
    cout << "Verification: ";
    if (approxEqual(r1, r2) && approxEqual(r2, r3) && approxEqual(r3, r4)) {
        cout << "ALL 4 RESULTS MATCH!" << endl;
    } else {
        cout << "WARNING: Results do NOT match!" << endl;
    }
    
    // Виведення окремих членів
    cout << endl;
    cout << "Individual terms:" << endl;
    cout << "+------+------------------------+" << endl;
    cout << "|  i   |        term(i)         |" << endl;
    cout << "+------+------------------------+" << endl;
    for (int i = 1; i <= N; i++) {
        cout << "| " << setw(4) << i << " | " << setw(22) << term(i) << " |" << endl;
    }
    cout << "+------+------------------------+" << endl;
    
    cout << endl;
    cout << "========================================" << endl;
    
    return 0;
}
