#include <iostream>//для ввода/вывода
#include <fstream>//для работы с файлами
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


    
    write_data(output_filename, data);

    std::cout << "Данные успешно отсортированы и записаны в файл '" << output_filename << "'" << std::endl;

    return 0;
}