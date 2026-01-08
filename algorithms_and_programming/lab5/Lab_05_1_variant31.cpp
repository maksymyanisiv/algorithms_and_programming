// Lab_05_1_variant31.cpp
// Янісів Максим
// Лабораторна робота 5.1
// Допоміжні алгоритми (функції)
// Варіант 31

#include <iostream>
#include <cmath>
#include <cassert>
#include <cstdlib>
using namespace std;

// Допоміжна функція p(x) = 1 + x^2/2 - x^4/4
double p(double x) {
    double x2 = x * x;
    double x4 = x2 * x2;
    return 1.0 + x2 / 2.0 - x4 / 4.0;
}

// Основна функція обчислення виразу
// result = (p^2 * (1+2s+s^2) - p^3 * (1+3s+s^3)) / (1 + sqrt(p(s) + p^4(s)))
double calculate(double s) {
    double ps = p(s);           // p(s)
    double ps2 = ps * ps;       // p^2
    double ps3 = ps2 * ps;      // p^3
    double ps4 = ps3 * ps;      // p^4
    
    double s2 = s * s;
    double s3 = s2 * s;
    
    double numerator = ps2 * (1 + 2*s + s2) - ps3 * (1 + 3*s + s3);
    double denominator = 1 + sqrt(ps + ps4);
    
    if (denominator == 0) {
        cerr << "Error: Division by zero!" << endl;
        return 0;
    }
    
    return numerator / denominator;
}

// =====================================================
// UNIT TESTS
// =====================================================

const double EPSILON = 1e-9;

bool approxEqual(double a, double b, double eps = EPSILON) {
    return fabs(a - b) < eps;
}

void test_p_function() {
    cout << "Testing p(x) function..." << endl;
    
    // Test p(0) = 1 + 0/2 - 0/4 = 1
    assert(approxEqual(p(0), 1.0));
    cout << "  p(0) = " << p(0) << " [PASS]" << endl;
    
    // Test p(1) = 1 + 1/2 - 1/4 = 1.25
    assert(approxEqual(p(1), 1.25));
    cout << "  p(1) = " << p(1) << " [PASS]" << endl;
    
    // Test p(-1) = 1 + 1/2 - 1/4 = 1.25 (функція парна по x^2 і x^4)
    assert(approxEqual(p(-1), 1.25));
    cout << "  p(-1) = " << p(-1) << " [PASS]" << endl;
    
    // Test p(2) = 1 + 4/2 - 16/4 = 1 + 2 - 4 = -1
    assert(approxEqual(p(2), -1.0));
    cout << "  p(2) = " << p(2) << " [PASS]" << endl;
    
    // Test p(0.5) = 1 + 0.25/2 - 0.0625/4 = 1 + 0.125 - 0.015625 = 1.109375
    assert(approxEqual(p(0.5), 1.109375));
    cout << "  p(0.5) = " << p(0.5) << " [PASS]" << endl;
    
    cout << "All p(x) tests PASSED!" << endl << endl;
}

void test_calculate_function() {
    cout << "Testing calculate(s) function..." << endl;
    
    // Test s = 0
    // p(0) = 1, p^2 = 1, p^3 = 1, p^4 = 1
    // numerator = 1*(1+0+0) - 1*(1+0+0) = 1 - 1 = 0
    // denominator = 1 + sqrt(1+1) = 1 + sqrt(2)
    // result = 0
    double result0 = calculate(0);
    assert(approxEqual(result0, 0.0));
    cout << "  calculate(0) = " << result0 << " [PASS]" << endl;
    
    // Test s = 1
    // p(1) = 1.25, p^2 = 1.5625, p^3 = 1.953125, p^4 = 2.44140625
    // numerator = 1.5625*(1+2+1) - 1.953125*(1+3+1) = 1.5625*4 - 1.953125*5
    //           = 6.25 - 9.765625 = -3.515625
    // denominator = 1 + sqrt(1.25 + 2.44140625) = 1 + sqrt(3.69140625) = 1 + 1.92130... ≈ 2.92130
    double result1 = calculate(1);
    double expected1 = -3.515625 / (1 + sqrt(1.25 + 2.44140625));
    assert(approxEqual(result1, expected1, 1e-6));
    cout << "  calculate(1) = " << result1 << " [PASS]" << endl;
    
    // Test s = 0.5
    double result05 = calculate(0.5);
    double ps05 = p(0.5);
    double ps05_2 = ps05 * ps05;
    double ps05_3 = ps05_2 * ps05;
    double ps05_4 = ps05_3 * ps05;
    double num05 = ps05_2 * (1 + 2*0.5 + 0.25) - ps05_3 * (1 + 3*0.5 + 0.125);
    double den05 = 1 + sqrt(ps05 + ps05_4);
    double expected05 = num05 / den05;
    assert(approxEqual(result05, expected05, 1e-6));
    cout << "  calculate(0.5) = " << result05 << " [PASS]" << endl;
    
    cout << "All calculate(s) tests PASSED!" << endl << endl;
}

void run_all_tests() {
    cout << "========================================" << endl;
    cout << "         RUNNING UNIT TESTS            " << endl;
    cout << "========================================" << endl << endl;
    
    test_p_function();
    test_calculate_function();
    
    cout << "========================================" << endl;
    cout << "      ALL TESTS PASSED!                " << endl;
    cout << "========================================" << endl << endl;
}

// =====================================================
// MAIN PROGRAM
// =====================================================

int main(int argc, char* argv[]) {
    // Якщо передано аргумент --test, запускаємо тести
    if (argc > 1 && string(argv[1]) == "--test") {
        run_all_tests();
        return 0;
    }
    
    double s;
    
    cout << "========================================" << endl;
    cout << "       Variant 31 - Lab 5.1            " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Formula:" << endl;
    cout << "  result = (p^2*(1+2s+s^2) - p^3*(1+3s+s^3))" << endl;
    cout << "           / (1 + sqrt(p(s) + p^4(s)))" << endl;
    cout << endl;
    cout << "where p(x) = 1 + x^2/2 - x^4/4" << endl;
    cout << endl;
    
    cout << "Enter s: ";
    cin >> s;
    cout << endl;
    
    double ps = p(s);
    double result = calculate(s);
    
    cout << "========================================" << endl;
    cout << "Intermediate values:" << endl;
    cout << "  p(s) = p(" << s << ") = " << ps << endl;
    cout << "  p^2 = " << ps * ps << endl;
    cout << "  p^3 = " << ps * ps * ps << endl;
    cout << "  p^4 = " << ps * ps * ps * ps << endl;
    cout << endl;
    cout << "Result:" << endl;
    cout << "  result = " << result << endl;
    cout << "========================================" << endl;
    
    cin.get();
    cin.get();
    return 0;
}

