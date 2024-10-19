#include <iostream>
#include <iomanip>
#include <ctime>
#include <Windows.h>

using namespace std;

static void CreateRow(int** a, const int rowNo, const int N, const int Low, const int High, int colNo) {
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < N - 1)
        CreateRow(a, rowNo, N, Low, High, colNo + 1);
}

static void CreateRows(int** a, const int N, const int K, const int Low, const int High, int rowNo) {
    CreateRow(a, rowNo, K, Low, High, 0);
    if (rowNo < N - 1)
        CreateRows(a, N, K, Low, High, rowNo + 1);
}

static void PrintRow(int** a, const int rowNo, const int N, int colNo) {
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < N - 1)
        PrintRow(a, rowNo, N, colNo + 1);
    else
        cout << endl;
}

static void PrintRows(int** a, const int N, const int K, int rowNo) {
    PrintRow(a, rowNo, K, 0);
    if (rowNo < N - 1)
        PrintRows(a, N, K, rowNo + 1);
    else
        cout << endl;
}

static void findMaxInRow(int** a, const int colCount, int i, int& max) {
    if (i >= colCount) {
        return;
    }
    if (a[0][i] > max) {
        max = a[0][i];
    }
    findMaxInRow(a, colCount, i + 1, max);
}

static void findSumOfMaxInEvenRows(int** a, const int rowCount, const int colCount, int i = 0, int sum = 0) {
    if (i >= rowCount) {
        cout << "Сума максимальних елементів по парних рядках: " << sum << endl;
        return;
    }

    if (i % 2 == 0) { 
        int max = a[i][0];
        findMaxInRow(a + i, colCount, 0, max); 
        sum += max;
    }

    findSumOfMaxInEvenRows(a, rowCount, colCount, i + 1, sum);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(static_cast<unsigned>(time(nullptr)));

    int Low = -34;
    int High = 26;
    int rowCount;
    int colCount;

    cout << "k = ";
    cin >> rowCount;
    cout << "n = ";
    cin >> colCount;

    int** a = new int* [rowCount];

    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    CreateRows(a, rowCount, colCount, Low, High, 0);
    PrintRows(a, colCount, rowCount, 0);

    findSumOfMaxInEvenRows(a, rowCount, colCount);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}
