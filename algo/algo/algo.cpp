#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;


int SelectionSort(int a[], int N) {
    int n = N;
    for (int j = (n - 1); j >= 2; j--) {
        int max_index = j;
        for (int i = j; i >= 0; i--) {
            if (a[i] > a[max_index]) {
                max_index = i;
            }
        }
        if (j != max_index) {
            swap(a[j], a[max_index]);
        }
    }
}

bool checkArray(int arr[], int N) {
    for (int i = 0; i < N - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

int log2RoundUp(int N) {
    int i = 0;
    while (pow(2, i) < N) {
        i++;
    }
    return i;
}

void BatchersMergeSort(int arr[], int N) {
    int t = log2RoundUp(N);
    int p0 = pow(2, t - 1);
    int p = p0;

    while (p > 0) {
        int q = p0, r = 0, d = p;

        while (r == 0 || q != p) {
            if (r != 0)
            {
                d = q - p;
                q >>= 1;
            }

            for (int i = 0; i < N - d; i++) {
                if (((i & p) == r) && arr[i] > arr[i + d]) {
                    swap(arr[i], arr[i + d]);
                }
            }

            r = p;
        }

        p = p / 2;
    }
}

int compare(const void* x1, const void* x2)   // функция сравнения элементов массива
{
    return (*(int*)x1 - *(int*)x2);              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}

int main()
{
    setlocale(LC_ALL, "RUS");
    const int N = 5000;
    int a[N] = {};
    int c [N] = {};
    int n;
    int bab[N] = {};
    ifstream input("d5000.txt");
    for (int i = 0; i < N; i++)
    {
        input >> n;
        a[i] = n;
        c[i] = n;
        bab[i] = n;
    }
    input.close();

    auto start = chrono::steady_clock::now();
    qsort(c,N, sizeof(int),compare);
    auto end = chrono::steady_clock::now();

    auto start1 = chrono::steady_clock::now();
    SelectionSort(a, N);
    auto end1 = chrono::steady_clock::now();

    auto start2 = chrono::steady_clock::now();
    BatchersMergeSort(bab, N);
    auto end2 = chrono::steady_clock::now();

    long duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << endl << "Время сортировки qsort:" << " " <<  duration << endl;

    long duration1 = chrono::duration_cast<chrono::microseconds>(end1 - start1).count(); 
    cout << endl << "Время сортировки SelectionSort:" << " " << duration1 << endl;

    long duration2 = chrono::duration_cast<chrono::microseconds>(end2 - start2).count(); 
    cout << endl << "Время сортировки  BatchersMergeSort:" << " " << duration2 << endl;

    ofstream out("Sorted.txt");
    if (out.is_open()) {
        for (int i = 0; i < N; i++) {
            out << a[i] << "\n";
        }
        out.close();
    }

    if (checkArray(a, N)) {
        cout << "Numbers sorted correctly" << endl;
    }
    else {
        cout << "Numbers sorted incorrectly" << endl;
    }

    return 0;
}
