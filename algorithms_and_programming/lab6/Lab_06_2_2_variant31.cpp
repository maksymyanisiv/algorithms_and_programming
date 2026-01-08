// Lab_06_2_2_variant31.cpp
// Янісів Максим
// Лабораторна робота 6.2 - РЕКУРСИВНИЙ СПОСІБ
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
// РЕКУРСИВНІ ФУНКЦІЇ
// =====================================================

// Рекурсивне заповнення масиву випадковими числами
void fillArray(int arr[], int size, int minVal, int maxVal, int index = 0) {
    if (index >= size) return;
    arr[index] = minVal + rand() % (maxVal - minVal + 1);
    fillArray(arr, size, minVal, maxVal, index + 1);
}

// Рекурсивне виведення масиву на екран
void printArray(const int arr[], int size, int index = 0) {
    if (index >= size) {
        cout << endl;
        return;
    }
    cout << setw(5) << arr[index];
    printArray(arr, size, index + 1);
}

// Рекурсивний пошук індексу найменшого парного елемента
// Параметри: arr - масив, size - розмір, index - поточний індекс,
//            minIndex - індекс поточного мінімуму, minValue - значення мінімуму
int findMinEvenIndexRec(const int arr[], int size, int index, int minIndex, int minValue) {
    // Базовий випадок: досягли кінця масиву
    if (index >= size) {
        return minIndex;
    }
    
    // Перевіряємо поточний елемент
    int newMinIndex = minIndex;
    int newMinValue = minValue;
    
    if (arr[index] % 2 == 0) {  // парний елемент
        if (arr[index] < minValue) {
            newMinIndex = index;
            newMinValue = arr[index];
        }
    }
    
    // Рекурсивний виклик для наступного елемента
    return findMinEvenIndexRec(arr, size, index + 1, newMinIndex, newMinValue);
}

// Обгортка для рекурсивного пошуку
int findMinEvenIndex(const int arr[], int size) {
    return findMinEvenIndexRec(arr, size, 0, -1, INT_MAX);
}

// Обмін двох елементів
void swapElements(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Міняти місцями перший елемент із найменшим парним
bool swapFirstWithMinEven(int arr[], int size) {
    int minEvenIndex = findMinEvenIndex(arr, size);
    
    if (minEvenIndex == -1) {
        return false;
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
    cout << "Testing findMinEvenIndex() [recursive]..." << endl;
    
    int arr1[] = {1, 4, 2, 8, 6};
    assert(findMinEvenIndex(arr1, 5) == 2);
    cout << "  {1,4,2,8,6} -> index 2 (value 2) [PASS]" << endl;
    
    int arr2[] = {1, 3, 5, 7, 9};
    assert(findMinEvenIndex(arr2, 5) == -1);
    cout << "  {1,3,5,7,9} -> -1 (no even) [PASS]" << endl;
    
    int arr3[] = {10, -4, 2, -6, 8};
    assert(findMinEvenIndex(arr3, 5) == 3);
    cout << "  {10,-4,2,-6,8} -> index 3 (value -6) [PASS]" << endl;
    
    int arr4[] = {0, 2, 4, 6, 8};
    assert(findMinEvenIndex(arr4, 5) == 0);
    cout << "  {0,2,4,6,8} -> index 0 (value 0) [PASS]" << endl;
    
    int arr5[] = {5, 3, -10, 7, 2};
    assert(findMinEvenIndex(arr5, 5) == 2);
    cout << "  {5,3,-10,7,2} -> index 2 (value -10) [PASS]" << endl;
    
    cout << "All findMinEvenIndex() tests PASSED!" << endl << endl;
}

void test_swapFirstWithMinEven() {
    cout << "Testing swapFirstWithMinEven() [recursive]..." << endl;
    
    int arr1[] = {5, 4, 2, 8, 6};
    bool result1 = swapFirstWithMinEven(arr1, 5);
    assert(result1 == true);
    assert(arr1[0] == 2 && arr1[2] == 5);
    cout << "  {5,4,2,8,6} -> {2,4,5,8,6} [PASS]" << endl;
    
    int arr2[] = {1, 3, 5, 7, 9};
    bool result2 = swapFirstWithMinEven(arr2, 5);
    assert(result2 == false);
    assert(arr2[0] == 1);
    cout << "  {1,3,5,7,9} -> unchanged (no even) [PASS]" << endl;
    
    int arr3[] = {2, 4, 6, 8, 10};
    bool result3 = swapFirstWithMinEven(arr3, 5);
    assert(result3 == true);
    assert(arr3[0] == 2);
    cout << "  {2,4,6,8,10} -> {2,4,6,8,10} (first is min even) [PASS]" << endl;
    
    int arr4[] = {10, 5, -8, 3, 4};
    bool result4 = swapFirstWithMinEven(arr4, 5);
    assert(result4 == true);
    assert(arr4[0] == -8 && arr4[2] == 10);
    cout << "  {10,5,-8,3,4} -> {-8,5,10,3,4} [PASS]" << endl;
    
    cout << "All swapFirstWithMinEven() tests PASSED!" << endl << endl;
}

void run_all_tests() {
    cout << "========================================" << endl;
    cout << "   UNIT TESTS - RECURSIVE VERSION      " << endl;
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
    cout << " Variant 31 - Lab 6.2.2 (Recursive)    " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Task: Swap first element with minimum even element" << endl;
    cout << "Array a[" << SIZE << "], range [" << MIN_VAL << ", " << MAX_VAL << "]" << endl;
    cout << endl;
    
    int a[SIZE];
    
    // Заповнення масиву (рекурсивно)
    fillArray(a, SIZE, MIN_VAL, MAX_VAL);
    
    // Виведення початкового масиву (рекурсивно)
    cout << "Original array:" << endl;
    printArray(a, SIZE);
    cout << endl;
    
    // Пошук найменшого парного (рекурсивно)
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
        
        // Виведення результату (рекурсивно)
        cout << "After swapping first with min even:" << endl;
        printArray(a, SIZE);
    }
    
    cout << endl;
    cout << "========================================" << endl;
    
    return 0;
}

