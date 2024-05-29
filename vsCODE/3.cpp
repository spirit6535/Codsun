#include <iostream>
#include <vector> 
#include <cmath> 
using namespace std;

// Функция для вычисления степеней числа
vector<double> degree_calculation(double degree_base, int max_degree) {
    vector<double> degree_number; // Создание вектора для хранения степеней числа
    for (int i = 1; i <= max_degree; ++i) { // Цикл от 1 до max_degree
        degree_number.push_back(pow(degree_base, i)); // Добавление i-й степени числа degree_base в вектор degree_number
    }//pow возводит первый аргумент (degree_base) в степень второго аргумента (i).
     //push_back добовляет в конец вектора результат вычисления pow
    return degree_number; 
}

// Функция для вывода степеней числа
template <typename T>
void print_vector(vector<T> v){
    int size = v.size();
    for (int i = 0; i < size; ++i){
        cout << v[i] << " ";
    }
    cout << endl;
}

int main() { // Главная функция программы
    setlocale(LC_ALL, "RUS");
    double degree_base; // основания степени
    cout << "\n Введите основание степени\n";
    cin >> degree_base;
    int max_degree; // максимальной степени
    cout << "\n Введите максимальную степени\n";
    cin >> max_degree;

    vector<double> degree_number = degree_calculation(degree_base, max_degree); // Вычисление степеней числа degree_base
    cout << "Первые " << max_degree << " степеней числа " << degree_base << ":\n"; // Вывод информационного сообщения
    print_vector(degree_number); // Вывод степеней числа

    return 0; // Завершение программы с кодом 0 (успешное выполнение)
}