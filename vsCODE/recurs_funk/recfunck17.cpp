#include <iostream> //Библиотека ввода-вывода

using namespace std; //Пространство стандартных имен

void print(int n, int maxn) {
    if (n <= maxn) { 
        for (int i = 1; i <= n; i++) { // цикл для первой цифры
            cout << n; 
        }
        for (int i = 1; i <= (maxn - n) * 2; i++) { // цикл для вывода дефисов
            cout << "-";
        }
        for (int i = 1; i <= n; i++) { // цикл для цифры в конце
            cout << n; 
        }
        cout << endl; // переход на новую строку
        print(n + 1, maxn); // рекурсивный вызов функции с увеличением n
        for (int i = 1; i <= n; i++) { // цикл от 1 до n
            cout << n; 
        }
        for (int i = 1; i <= (maxn - n) * 2; i++) { // цикл для вывода дефисов
            cout << "-";
        }
        for (int i = 1; i <= n; i++) { // цикл от 1 до n
            cout << n; 
        }
        cout << endl; // переход на новую строку
    }
}

int main() {
    int n, max; // объявление переменных n и max
    cout << "Введите начальное число n = "; cin >> n; // вывод текста и ввод значения для n
    cout << "Введите максимальное число n = "; cin >> max; // вывод текста и ввод значения для max
    print(n, max); // вызов функции print с параметрами n и max
    return 0; // возврат значения 0
}
