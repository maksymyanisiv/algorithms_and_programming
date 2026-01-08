// Lab_05_5_variant31.cpp
// Янісів Максим
// Лабораторна робота 5.5
// Рекурсивні функції для переведення чисел у різні системи числення
// Варіант 31

#include <iostream>
#include <string>
#include <cassert>
#include <iomanip>
using namespace std;

// Глобальний лічильник глибини рекурсії
int recursionDepth = 0;
int maxRecursionDepth = 0;

void trackDepth() {
    recursionDepth++;
    if (recursionDepth > maxRecursionDepth) {
        maxRecursionDepth = recursionDepth;
    }
}

void resetDepthCounters() {
    recursionDepth = 0;
    maxRecursionDepth = 0;
}

// =====================================================
// ДВІЙКОВА СИСТЕМА (base = 2)
// =====================================================

// Рекурсивне виведення двійкового представлення (вивід на екран)
void printBinary(unsigned long long n) {
    trackDepth();
    if (n >= 2) {
        printBinary(n / 2);
    }
    cout << (n % 2);
    recursionDepth--;
}

// Рекурсивне отримання двійкового рядка
string toBinaryRecursive(unsigned long long n) {
    trackDepth();
    string result;
    if (n < 2) {
        result = to_string(n % 2);
    } else {
        result = toBinaryRecursive(n / 2) + to_string(n % 2);
    }
    recursionDepth--;
    return result;
}

// =====================================================
// ВІСІМКОВА СИСТЕМА (base = 8)
// =====================================================

// Рекурсивне виведення вісімкового представлення
void printOctal(unsigned long long n) {
    trackDepth();
    if (n >= 8) {
        printOctal(n / 8);
    }
    cout << (n % 8);
    recursionDepth--;
}

// Рекурсивне отримання вісімкового рядка
string toOctalRecursive(unsigned long long n) {
    trackDepth();
    string result;
    if (n < 8) {
        result = to_string(n % 8);
    } else {
        result = toOctalRecursive(n / 8) + to_string(n % 8);
    }
    recursionDepth--;
    return result;
}

// =====================================================
// СИСТЕМА З ОСНОВОЮ N (base = N, де N > 1)
// =====================================================

// Символ для цифри (0-9, A-Z для основ до 36)
char digitToChar(int digit) {
    if (digit < 10) return '0' + digit;
    return 'A' + (digit - 10);
}

// Рекурсивне виведення числа в системі з основою base
void printBaseN(unsigned long long n, int base) {
    trackDepth();
    if (n >= (unsigned long long)base) {
        printBaseN(n / base, base);
    }
    cout << digitToChar(n % base);
    recursionDepth--;
}

// Рекурсивне отримання рядка в системі з основою base
string toBaseNRecursive(unsigned long long n, int base) {
    trackDepth();
    string result;
    if (n < (unsigned long long)base) {
        result = string(1, digitToChar(n % base));
    } else {
        result = toBaseNRecursive(n / base, base) + digitToChar(n % base);
    }
    recursionDepth--;
    return result;
}

// =====================================================
// ІТЕРАТИВНІ ВЕРСІЇ (для перевірки)
// =====================================================

string toBinaryIterative(unsigned long long n) {
    if (n == 0) return "0";
    string result = "";
    while (n > 0) {
        result = to_string(n % 2) + result;
        n /= 2;
    }
    return result;
}

string toOctalIterative(unsigned long long n) {
    if (n == 0) return "0";
    string result = "";
    while (n > 0) {
        result = to_string(n % 8) + result;
        n /= 8;
    }
    return result;
}

string toBaseNIterative(unsigned long long n, int base) {
    if (n == 0) return "0";
    string result = "";
    while (n > 0) {
        result = digitToChar(n % base) + result;
        n /= base;
    }
    return result;
}

// =====================================================
// ОБЧИСЛЕННЯ ГЛИБИНИ РЕКУРСІЇ
// =====================================================

// Глибина = кількість цифр у представленні = floor(log_base(n)) + 1
int calculateRecursionDepth(unsigned long long n, int base) {
    if (n == 0) return 1;
    int depth = 0;
    while (n > 0) {
        n /= base;
        depth++;
    }
    return depth;
}

// =====================================================
// UNIT TESTS
// =====================================================

void test_binary() {
    cout << "Testing binary conversion..." << endl;
    
    assert(toBinaryRecursive(0) == "0");
    cout << "  toBinary(0) = 0 [PASS]" << endl;
    
    assert(toBinaryRecursive(1) == "1");
    cout << "  toBinary(1) = 1 [PASS]" << endl;
    
    assert(toBinaryRecursive(5) == "101");
    cout << "  toBinary(5) = 101 [PASS]" << endl;
    
    assert(toBinaryRecursive(10) == "1010");
    cout << "  toBinary(10) = 1010 [PASS]" << endl;
    
    assert(toBinaryRecursive(255) == "11111111");
    cout << "  toBinary(255) = 11111111 [PASS]" << endl;
    
    assert(toBinaryRecursive(1024) == "10000000000");
    cout << "  toBinary(1024) = 10000000000 [PASS]" << endl;
    
    // Порівняння з ітеративною версією
    for (unsigned long long i = 0; i <= 100; i++) {
        assert(toBinaryRecursive(i) == toBinaryIterative(i));
    }
    cout << "  Recursive == Iterative for 0..100 [PASS]" << endl;
    
    cout << "All binary tests PASSED!" << endl << endl;
}

void test_octal() {
    cout << "Testing octal conversion..." << endl;
    
    assert(toOctalRecursive(0) == "0");
    cout << "  toOctal(0) = 0 [PASS]" << endl;
    
    assert(toOctalRecursive(7) == "7");
    cout << "  toOctal(7) = 7 [PASS]" << endl;
    
    assert(toOctalRecursive(8) == "10");
    cout << "  toOctal(8) = 10 [PASS]" << endl;
    
    assert(toOctalRecursive(64) == "100");
    cout << "  toOctal(64) = 100 [PASS]" << endl;
    
    assert(toOctalRecursive(100) == "144");
    cout << "  toOctal(100) = 144 [PASS]" << endl;
    
    assert(toOctalRecursive(511) == "777");
    cout << "  toOctal(511) = 777 [PASS]" << endl;
    
    // Порівняння з ітеративною версією
    for (unsigned long long i = 0; i <= 100; i++) {
        assert(toOctalRecursive(i) == toOctalIterative(i));
    }
    cout << "  Recursive == Iterative for 0..100 [PASS]" << endl;
    
    cout << "All octal tests PASSED!" << endl << endl;
}

void test_baseN() {
    cout << "Testing base-N conversion..." << endl;
    
    // Шістнадцяткова система
    assert(toBaseNRecursive(255, 16) == "FF");
    cout << "  toBaseN(255, 16) = FF [PASS]" << endl;
    
    assert(toBaseNRecursive(16, 16) == "10");
    cout << "  toBaseN(16, 16) = 10 [PASS]" << endl;
    
    assert(toBaseNRecursive(4096, 16) == "1000");
    cout << "  toBaseN(4096, 16) = 1000 [PASS]" << endl;
    
    // Трійкова система
    assert(toBaseNRecursive(9, 3) == "100");
    cout << "  toBaseN(9, 3) = 100 [PASS]" << endl;
    
    assert(toBaseNRecursive(26, 3) == "222");
    cout << "  toBaseN(26, 3) = 222 [PASS]" << endl;
    
    // Система з основою 5
    assert(toBaseNRecursive(25, 5) == "100");
    cout << "  toBaseN(25, 5) = 100 [PASS]" << endl;
    
    // Перевірка: binary через baseN == toBinary
    for (unsigned long long i = 0; i <= 50; i++) {
        assert(toBaseNRecursive(i, 2) == toBinaryRecursive(i));
    }
    cout << "  toBaseN(n, 2) == toBinary(n) for 0..50 [PASS]" << endl;
    
    // Перевірка: octal через baseN == toOctal
    for (unsigned long long i = 0; i <= 50; i++) {
        assert(toBaseNRecursive(i, 8) == toOctalRecursive(i));
    }
    cout << "  toBaseN(n, 8) == toOctal(n) for 0..50 [PASS]" << endl;
    
    cout << "All base-N tests PASSED!" << endl << endl;
}

void test_recursion_depth() {
    cout << "Testing recursion depth calculation..." << endl;
    
    // Для двійкової системи
    resetDepthCounters();
    toBinaryRecursive(1);
    assert(maxRecursionDepth == 1);
    cout << "  Depth for toBinary(1) = 1 [PASS]" << endl;
    
    resetDepthCounters();
    toBinaryRecursive(255);
    assert(maxRecursionDepth == 8);  // 255 = 11111111 (8 цифр)
    cout << "  Depth for toBinary(255) = 8 [PASS]" << endl;
    
    resetDepthCounters();
    toBinaryRecursive(1024);
    assert(maxRecursionDepth == 11);  // 1024 = 10000000000 (11 цифр)
    cout << "  Depth for toBinary(1024) = 11 [PASS]" << endl;
    
    // Перевірка формули
    assert(calculateRecursionDepth(255, 2) == 8);
    assert(calculateRecursionDepth(1024, 2) == 11);
    assert(calculateRecursionDepth(100, 10) == 3);
    cout << "  calculateRecursionDepth formula verified [PASS]" << endl;
    
    cout << "All recursion depth tests PASSED!" << endl << endl;
}

void run_all_tests() {
    cout << "========================================" << endl;
    cout << "         RUNNING UNIT TESTS            " << endl;
    cout << "========================================" << endl << endl;
    
    test_binary();
    test_octal();
    test_baseN();
    test_recursion_depth();
    
    cout << "========================================" << endl;
    cout << "      ALL TESTS PASSED!                " << endl;
    cout << "========================================" << endl << endl;
}

// =====================================================
// ДЕМОНСТРАЦІЯ
// =====================================================

void demonstrateConversion(unsigned long long n) {
    cout << "\n+------------------------------------------------------------------+" << endl;
    cout << "| Число: " << setw(56) << n << " |" << endl;
    cout << "+------------------------------------------------------------------+" << endl;
    
    // Двійкова система
    resetDepthCounters();
    string binary = toBinaryRecursive(n);
    int binaryDepth = maxRecursionDepth;
    cout << "| Двійкова (base 2):    " << setw(30) << binary 
         << " | Глибина: " << setw(3) << binaryDepth << " |" << endl;
    
    // Вісімкова система
    resetDepthCounters();
    string octal = toOctalRecursive(n);
    int octalDepth = maxRecursionDepth;
    cout << "| Вісімкова (base 8):   " << setw(30) << octal 
         << " | Глибина: " << setw(3) << octalDepth << " |" << endl;
    
    // Шістнадцяткова система
    resetDepthCounters();
    string hex = toBaseNRecursive(n, 16);
    int hexDepth = maxRecursionDepth;
    cout << "| Шістнадцяткова (16):  " << setw(30) << hex 
         << " | Глибина: " << setw(3) << hexDepth << " |" << endl;
    
    // Трійкова система
    resetDepthCounters();
    string ternary = toBaseNRecursive(n, 3);
    int ternaryDepth = maxRecursionDepth;
    cout << "| Трійкова (base 3):    " << setw(30) << ternary 
         << " | Глибина: " << setw(3) << ternaryDepth << " |" << endl;
    
    // П'ятіркова система
    resetDepthCounters();
    string quinary = toBaseNRecursive(n, 5);
    int quinaryDepth = maxRecursionDepth;
    cout << "| П'ятіркова (base 5):  " << setw(30) << quinary 
         << " | Глибина: " << setw(3) << quinaryDepth << " |" << endl;
    
    cout << "+------------------------------------------------------------------+" << endl;
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
    cout << "       Variant 31 - Lab 5.5            " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Рекурсивні функції перетворення чисел" << endl;
    cout << "у різні системи числення" << endl;
    cout << endl;
    
    // Демонстрація з тестовими значеннями
    cout << "=== Демонстрація на прикладах ===" << endl;
    
    unsigned long long testValues[] = {0, 1, 10, 100, 255, 1000, 1024, 65535};
    int numTests = sizeof(testValues) / sizeof(testValues[0]);
    
    for (int i = 0; i < numTests; i++) {
        demonstrateConversion(testValues[i]);
    }
    
    // Інтерактивний режим
    cout << "\n========================================" << endl;
    cout << "=== Інтерактивний режим ===" << endl;
    cout << "========================================" << endl;
    
    while (true) {
        cout << "\nВведіть натуральне число (0 для виходу): ";
        unsigned long long n;
        cin >> n;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка введення! Спробуйте ще раз." << endl;
            continue;
        }
        
        if (n == 0) {
            cout << "Вихід з програми." << endl;
            break;
        }
        
        demonstrateConversion(n);
        
        // Можливість вибору довільної основи
        cout << "\nВведіть основу системи числення (2-36, 0 для пропуску): ";
        int base;
        cin >> base;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        
        if (base >= 2 && base <= 36) {
            resetDepthCounters();
            string result = toBaseNRecursive(n, base);
            int depth = maxRecursionDepth;
            
            cout << "\n+------------------------------------------------------------------+" << endl;
            cout << "| Число " << n << " у системі з основою " << base << ":" << endl;
            cout << "| Результат: " << result << endl;
            cout << "| Глибина рекурсії: " << depth << endl;
            cout << "+------------------------------------------------------------------+" << endl;
        }
    }
    
    cout << endl;
    cout << "========================================" << endl;
    cout << "Дякую за використання програми!" << endl;
    cout << "========================================" << endl;
    
    return 0;
}

