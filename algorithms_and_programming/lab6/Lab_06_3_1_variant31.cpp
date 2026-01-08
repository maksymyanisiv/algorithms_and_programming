// Lab_06_3_1_variant31.cpp
// Янісів Максим
// Лабораторна робота 6.3 - ІТЕРАЦІЙНИЙ СПОСІБ
// Варіант 31: Обчислити суму непарних елементів масиву цілих чисел
// Два способи: 1) звичайні функції, 2) шаблони функцій

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cassert>
using namespace std;

const int SIZE = 15;
const int MIN_VAL = -50;
const int MAX_VAL = 50;

// =====================================================
// СПОСІБ 1: ЗВИЧАЙНІ ФУНКЦІЇ (ітераційні)
// =====================================================

// Заповнення масиву випадковими числами
void fillArray(int arr[], int size, int minVal, int maxVal) {
    for (int i = 0; i < size; i++) {
        arr[i] = minVal + rand() % (maxVal - minVal + 1);
    }
}

// Виведення масиву на екран
void printArray(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << setw(5) << arr[i];
    }
    cout << endl;
}

// Обчислення суми непарних елементів (ітераційно)
int sumOddElements(const int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {  // непарний елемент
            sum += arr[i];
        }
    }
    return sum;
}

// Підрахунок кількості непарних елементів (ітераційно)
int countOddElements(const int arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            count++;
        }
    }
    return count;
}

// =====================================================
// СПОСІБ 2: ШАБЛОНИ ФУНКЦІЙ (ітераційні)
// =====================================================

// Шаблон заповнення масиву
template <typename T>
void fillArrayTemplate(T arr[], int size, T minVal, T maxVal) {
    for (int i = 0; i < size; i++) {
        arr[i] = minVal + rand() % (maxVal - minVal + 1);
    }
}

// Шаблон виведення масиву
template <typename T>
void printArrayTemplate(const T arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << setw(5) << arr[i];
    }
    cout << endl;
}

// Шаблон обчислення суми непарних елементів
template <typename T>
T sumOddElementsTemplate(const T arr[], int size) {
    T sum = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            sum += arr[i];
        }
    }
    return sum;
}

// Шаблон підрахунку кількості непарних елементів
template <typename T>
int countOddElementsTemplate(const T arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            count++;
        }
    }
    return count;
}

// =====================================================
// UNIT TESTS
// =====================================================

void test_sumOddElements() {
    cout << "Testing sumOddElements()..." << endl;
    
    int arr1[] = {1, 2, 3, 4, 5};  // Непарні: 1, 3, 5. Сума = 9
    assert(sumOddElements(arr1, 5) == 9);
    cout << "  {1,2,3,4,5} -> sum of odd = 9 [PASS]" << endl;
    
    int arr2[] = {2, 4, 6, 8, 10};  // Немає непарних
    assert(sumOddElements(arr2, 5) == 0);
    cout << "  {2,4,6,8,10} -> sum of odd = 0 [PASS]" << endl;
    
    int arr3[] = {1, 3, 5, 7, 9};  // Всі непарні. Сума = 25
    assert(sumOddElements(arr3, 5) == 25);
    cout << "  {1,3,5,7,9} -> sum of odd = 25 [PASS]" << endl;
    
    int arr4[] = {-1, -3, 2, 4, 5};  // Непарні: -1, -3, 5. Сума = 1
    assert(sumOddElements(arr4, 5) == 1);
    cout << "  {-1,-3,2,4,5} -> sum of odd = 1 [PASS]" << endl;
    
    int arr5[] = {0, 0, 0, 0, 0};  // Всі парні (0). Сума = 0
    assert(sumOddElements(arr5, 5) == 0);
    cout << "  {0,0,0,0,0} -> sum of odd = 0 [PASS]" << endl;
    
    cout << "All sumOddElements() tests PASSED!" << endl << endl;
}

void test_countOddElements() {
    cout << "Testing countOddElements()..." << endl;
    
    int arr1[] = {1, 2, 3, 4, 5};
    assert(countOddElements(arr1, 5) == 3);
    cout << "  {1,2,3,4,5} -> count of odd = 3 [PASS]" << endl;
    
    int arr2[] = {2, 4, 6, 8, 10};
    assert(countOddElements(arr2, 5) == 0);
    cout << "  {2,4,6,8,10} -> count of odd = 0 [PASS]" << endl;
    
    int arr3[] = {1, 3, 5, 7, 9};
    assert(countOddElements(arr3, 5) == 5);
    cout << "  {1,3,5,7,9} -> count of odd = 5 [PASS]" << endl;
    
    cout << "All countOddElements() tests PASSED!" << endl << endl;
}

void test_templates() {
    cout << "Testing template functions..." << endl;
    
    // int
    int arrInt[] = {1, 2, 3, 4, 5};
    assert(sumOddElementsTemplate(arrInt, 5) == 9);
    assert(countOddElementsTemplate(arrInt, 5) == 3);
    cout << "  Template<int> works correctly [PASS]" << endl;
    
    // short
    short arrShort[] = {1, 2, 3, 4, 5};
    assert(sumOddElementsTemplate(arrShort, 5) == 9);
    assert(countOddElementsTemplate(arrShort, 5) == 3);
    cout << "  Template<short> works correctly [PASS]" << endl;
    
    // long
    long arrLong[] = {1, 2, 3, 4, 5};
    assert(sumOddElementsTemplate(arrLong, 5) == 9);
    assert(countOddElementsTemplate(arrLong, 5) == 3);
    cout << "  Template<long> works correctly [PASS]" << endl;
    
    // Перевірка рівності результатів звичайної та шаблонної функцій
    int testArr[] = {-5, 8, 3, -2, 7, 0, -9, 4};
    assert(sumOddElements(testArr, 8) == sumOddElementsTemplate(testArr, 8));
    assert(countOddElements(testArr, 8) == countOddElementsTemplate(testArr, 8));
    cout << "  Regular == Template functions [PASS]" << endl;
    
    cout << "All template tests PASSED!" << endl << endl;
}

void run_all_tests() {
    cout << "========================================" << endl;
    cout << "   UNIT TESTS - ITERATIVE VERSION      " << endl;
    cout << "========================================" << endl << endl;
    
    test_sumOddElements();
    test_countOddElements();
    test_templates();
    
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
    
    srand(static_cast<unsigned>(time(nullptr)));
    
    cout << "========================================" << endl;
    cout << " Variant 31 - Lab 6.3.1 (Iterative)      " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Task: Calculate sum of ODD elements" << endl;
    cout << "Array size: " << SIZE << ", range [" << MIN_VAL << ", " << MAX_VAL << "]" << endl;
    cout << endl;
    
    // ===== СПОСІБ 1: Звичайні функції =====
    cout << "========== METHOD 1: Regular Functions ==========" << endl;
    cout << endl;
    
    int arr1[SIZE];
    fillArray(arr1, SIZE, MIN_VAL, MAX_VAL);
    
    cout << "Array:" << endl;
    printArray(arr1, SIZE);
    cout << endl;
    
    int sum1 = sumOddElements(arr1, SIZE);
    int count1 = countOddElements(arr1, SIZE);
    
    cout << "Result (regular functions):" << endl;
    cout << "  Count of odd elements: " << count1 << endl;
    cout << "  Sum of odd elements:   " << sum1 << endl;
    cout << endl;
    
    // ===== СПОСІБ 2: Шаблони функцій =====
    cout << "========== METHOD 2: Template Functions ==========" << endl;
    cout << endl;
    
    int arr2[SIZE];
    fillArrayTemplate(arr2, SIZE, MIN_VAL, MAX_VAL);
    
    cout << "Array:" << endl;
    printArrayTemplate(arr2, SIZE);
    cout << endl;
    
    int sum2 = sumOddElementsTemplate(arr2, SIZE);
    int count2 = countOddElementsTemplate(arr2, SIZE);
    
    cout << "Result (template functions):" << endl;
    cout << "  Count of odd elements: " << count2 << endl;
    cout << "  Sum of odd elements:   " << sum2 << endl;
    cout << endl;
    
    // Демонстрація шаблонів з різними типами
    cout << "========== Template with different types ==========" << endl;
    cout << endl;
    
    short arrShort[5] = {11, 22, 33, 44, 55};
    cout << "short array: ";
    printArrayTemplate(arrShort, 5);
    cout << "Sum of odd (short): " << sumOddElementsTemplate(arrShort, 5) << endl;
    
    long arrLong[5] = {100001, 200002, 300003, 400004, 500005};
    cout << "long array:  ";
    printArrayTemplate(arrLong, 5);
    cout << "Sum of odd (long):  " << sumOddElementsTemplate(arrLong, 5) << endl;
    
    cout << endl;
    cout << "========================================" << endl;
    
    return 0;
}

