#include <iostream> //Бибилиотека ввода-вывода
using namespace std; //пространство стандартных имен

int decitich(int bin, int m = 1) { //Рекурсивная функция, для перевода в десятичную систему
    if (bin == 0){ 
        return 0;   //Условие для нуля
    }
    return bin % 10 * m + decitich(bin / 10, 2 * m); //Вызов функции
}

int main() {

    int n;
    cout<<"Введите число:"; 
    cin >> n;
    cout <<"Новое число:" << decitich(n);
    return 0;
}