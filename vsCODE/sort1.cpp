#include <iostream>//для ввода
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

struct Employee {
    std::string name; // Имя
    std::string profession;// Должность
    int day, month, year; // День, месяц, год рождения
    int experience;//стаж
    int salary;//зарплата
};

std::vector<Employee> read_data(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Employee> data;
    Employee employee;
    char dot; // Для чтения точек в дате

    while (file >> employee.name >> employee.profession >> employee.day >> dot >> employee.month >> dot >> employee.year 
           >> employee.experience >> employee.salary) {
        data.push_back(employee);
    }

    return data;
}


void lsd_radix_sort(std::vector<Employee>& data, int max_digit) {
    for (int digit = 0; digit < max_digit; ++digit) {
        std::vector<Employee> buckets[10];

        for (Employee& employee : data) {
            int current_digit = (employee.salary / static_cast<int>(pow(10, digit))) % 10;//вычисляется значение текущего разряда в зарплате сотрудника 
            buckets[current_digit].push_back(employee);                                        
        }

        data.clear();//чистим вектор для заполнения его новыми отсортированными данными 
        for (int i = 0; i < 10; ++i) {
            data.insert(data.end(), buckets[i].begin(), buckets[i].end());
        }
    }
}

void write_data(const std::string& filename, const std::vector<Employee>& data) {
    std::ofstream file(filename);

    for (const Employee& employee : data) {
        file << std::left << std::setw(15) << employee.name
             << std::setw(15) << employee.profession
             << std::setw(2) << std::setfill('0') << employee.day << "."
             << std::setw(2) << std::setfill('0') << employee.month << "."
             << std::setw(4) << employee.year << std::setfill(' ') // Добавляем пробел
             << " " // Пробел между датой и опытом
             << std::setw(5) << employee.experience 
             << std::setw(10) << employee.salary << std::endl;
    }
}

// Сортировка слиянием по зарплате, затем по году рождения
void merge_sort(vector<Employee>& data, int left, int right, bool (*compare)(const Employee&, const Employee&)) {
        if (left >= right) return; //если подмассив содержит 0 или 1 элемент, он уже отсортирован.


        int mid = left + (right - left) / 2; // Находим середину подмассива.

    merge_sort(data, left, mid, compare);//На этом этапе у нас есть два отсортированных подмассива: от `left` до `mid` и от `mid+1` до `right`
    merge_sort(data, mid + 1, right, compare);

        vector<Employee> temp(right - left + 1); // Создаем временный вектор для хранения отсортированного результата.

        int i = left, j = mid + 1, k = 0; // Инициализируем индексы для левого подмассива (i), правого подмассива (j) и временного вектора (k).

        while (i <= mid && j <= right) { // Сравниваем элементы из левого и правого подмассивов и помещаем меньший элемент во временный вектор.
        if (compare(data[i], data[j])) {
            temp[k++] = data[i++];
        } else {
            temp[k++] = data[j++];
        }
    }

        while (i <= mid) temp[k++] = data[i++]; // Копируем оставшиеся элементы из левого подмассива (если они есть) во временный вектор.
    while (j <= right) temp[k++] = data[j++]; // Копируем оставшиеся элементы из правого подмассива (если они есть) во временный вектор.
    //если чет

        for (int p = 0; p < k; p++) { // Копируем отсортированный результат из временного вектора обратно в исходный вектор.
        data[left + p] = temp[p];
    }
}


// Функции сравнения для сортировки слиянием
bool compare_salary(const Employee& a, const Employee& b) {
    if (a.salary != b.salary) return a.salary < b.salary; // Сначала сравниваем по зарплате.
    return a.year < b.year; // Если зарплаты равны, сравниваем по году рождения.
}


// Сортировка перемешиванием по дате рождения
void shuffle_sort(vector<Employee>& data, bool (*compare)(const Employee&, const Employee&)) {
    for (int i = 0; i < data.size() - 1; i++) {
        for (int j = i + 1; j < data.size(); j++) {
            if (compare(data[j], data[i])) {
                swap(data[i], data[j]);
            }
        }
    }
}

// Функция сравнения для сортировки перемешиванием
bool compare_birthdate(const Employee& a, const Employee& b) {
    if (a.year != b.year) return a.year < b.year;
    if (a.month != b.month) return a.month < b.month;
    return a.day < b.day;
}

int main() {
    std::string input_filename = "employees.txt";
    std::string output_filename = "sorted_employees.txt";

    std::vector<Employee> data = read_data(input_filename);

    // Находим максимальное количество разрядов в зарплате
    int max_salary = 0;
    for (const Employee& employee : data) {
        max_salary = std::max(max_salary, employee.salary);
    }
    int max_digit = 0;
    while (max_salary > 0) {
        max_salary /= 10;
        max_digit++;
    }
    lsd_radix_sort(data, max_digit);

    int sort_type;
    cout << "Выберите вид сортировки:\n";
    cout << "1. По зарплате (LSD)\n";
    cout << "2. По зарплате, затем по году рождения (слияние)\n";
    cout << "3. По дате рождения (перемешивание)\n";
    cin >> sort_type;

    switch (sort_type) {
        case 1:
            lsd_radix_sort(data, max_digit);
            break;
        case 2:
            merge_sort(data, 0, data.size() - 1, compare_salary);
            break;
        case 3:
            shuffle_sort(data, compare_birthdate);
            break;
        default:
            cout << "Неверный тип сортировки. Выход из программы.\n";
            return 1;
    }

    
    write_data(output_filename, data);

    std::cout << "Данные успешно отсортированы и записаны в файл '" << output_filename << "'" << std::endl;

    return 0;
}