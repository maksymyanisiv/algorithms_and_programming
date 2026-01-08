// Lab_06_2_variant31.cpp
// Янісів Максим
// Лабораторна робота 6.2 - РЕКУРСИВНИЙ СПОСІБ
// Варіант 31: масив b[22], діапазон [-40, 50], критерій: всі, крім додатних кратних 5

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cassert>
using namespace std;

const int SIZE = 22;
const int MIN_VAL = -40;
const int MAX_VAL = 50;

// Критерій: елемент НЕ є додатним кратним 5
bool matchesCriteria(int value) {
    return !(value > 0 && value % 5 == 0);
}

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
    cout << setw(4) << arr[index];
    printArray(arr, size, index + 1);
}

// Рекурсивний підрахунок кількості елементів, що задовольняють критерію
int countElements(const int arr[], int size, int index = 0) {
    if (index >= size) return 0;
    int current = matchesCriteria(arr[index]) ? 1 : 0;
    return current + countElements(arr, size, index + 1);
}

// Рекурсивне обчислення суми елементів, що задовольняють критерію
int sumElements(const int arr[], int size, int index = 0) {
    if (index >= size) return 0;
    int current = matchesCriteria(arr[index]) ? arr[index] : 0;
    return current + sumElements(arr, size, index + 1);
}

// Рекурсивна заміна нулями елементів, що задовольняють критерію
void replaceWithZeros(int arr[], int size, int index = 0) {
    if (index >= size) return;
    if (matchesCriteria(arr[index])) {
        arr[index] = 0;
    }
    replaceWithZeros(arr, size, index + 1);
}

// =====================================================
// UNIT TESTS
// =====================================================

void test_matchesCriteria() {
    cout << "Testing matchesCriteria()..." << endl;
    
    // Додатні кратні 5 - НЕ задовольняють критерію
    assert(matchesCriteria(5) == false);
    assert(matchesCriteria(10) == false);
    assert(matchesCriteria(15) == false);
    assert(matchesCriteria(50) == false);
    cout << "  Positive multiples of 5 -> false [PASS]" << endl;
    
    // Від'ємні числа - задовольняють критерію
    assert(matchesCriteria(-5) == true);
    assert(matchesCriteria(-10) == true);
    assert(matchesCriteria(-40) == true);
    assert(matchesCriteria(-1) == true);
    cout << "  Negative numbers -> true [PASS]" << endl;
    
    // Нуль - задовольняє критерію (не є додатним)
    assert(matchesCriteria(0) == true);
    cout << "  Zero -> true [PASS]" << endl;
    
    // Додатні НЕ кратні 5 - задовольняють критерію
    assert(matchesCriteria(1) == true);
    assert(matchesCriteria(7) == true);
    assert(matchesCriteria(13) == true);
    assert(matchesCriteria(49) == true);
    cout << "  Positive non-multiples of 5 -> true [PASS]" << endl;
    
    cout << "All matchesCriteria() tests PASSED!" << endl << endl;
}

void test_countElements() {
    cout << "Testing countElements() [recursive]..." << endl;
    
    int arr1[] = {5, 10, 15, 20, 25};
    assert(countElements(arr1, 5) == 0);
    cout << "  Array of positive multiples of 5 -> count = 0 [PASS]" << endl;
    
    int arr2[] = {1, 2, 3, 4, 6};
    assert(countElements(arr2, 5) == 5);
    cout << "  Array without multiples of 5 -> count = 5 [PASS]" << endl;
    
    int arr3[] = {-5, -10, 0, 5, 10};
    assert(countElements(arr3, 5) == 3);
    cout << "  Mixed array -> count = 3 [PASS]" << endl;
    
    int arr4[] = {5, 1, 10, 2, 15};
    assert(countElements(arr4, 5) == 2);
    cout << "  Array {5,1,10,2,15} -> count = 2 [PASS]" << endl;
    
    cout << "All countElements() tests PASSED!" << endl << endl;
}

void test_sumElements() {
    cout << "Testing sumElements() [recursive]..." << endl;
    
    int arr1[] = {5, 10, 15, 20, 25};
    assert(sumElements(arr1, 5) == 0);
    cout << "  Array of positive multiples of 5 -> sum = 0 [PASS]" << endl;
    
    int arr2[] = {1, 2, 3, 4, 6};
    assert(sumElements(arr2, 5) == 16);
    cout << "  Array {1,2,3,4,6} -> sum = 16 [PASS]" << endl;
    
    int arr3[] = {-5, -10, 0, 5, 10};
    assert(sumElements(arr3, 5) == -15);
    cout << "  Mixed array -> sum = -15 [PASS]" << endl;
    
    int arr4[] = {5, 7, 10, 3, 15};
    assert(sumElements(arr4, 5) == 10);
    cout << "  Array {5,7,10,3,15} -> sum = 10 [PASS]" << endl;
    
    cout << "All sumElements() tests PASSED!" << endl << endl;
}

void test_replaceWithZeros() {
    cout << "Testing replaceWithZeros() [recursive]..." << endl;
    
    int arr1[] = {1, 5, 2, 10, 3};
    replaceWithZeros(arr1, 5);
    assert(arr1[0] == 0 && arr1[1] == 5 && arr1[2] == 0 && arr1[3] == 10 && arr1[4] == 0);
    cout << "  Array {1,5,2,10,3} -> {0,5,0,10,0} [PASS]" << endl;
    
    int arr2[] = {-5, -10, 0, 5, 10};
    replaceWithZeros(arr2, 5);
    assert(arr2[0] == 0 && arr2[1] == 0 && arr2[2] == 0 && arr2[3] == 5 && arr2[4] == 10);
    cout << "  Array {-5,-10,0,5,10} -> {0,0,0,5,10} [PASS]" << endl;
    
    int arr3[] = {5, 10, 15, 20, 25};
    replaceWithZeros(arr3, 5);
    assert(arr3[0] == 5 && arr3[1] == 10 && arr3[2] == 15 && arr3[3] == 20 && arr3[4] == 25);
    cout << "  Array of multiples of 5 unchanged [PASS]" << endl;
    
    cout << "All replaceWithZeros() tests PASSED!" << endl << endl;
}

void run_all_tests() {
    cout << "========================================" << endl;
    cout << "   UNIT TESTS - RECURSIVE VERSION      " << endl;
    cout << "========================================" << endl << endl;
    
    test_matchesCriteria();
    test_countElements();
    test_sumElements();
    test_replaceWithZeros();
    
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
    cout << "   Variant 31 - Lab 6.2 (Recursive)    " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Array b[" << SIZE << "], range [" << MIN_VAL << ", " << MAX_VAL << "]" << endl;
    cout << "Criteria: all except positive multiples of 5" << endl;
    cout << endl;
    
    int b[SIZE];
    
    // Заповнення масиву (рекурсивно)
    fillArray(b, SIZE, MIN_VAL, MAX_VAL);
    
    // Виведення початкового масиву (рекурсивно)
    cout << "Original array:" << endl;
    printArray(b, SIZE);
    cout << endl;
    
    // Обчислення кількості та суми (рекурсивно)
    int count = countElements(b, SIZE);
    int sum = sumElements(b, SIZE);
    
    cout << "Elements matching criteria (not positive multiples of 5):" << endl;
    cout << "  Count: " << count << endl;
    cout << "  Sum:   " << sum << endl;
    cout << endl;
    
    // Заміна нулями (рекурсивно)
    replaceWithZeros(b, SIZE);
    
    // Виведення модифікованого масиву (рекурсивно)
    cout << "Modified array (matching elements replaced with 0):" << endl;
    printArray(b, SIZE);
    
    cout << endl;
    cout << "========================================" << endl;
    
    return 0;
}

