// Lab_06_4_2_variant31.cpp
// Янісів Максим
// Лабораторна робота 6.4 - РЕКУРСИВНИЙ СПОСІБ
// Варіант 31: Динамічний масив дійсних чисел
// 1.1 Номер мінімального по модулю елемента
// 1.2 Сума модулів після першого від'ємного
// 2. Стиснути масив, видаливши елементи в інтервалі [a, b]

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cassert>
using namespace std;

// =====================================================
// РЕКУРСИВНІ ФУНКЦІЇ
// =====================================================

// Створення динамічного масиву
double* createArray(int size) {
    return new double[size];
}

// Видалення динамічного масиву
void deleteArray(double* arr) {
    delete[] arr;
}

// Рекурсивне заповнення масиву випадковими числами
void fillArray(double arr[], int size, double minVal, double maxVal, int index = 0) {
    if (index >= size) return;
    arr[index] = minVal + (rand() / (double)RAND_MAX) * (maxVal - minVal);
    arr[index] = round(arr[index] * 100) / 100;
    fillArray(arr, size, minVal, maxVal, index + 1);
}

// Рекурсивне виведення масиву на екран
void printArray(const double arr[], int size, int index = 0) {
    if (index >= size) {
        cout << endl;
        return;
    }
    cout << setw(8) << fixed << setprecision(2) << arr[index];
    printArray(arr, size, index + 1);
}

// Рекурсивний пошук мінімального по модулю (допоміжна функція)
int findMinAbsIndexRec(const double arr[], int size, int index, int minIdx, double minAbs) {
    if (index >= size) return minIdx;
    
    int newMinIdx = minIdx;
    double newMinAbs = minAbs;
    
    if (fabs(arr[index]) < minAbs) {
        newMinIdx = index;
        newMinAbs = fabs(arr[index]);
    }
    
    return findMinAbsIndexRec(arr, size, index + 1, newMinIdx, newMinAbs);
}

// 1.1 Пошук номера мінімального по модулю елемента (рекурсивно)
int findMinAbsIndex(const double arr[], int size) {
    if (size <= 0) return -1;
    return findMinAbsIndexRec(arr, size, 1, 0, fabs(arr[0]));
}

// Рекурсивний пошук індексу першого від'ємного елемента
int findFirstNegativeIndex(const double arr[], int size, int index = 0) {
    if (index >= size) return -1;
    if (arr[index] < 0) return index;
    return findFirstNegativeIndex(arr, size, index + 1);
}

// Рекурсивна сума модулів починаючи з індексу start
double sumAbsFromIndex(const double arr[], int size, int index) {
    if (index >= size) return 0.0;
    return fabs(arr[index]) + sumAbsFromIndex(arr, size, index + 1);
}

// 1.2 Сума модулів елементів після першого від'ємного (рекурсивно)
double sumAbsAfterFirstNegative(const double arr[], int size) {
    int firstNegIdx = findFirstNegativeIndex(arr, size);
    
    if (firstNegIdx == -1 || firstNegIdx == size - 1) {
        return 0.0;
    }
    
    return sumAbsFromIndex(arr, size, firstNegIdx + 1);
}

// Рекурсивне копіювання елементів, що не входять в інтервал [a, b]
int copyExcludingInterval(double arr[], int size, double a, double b, 
                          int readIdx, int writeIdx) {
    if (readIdx >= size) return writeIdx;
    
    if (arr[readIdx] < a || arr[readIdx] > b) {
        double temp = arr[readIdx];
        arr[writeIdx] = temp;
        return copyExcludingInterval(arr, size, a, b, readIdx + 1, writeIdx + 1);
    }
    return copyExcludingInterval(arr, size, a, b, readIdx + 1, writeIdx);
}

// Рекурсивне заповнення нулями
void fillWithZeros(double arr[], int size, int index) {
    if (index >= size) return;
    arr[index] = 0.0;
    fillWithZeros(arr, size, index + 1);
}

// 2. Стиснення масиву - видалення елементів в інтервалі [a, b] (рекурсивно)
int compressArray(double arr[], int size, double a, double b) {
    int newSize = copyExcludingInterval(arr, size, a, b, 0, 0);
    fillWithZeros(arr, size, newSize);
    return newSize;
}

// Рекурсивний підрахунок елементів в інтервалі [a, b]
int countInInterval(const double arr[], int size, double a, double b, int index = 0) {
    if (index >= size) return 0;
    int current = (arr[index] >= a && arr[index] <= b) ? 1 : 0;
    return current + countInInterval(arr, size, a, b, index + 1);
}

// =====================================================
// UNIT TESTS
// =====================================================

void test_findMinAbsIndex() {
    cout << "Testing findMinAbsIndex() [recursive]..." << endl;
    
    double arr1[] = {3.0, -1.0, 4.0, -0.5, 2.0};
    assert(findMinAbsIndex(arr1, 5) == 3);
    cout << "  {3,-1,4,-0.5,2} -> index 3 (value -0.5) [PASS]" << endl;
    
    double arr2[] = {-5.0, -3.0, -1.0, -2.0, -4.0};
    assert(findMinAbsIndex(arr2, 5) == 2);
    cout << "  {-5,-3,-1,-2,-4} -> index 2 (value -1) [PASS]" << endl;
    
    double arr3[] = {0.1, 0.2, 0.05, 0.3};
    assert(findMinAbsIndex(arr3, 4) == 2);
    cout << "  {0.1, 0.2, 0.05, 0.3} -> index 2 (value 0.05) [PASS]" << endl;
    
    cout << "All findMinAbsIndex() tests PASSED!" << endl << endl;
}

void test_sumAbsAfterFirstNegative() {
    cout << "Testing sumAbsAfterFirstNegative() [recursive]..." << endl;
    
    double arr1[] = {1.0, 2.0, -3.0, 4.0, -5.0};
    assert(fabs(sumAbsAfterFirstNegative(arr1, 5) - 9.0) < 0.001);
    cout << "  {1,2,-3,4,-5} -> sum = 9 [PASS]" << endl;
    
    double arr2[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    assert(sumAbsAfterFirstNegative(arr2, 5) == 0.0);
    cout << "  {1,2,3,4,5} -> sum = 0 (no negative) [PASS]" << endl;
    
    double arr3[] = {-1.0, 2.0, 3.0, 4.0, 5.0};
    assert(fabs(sumAbsAfterFirstNegative(arr3, 5) - 14.0) < 0.001);
    cout << "  {-1,2,3,4,5} -> sum = 14 [PASS]" << endl;
    
    double arr4[] = {1.0, 2.0, 3.0, 4.0, -5.0};
    assert(sumAbsAfterFirstNegative(arr4, 5) == 0.0);
    cout << "  {1,2,3,4,-5} -> sum = 0 (negative is last) [PASS]" << endl;
    
    cout << "All sumAbsAfterFirstNegative() tests PASSED!" << endl << endl;
}

void test_compressArray() {
    cout << "Testing compressArray() [recursive]..." << endl;
    
    double arr1[] = {1.0, 5.0, 3.0, 7.0, 2.0};
    int newSize1 = compressArray(arr1, 5, 3.0, 6.0);
    assert(newSize1 == 3);
    assert(arr1[0] == 1.0 && arr1[1] == 7.0 && arr1[2] == 2.0);
    assert(arr1[3] == 0.0 && arr1[4] == 0.0);
    cout << "  {1,5,3,7,2} remove [3,6] -> {1,7,2,0,0} [PASS]" << endl;
    
    double arr2[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    int newSize2 = compressArray(arr2, 5, 10.0, 20.0);
    assert(newSize2 == 5);
    cout << "  {1,2,3,4,5} remove [10,20] -> unchanged [PASS]" << endl;
    
    double arr3[] = {5.0, 5.0, 5.0, 5.0, 5.0};
    int newSize3 = compressArray(arr3, 5, 4.0, 6.0);
    assert(newSize3 == 0);
    assert(arr3[0] == 0.0 && arr3[4] == 0.0);
    cout << "  {5,5,5,5,5} remove [4,6] -> {0,0,0,0,0} [PASS]" << endl;
    
    cout << "All compressArray() tests PASSED!" << endl << endl;
}

void run_all_tests() {
    cout << "========================================" << endl;
    cout << "   UNIT TESTS - RECURSIVE VERSION      " << endl;
    cout << "========================================" << endl << endl;
    
    test_findMinAbsIndex();
    test_sumAbsAfterFirstNegative();
    test_compressArray();
    
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
    cout << " Variant 31 - Lab 6.4.2 (Recursive)    " << endl;
    cout << "========================================" << endl;
    cout << endl;
    
    // Введення параметрів
    int n;
    double a, b;
    
    cout << "Enter array size n: ";
    cin >> n;
    
    if (n <= 0) {
        cout << "Error: n must be positive!" << endl;
        return 1;
    }
    
    cout << "Enter interval [a, b] for compression:" << endl;
    cout << "  a = ";
    cin >> a;
    cout << "  b = ";
    cin >> b;
    
    if (a > b) {
        swap(a, b);
        cout << "  (swapped: a=" << a << ", b=" << b << ")" << endl;
    }
    
    // Створення та заповнення масиву (рекурсивно)
    double* arr = createArray(n);
    fillArray(arr, n, -10.0, 10.0);
    
    cout << endl;
    cout << "========== ORIGINAL ARRAY ==========" << endl;
    cout << "Array (" << n << " elements):" << endl;
    printArray(arr, n);
    cout << endl;
    
    // 1.1 Номер мінімального по модулю (рекурсивно)
    int minAbsIdx = findMinAbsIndex(arr, n);
    cout << "1.1 Index of min |element|: " << minAbsIdx 
         << " (value = " << arr[minAbsIdx] << ", |value| = " << fabs(arr[minAbsIdx]) << ")" << endl;
    
    // 1.2 Сума модулів після першого від'ємного (рекурсивно)
    int firstNegIdx = findFirstNegativeIndex(arr, n);
    double sumAbs = sumAbsAfterFirstNegative(arr, n);
    
    if (firstNegIdx == -1) {
        cout << "1.2 No negative elements in array" << endl;
    } else {
        cout << "1.2 First negative at index " << firstNegIdx 
             << " (value = " << arr[firstNegIdx] << ")" << endl;
        cout << "    Sum of |elements| after first negative: " << sumAbs << endl;
    }
    cout << endl;
    
    // 2. Стиснення масиву (рекурсивно)
    cout << "========== COMPRESSION ==========" << endl;
    cout << "Removing elements in interval [" << a << ", " << b << "]" << endl;
    
    int countRemoved = countInInterval(arr, n, a, b);
    cout << "Elements to remove: " << countRemoved << endl;
    
    int newSize = compressArray(arr, n, a, b);
    
    cout << endl;
    cout << "========== MODIFIED ARRAY ==========" << endl;
    cout << "Array after compression (" << newSize << " non-zero elements):" << endl;
    printArray(arr, n);
    
    // Звільнення пам'яті
    deleteArray(arr);
    
    cout << endl;
    cout << "========================================" << endl;
    
    return 0;
}
