#include <iostream> //Библиотека ввода-вывода
using namespace std;  //Пространство стандартных имен

double H_rec(int n, double x) {  //Рекурсивная функция
    if (n == 0) {       //Условие
        return 1.0;
    }
    if (n == 1) {          //Условие
        return 2.0 * x;  
    }
    return 2.0 * H_rec(n - 1, x) - 2.0  * (n - 1) * H_rec(n - 2, x); //Вызов рекурсии
}

double H(int n, double x) {  // Нерекурсивная функция
    if (n == 0) { 
        return 1;
    }
    if (n == 1) {
        return 2.0 * x;
    }
    double h1 = 1.0;
    double h2 = 2.0 * x;
    for (int i = 2; i <= n; ++i) {
        double q = 2.0 * h2 - 2.0 * (i - 1) * h1;
        h1 = h2;
        h2 = q;  //Перезаписываем элементы, нужные для подсчета следующего
    }
    return h2;
}

int main() {
    int n;cout<<"Введите число:";cin>>n;
    int x; cout<<"Введите коэф x: "; cin>>x;

    cout <<"Рекурсивная функция: " << H_rec(n, x) << "\n";
    cout <<"Функция:"<< H(n, x) << "\n";

    return 0;
}
