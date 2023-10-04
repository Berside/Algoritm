#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
using namespace std;

void print(std::vector<int> const& input)
{
    for (int i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << ' ';
    }
}

vector <int> sort_10(vector<int> a) {
    int tmp;
    int n = a.size();
    for (int j = (n-1); j > 0; j--) {
        int max_index = j;
        for (int i = j; i >= 0; i --) {
            if (a[i] > a[max_index]) {
                max_index = i; // индекс минимального элемента
            }
        }
        if (j != max_index) {
            tmp = a[j];
            a[j] = a[max_index];
            a[max_index] = tmp;
            print(a);
            cout << endl;
        }
    }
    return a;
}

int compare(const void* x1, const void* x2)   // функция сравнения элементов массива
{
    return (*(int*)x1 - *(int*)x2);              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}

int main()
{
    vector <int> a = {};
    int c [100] = {};
    int n;
    ifstream input("d100.txt");
    for (int i = 0; i < 100; i++)
    {
        input >> n;
        c[i] = n;
        a.push_back(n);
    }
    print(a);
    cout << endl;
    vector <int> b = {};
    vector <int> g = {};
    input.close();
    qsort(c,100, sizeof(int),compare);
    b = sort_10(a);
    print(b);
    for (int i = 0; i < 100; i++) {
        cout << c[i] << " ";
    }
}
