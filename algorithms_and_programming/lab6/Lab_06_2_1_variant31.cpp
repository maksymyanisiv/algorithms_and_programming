// Lab_06_2_1_variant31.cpp
// Янісів Максим
// Лабораторна робота 6.2 - ІТЕРАЦІЙНИЙ СПОСІБ
// Варіант 31: Міняти місцями перший елемент із найменшим парним елементом масиву

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <climits>
using namespace std;

const int SIZE = 13;
const int MIN_VAL = -50;
const int MAX_VAL = 50;

// =====================================================
// ІТЕРАЦІЙНІ ФУНКЦІЇ
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

// Пошук індексу найменшого парного елемента (ітераційно)
// Повертає -1, якщо парних елементів немає
int findMinEvenIndex(const int arr[], int size) {
    int minIndex = -1;
    int minValue = INT_MAX;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {  // парний елемент
            if (arr[i] < minValue) {
                minValue = arr[i];
                minIndex = i;
            }
        }
    }
    return minIndex;
}

// Обмін двох елементів
void swapElements(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Міняти місцями перший елемент із найменшим парним
// Повертає true, якщо обмін відбувся
bool swapFirstWithMinEven(int arr[], int size) {
    int minEvenIndex = findMinEvenIndex(arr, size);
    
    if (minEvenIndex == -1) {
        return false;  // парних елементів немає
    }
    
    if (minEvenIndex != 0) {
        swapElements(arr[0], arr[minEvenIndex]);
    }
    return true;
}

// =====================================================
// UNIT TESTS
// =====================================================

void test_findMinEvenIndex() {
    cout << "Testing findMinEvenIndex()..." << endl;
    
    int arr1[] = {1, 4, 2, 8, 6};  // Парні: 4(1), 2(2), 8(3), 6(4). Мін = 2 на індексі 2
    assert(findMinEvenIndex(arr1, 5) == 2);
    cout << "  {1,4,2,8,6} -> index 2 (value 2) [PASS]" << endl;
    
    int arr2[] = {1, 3, 5, 7, 9};  // Немає парних
    assert(findMinEvenIndex(arr2, 5) == -1);
    cout << "  {1,3,5,7,9} -> -1 (no even) [PASS]" << endl;
    
    int arr3[] = {10, -4, 2, -6, 8};  // Парні: 10, -4, 2, -6, 8. Мін = -6 на індексі 3
    assert(findMinEvenIndex(arr3, 5) == 3);
    cout << "  {10,-4,2,-6,8} -> index 3 (value -6) [PASS]" << endl;
    
    int arr4[] = {0, 2, 4, 6, 8};  // Всі парні. Мін = 0 на індексі 0
    assert(findMinEvenIndex(arr4, 5) == 0);
    cout << "  {0,2,4,6,8} -> index 0 (value 0) [PASS]" << endl;
    
    int arr5[] = {5, 3, -10, 7, 2};  // Парні: -10(2), 2(4). Мін = -10 на індексі 2
    assert(findMinEvenIndex(arr5, 5) == 2);
    cout << "  {5,3,-10,7,2} -> index 2 (value -10) [PASS]" << endl;
    
    cout << "All findMinEvenIndex() tests PASSED!" << endl << endl;
}

void test_swapFirstWithMinEven() {
    cout << "Testing swapFirstWithMinEven()..." << endl;
    
    int arr1[] = {5, 4, 2, 8, 6};
    bool result1 = swapFirstWithMinEven(arr1, 5);
    assert(result1 == true);
    assert(arr1[0] == 2 && arr1[2] == 5);  // 5 і 2 помінялись
    cout << "  {5,4,2,8,6} -> {2,4,5,8,6} [PASS]" << endl;
    
    int arr2[] = {1, 3, 5, 7, 9};
    bool result2 = swapFirstWithMinEven(arr2, 5);
    assert(result2 == false);  // Немає парних
    assert(arr2[0] == 1);  // Масив не змінився
    cout << "  {1,3,5,7,9} -> unchanged (no even) [PASS]" << endl;
    
    int arr3[] = {2, 4, 6, 8, 10};  // Перший вже найменший парний
    bool result3 = swapFirstWithMinEven(arr3, 5);
    assert(result3 == true);
    assert(arr3[0] == 2);  // Масив не змінився (перший вже мінімальний)
    cout << "  {2,4,6,8,10} -> {2,4,6,8,10} (first is min even) [PASS]" << endl;
    
    int arr4[] = {10, 5, -8, 3, 4};  // Мін парний = -8 на індексі 2
    bool result4 = swapFirstWithMinEven(arr4, 5);
    assert(result4 == true);
    assert(arr4[0] == -8 && arr4[2] == 10);
    cout << "  {10,5,-8,3,4} -> {-8,5,10,3,4} [PASS]" << endl;
    
    cout << "All swapFirstWithMinEven() tests PASSED!" << endl << endl;
}

void run_all_tests() {
    cout << "========================================" << endl;
    cout << "   UNIT TESTS - ITERATIVE VERSION      " << endl;
    cout << "========================================" << endl << endl;
    
    test_findMinEvenIndex();
    test_swapFirstWithMinEven();
    
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
    cout << " Variant 31 - Lab 6.2.1 (Iterative)    " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Task: Swap first element with minimum even element" << endl;
    cout << "Array a[" << SIZE << "], range [" << MIN_VAL << ", " << MAX_VAL << "]" << endl;
    cout << endl;
    
    int a[SIZE];
    
    // Заповнення масиву
    fillArray(a, SIZE, MIN_VAL, MAX_VAL);
    
    // Виведення початкового масиву
    cout << "Original array:" << endl;
    printArray(a, SIZE);
    cout << endl;
    
    // Пошук найменшого парного
    int minEvenIndex = findMinEvenIndex(a, SIZE);
    
    if (minEvenIndex == -1) {
        cout << "No even elements found in the array!" << endl;
    } else {
        cout << "Minimum even element: " << a[minEvenIndex] 
             << " at index " << minEvenIndex << endl;
        cout << "First element: " << a[0] << " at index 0" << endl;
        cout << endl;
        
        // Обмін
        swapFirstWithMinEven(a, SIZE);
        
        // Виведення результату
        cout << "After swapping first with min even:" << endl;
        printArray(a, SIZE);
    }
    
    cout << endl;
    cout << "========================================" << endl;
    
    return 0;
}

