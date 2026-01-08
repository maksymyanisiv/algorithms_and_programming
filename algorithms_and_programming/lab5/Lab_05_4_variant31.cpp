// Lab_05_4_variant31.cpp
// Янісів Максим
// Лабораторна робота 5.4
// Рекурсивні функції для обчислення добутку
// Варіант 31

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
using namespace std;

// Обчислення одного члена добутку: (sin²(i) + cos²(1/i)) / i²
double term(int i) {
    double sini = sin((double)i);
    double cosi_inv = cos(1.0 / i);
    return (sini * sini + cosi_inv * cosi_inv) / (i * i);
}

// =====================================================
// СПОСІБ 1: Рекурсивний спуск, параметр спадає (n -> 1)
// Обчислення на спуску: спочатку множимо, потім рекурсія
// =====================================================
double productDescentDesc(int n) {
    if (n < 1) return 1.0;
    return term(n) * productDescentDesc(n - 1);
}

// =====================================================
// СПОСІБ 2: Рекурсивний спуск, параметр зростає (1 -> n)
// Обчислення на спуску: спочатку множимо, потім рекурсія
// =====================================================
double productDescentAsc(int i, int n) {
    if (i > n) return 1.0;
    return term(i) * productDescentAsc(i + 1, n);
}

// =====================================================
// СПОСІБ 3: Рекурсивний підйом, параметр спадає (n -> 1)
// Обчислення на підйомі: спочатку рекурсія, потім множимо
// =====================================================
double productAscentDesc(int n) {
    if (n < 1) return 1.0;
    double result = productAscentDesc(n - 1);
    return result * term(n);
}

// =====================================================
// СПОСІБ 4: Рекурсивний підйом, параметр зростає (1 -> n)
// Обчислення на підйомі: спочатку рекурсія, потім множимо
// =====================================================
double productAscentAsc(int i, int n) {
    if (i > n) return 1.0;
    double result = productAscentAsc(i + 1, n);
    return result * term(i);
}

// =====================================================
// СПОСІБ 5: Ітеративний (для контролю)
// =====================================================
double productIterative(int n) {
    double product = 1.0;
    for (int i = 1; i <= n; i++) {
        product *= term(i);
    }
    return product;
}

// =====================================================
// UNIT TESTS
// =====================================================

const double EPSILON = 1e-12;

bool approxEqual(double a, double b, double eps = EPSILON) {
    return fabs(a - b) < eps;
}

void test_term() {
    cout << "Testing term(i) function..." << endl;
    
    // term(1) = (sin²(1) + cos²(1)) / 1 = sin²(1) + cos²(1)
    double t1 = term(1);
    double expected1 = sin(1.0) * sin(1.0) + cos(1.0) * cos(1.0);
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
    cout << "Testing all 5 methods produce same result..." << endl;
    
    int n = 15;
    
    double r1 = productDescentDesc(n);
    double r2 = productDescentAsc(1, n);
    double r3 = productAscentDesc(n);
    double r4 = productAscentAsc(1, n);
    double r5 = productIterative(n);
    
    cout << "  Method 1 (descent, desc): " << r1 << endl;
    cout << "  Method 2 (descent, asc):  " << r2 << endl;
    cout << "  Method 3 (ascent, desc):  " << r3 << endl;
    cout << "  Method 4 (ascent, asc):   " << r4 << endl;
    cout << "  Method 5 (iterative):     " << r5 << endl;
    
    assert(approxEqual(r1, r2));
    assert(approxEqual(r2, r3));
    assert(approxEqual(r3, r4));
    assert(approxEqual(r4, r5));
    
    cout << "All methods produce SAME result! [PASS]" << endl << endl;
}

void test_small_n() {
    cout << "Testing with small n values..." << endl;
    
    // n = 1: result = term(1)
    double t1 = term(1);
    assert(approxEqual(productDescentDesc(1), t1));
    assert(approxEqual(productDescentAsc(1, 1), t1));
    assert(approxEqual(productAscentDesc(1), t1));
    assert(approxEqual(productAscentAsc(1, 1), t1));
    assert(approxEqual(productIterative(1), t1));
    cout << "  n = 1: All methods = " << t1 << " [PASS]" << endl;
    
    // n = 3: result = term(1) * term(2) * term(3)
    double expected3 = term(1) * term(2) * term(3);
    assert(approxEqual(productDescentDesc(3), expected3));
    assert(approxEqual(productDescentAsc(1, 3), expected3));
    assert(approxEqual(productAscentDesc(3), expected3));
    assert(approxEqual(productAscentAsc(1, 3), expected3));
    assert(approxEqual(productIterative(3), expected3));
    cout << "  n = 3: All methods = " << expected3 << " [PASS]" << endl;
    
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
    cout << "       Variant 31 - Lab 5.4            " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Product: П(i=1..15) (sin^2(i) + cos^2(1/i)) / i^2" << endl;
    cout << endl;
    
    int n = 15;
    
    cout << "Computing product for n = " << n << endl;
    cout << endl;
    
    cout << "+------------------------------------------+----------------------+" << endl;
    cout << "| Method                                   | Result               |" << endl;
    cout << "+------------------------------------------+----------------------+" << endl;
    
    double r1 = productDescentDesc(n);
    cout << "| 1. Recursive descent, param descending   | " 
         << setw(20) << scientific << setprecision(12) << r1 << " |" << endl;
    
    double r2 = productDescentAsc(1, n);
    cout << "| 2. Recursive descent, param ascending    | " 
         << setw(20) << r2 << " |" << endl;
    
    double r3 = productAscentDesc(n);
    cout << "| 3. Recursive ascent, param descending    | " 
         << setw(20) << r3 << " |" << endl;
    
    double r4 = productAscentAsc(1, n);
    cout << "| 4. Recursive ascent, param ascending     | " 
         << setw(20) << r4 << " |" << endl;
    
    double r5 = productIterative(n);
    cout << "| 5. Iterative (control)                   | " 
         << setw(20) << r5 << " |" << endl;
    
    cout << "+------------------------------------------+----------------------+" << endl;
    cout << endl;
    
    // Перевірка збігу результатів
    cout << "Verification:" << endl;
    if (approxEqual(r1, r2) && approxEqual(r2, r3) && 
        approxEqual(r3, r4) && approxEqual(r4, r5)) {
        cout << "  All 5 results MATCH!" << endl;
    }
    else {
        cout << "  WARNING: Results do NOT match!" << endl;
    }
    
    cout << endl;
    cout << "========================================" << endl;
    
    // Показати значення окремих членів
    cout << endl;
    cout << "Individual terms:" << endl;
    cout << "+------+----------------------+" << endl;
    cout << "|  i   |      term(i)         |" << endl;
    cout << "+------+----------------------+" << endl;
    for (int i = 1; i <= n; i++) {
        cout << "| " << setw(4) << i << " | " 
             << setw(20) << term(i) << " |" << endl;
    }
    cout << "+------+----------------------+" << endl;
    
    cin.get();
    cin.get();
    return 0;
}

