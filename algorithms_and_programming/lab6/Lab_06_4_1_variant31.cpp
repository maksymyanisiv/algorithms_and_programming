// Lab_06_4_1_variant31.cpp
// Янісів Максим
// Лабораторна робота 6.4 - ІТЕРАЦІЙНИЙ СПОСІБ
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
// ІТЕРАЦІЙНІ ФУНКЦІЇ
// =====================================================

// Створення динамічного масиву
double* createArray(int size) {
    return new double[size];
}

// Видалення динамічного масиву
void deleteArray(double* arr) {
    delete[] arr;
}

// Заповнення масиву випадковими числами
void fillArray(double arr[], int size, double minVal, double maxVal) {
    for (int i = 0; i < size; i++) {
        arr[i] = minVal + (rand() / (double)RAND_MAX) * (maxVal - minVal);
        arr[i] = round(arr[i] * 100) / 100;  // округлення до 2 знаків
    }
}

// Виведення масиву на екран
void printArray(const double arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << setw(8) << fixed << setprecision(2) << arr[i];
    }
    cout << endl;
}

// 1.1 Пошук номера мінімального по модулю елемента (ітераційно)
int findMinAbsIndex(const double arr[], int size) {
    if (size <= 0) return -1;
    
    int minIndex = 0;
    double minAbs = fabs(arr[0]);
    
    for (int i = 1; i < size; i++) {
        if (fabs(arr[i]) < minAbs) {
            minAbs = fabs(arr[i]);
            minIndex = i;
        }
    }
    return minIndex;
}

// Пошук індексу першого від'ємного елемента (ітераційно)
int findFirstNegativeIndex(const double arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            return i;
        }
    }
    return -1;  // немає від'ємних
}

// 1.2 Сума модулів елементів після першого від'ємного (ітераційно)
double sumAbsAfterFirstNegative(const double arr[], int size) {
    int firstNegIdx = findFirstNegativeIndex(arr, size);
    
    if (firstNegIdx == -1 || firstNegIdx == size - 1) {
        return 0.0;  // немає від'ємних або від'ємний останній
    }
    
    double sum = 0.0;
    for (int i = firstNegIdx + 1; i < size; i++) {
        sum += fabs(arr[i]);
    }
    return sum;
}

// 2. Стиснення масиву - видалення елементів в інтервалі [a, b] (ітераційно)
// Повертає нову кількість ненульових елементів
int compressArray(double arr[], int size, double a, double b) {
    int writeIdx = 0;
    
    // Копіюємо елементи, що не входять в інтервал [a, b]
    for (int readIdx = 0; readIdx < size; readIdx++) {
        if (arr[readIdx] < a || arr[readIdx] > b) {
            arr[writeIdx] = arr[readIdx];
            writeIdx++;
        }
    }
    
    // Заповнюємо решту нулями
    int newSize = writeIdx;
    for (int i = writeIdx; i < size; i++) {
        arr[i] = 0.0;
    }
    
    return newSize;
}

// Підрахунок елементів в інтервалі [a, b]
int countInInterval(const double arr[], int size, double a, double b) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] >= a && arr[i] <= b) {
            count++;
        }
    }
    return count;
}

// =====================================================
// UNIT TESTS
// =====================================================

void test_findMinAbsIndex() {
    cout << "Testing findMinAbsIndex()..." << endl;
    
    double arr1[] = {3.0, -1.0, 4.0, -0.5, 2.0};
    assert(findMinAbsIndex(arr1, 5) == 3);  // |-0.5| = 0.5 мінімальний
    cout << "  {3,-1,4,-0.5,2} -> index 3 (value -0.5) [PASS]" << endl;
    
    double arr2[] = {-5.0, -3.0, -1.0, -2.0, -4.0};
    assert(findMinAbsIndex(arr2, 5) == 2);  // |-1| = 1 мінімальний
    cout << "  {-5,-3,-1,-2,-4} -> index 2 (value -1) [PASS]" << endl;
    
    double arr3[] = {0.1, 0.2, 0.05, 0.3};
    assert(findMinAbsIndex(arr3, 4) == 2);  // |0.05| мінімальний
    cout << "  {0.1, 0.2, 0.05, 0.3} -> index 2 (value 0.05) [PASS]" << endl;
    
    cout << "All findMinAbsIndex() tests PASSED!" << endl << endl;
}

void test_sumAbsAfterFirstNegative() {
    cout << "Testing sumAbsAfterFirstNegative()..." << endl;
    
    double arr1[] = {1.0, 2.0, -3.0, 4.0, -5.0};
    // Перший від'ємний: -3 (індекс 2). Після нього: 4, -5. Сума модулів: 4+5=9
    assert(fabs(sumAbsAfterFirstNegative(arr1, 5) - 9.0) < 0.001);
    cout << "  {1,2,-3,4,-5} -> sum = 9 [PASS]" << endl;
    
    double arr2[] = {1.0, 2.0, 3.0, 4.0, 5.0};  // немає від'ємних
    assert(sumAbsAfterFirstNegative(arr2, 5) == 0.0);
    cout << "  {1,2,3,4,5} -> sum = 0 (no negative) [PASS]" << endl;
    
    double arr3[] = {-1.0, 2.0, 3.0, 4.0, 5.0};
    // Перший від'ємний: -1 (індекс 0). Після нього: 2,3,4,5. Сума: 14
    assert(fabs(sumAbsAfterFirstNegative(arr3, 5) - 14.0) < 0.001);
    cout << "  {-1,2,3,4,5} -> sum = 14 [PASS]" << endl;
    
    double arr4[] = {1.0, 2.0, 3.0, 4.0, -5.0};  // від'ємний останній
    assert(sumAbsAfterFirstNegative(arr4, 5) == 0.0);
    cout << "  {1,2,3,4,-5} -> sum = 0 (negative is last) [PASS]" << endl;
    
    cout << "All sumAbsAfterFirstNegative() tests PASSED!" << endl << endl;
}

void test_compressArray() {
    cout << "Testing compressArray()..." << endl;
    
    double arr1[] = {1.0, 5.0, 3.0, 7.0, 2.0};
    int newSize1 = compressArray(arr1, 5, 3.0, 6.0);  // Видалити [3, 6]: 5, 3
    assert(newSize1 == 3);
    assert(arr1[0] == 1.0 && arr1[1] == 7.0 && arr1[2] == 2.0);
    assert(arr1[3] == 0.0 && arr1[4] == 0.0);
    cout << "  {1,5,3,7,2} remove [3,6] -> {1,7,2,0,0} [PASS]" << endl;
    
    double arr2[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    int newSize2 = compressArray(arr2, 5, 10.0, 20.0);  // нічого не видаляється
    assert(newSize2 == 5);
    cout << "  {1,2,3,4,5} remove [10,20] -> unchanged [PASS]" << endl;
    
    double arr3[] = {5.0, 5.0, 5.0, 5.0, 5.0};
    int newSize3 = compressArray(arr3, 5, 4.0, 6.0);  // все видаляється
    assert(newSize3 == 0);
    assert(arr3[0] == 0.0 && arr3[4] == 0.0);
    cout << "  {5,5,5,5,5} remove [4,6] -> {0,0,0,0,0} [PASS]" << endl;
    
    cout << "All compressArray() tests PASSED!" << endl << endl;
}

void run_all_tests() {
    cout << "========================================" << endl;
    cout << "   UNIT TESTS - ITERATIVE VERSION      " << endl;
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
    cout << " Variant 31 - Lab 6.4.1 (Iterative)    " << endl;
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
    
    // Створення та заповнення масиву
    double* arr = createArray(n);
    fillArray(arr, n, -10.0, 10.0);
    
    cout << endl;
    cout << "========== ORIGINAL ARRAY ==========" << endl;
    cout << "Array (" << n << " elements):" << endl;
    printArray(arr, n);
    cout << endl;
    
    // 1.1 Номер мінімального по модулю
    int minAbsIdx = findMinAbsIndex(arr, n);
    cout << "1.1 Index of min |element|: " << minAbsIdx 
         << " (value = " << arr[minAbsIdx] << ", |value| = " << fabs(arr[minAbsIdx]) << ")" << endl;
    
    // 1.2 Сума модулів після першого від'ємного
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
    
    // 2. Стиснення масиву
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
