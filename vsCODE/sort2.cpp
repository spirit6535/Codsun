#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

// Функция для создания файла и записи в него двумерного массива
void createFileWithArray(const std::string& filename, int n) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                file << rand() % 100 << " ";
            }
            file << "\n";
        }
        file.close();
    } else {
        std::cerr << "Не удалось открыть файл." << std::endl;
    }
}

// Функция для записи отсортированного массива в новый файл
void writeSortedArrayToFile(const std::string& filename, const std::vector<std::vector<int>>& array) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& row : array) {
            for (int val : row) {
                file << val << " ";
            }
            file << "\n";
        }
        file.close();
    } else {
        std::cerr << "Не удалось открыть файл для записи отсортированного массива." << std::endl;
    }
}
// Функция для чтения двумерного массива из файла
std::vector<std::vector<int>> readArrayFromFile(const std::string& filename, int n) {
    std::vector<std::vector<int>> array(n, std::vector<int>(n));
    std::ifstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                file >> array[i][j];
            }
        }
        file.close();
    } else {
        std::cerr << "Не удалось открыть файл." << std::endl;
    }
    return array;
}

// Функция для сортировки столбцов массива методом поразрядной сортировки
void radixSortColumns(std::vector<std::vector<int>>& array) {
    int n = array.size();
    const int maxDigits = 10; // Максимальное количество разрядов для чисел

    for (int col = 0; col < n; ++col) {
        // Применяем поразрядную сортировку для каждого столбца
        std::vector<int> output(n); // Вспомогательный массив для сортировки
        int count[10] = {0}; // Счетчик для каждого разряда

        // Находим максимальное число в столбце, чтобы знать количество разрядов
int maxVal = 0;
for (int i = 0; i < array.size(); ++i) {
    if (array[i][col] > maxVal) {
        maxVal = array[i][col];
    }
}

        // Проходим по каждому разряду
        for (int exp = 1; maxVal/exp > 0; exp *= 10) {
            std::fill_n(count, 10, 0); // Обнуляем счетчик

            // Считаем количество элементов для каждого разряда
            for (int i = 0; i < n; i++)
                count[(array[i][col] / exp) % 10]++;

            // Изменяем count[i], чтобы count[i] содержал позицию этого разряда в output[]
            for (int i = 1; i < 10; i++)
                count[i] += count[i - 1];

            // Строим отсортированный массив
            for (int i = n - 1; i >= 0; i--) {
                output[count[(array[i][col] / exp) % 10] - 1] = array[i][col];
                count[(array[i][col] / exp) % 10]--;
            }

            // Копируем отсортированный массив в array[], чтобы array[] содержал отсортированные числа по текущему разряду
            for (int i = 0; i < n; i++)
                array[i][col] = output[i];
        }

        // Переворачиваем столбец для убывающей сортировки
        std::reverse(array.begin(), array.end());
    }
}

// Вспомогательная функция для слияния двух половин массива
void merge(std::vector<int>& left, std::vector<int>& right, std::vector<int>& bars, bool descending) {
    int nL = left.size();
    int nR = right.size();
    int i = 0, j = 0, k = 0;

    // Слияние двух половин
    while (i < nL && j < nR) {
        if (descending) {
            if (left[i] >= right[j]) {
                bars[k] = left[i];
                i++;
            } else {
                bars[k] = right[j];
                j++;
            }
        } else {
            if (left[i] <= right[j]) {
                bars[k] = left[i];
                i++;
            } else {
                bars[k] = right[j];
                j++;
            }
        }
        k++;
    }

    // Копирование оставшихся элементов, если есть
    while (i < nL) {
        bars[k] = left[i];
        i++; k++;
    }
    while (j < nR) {
        bars[k] = right[j];
        j++; k++;
    }
}

// Функция для сортировки слиянием
void mergeSort(std::vector<int>& array, bool descending) {
    if (array.size() <= 1) return;

    int mid = array.size() / 2;
    std::vector<int> left(array.begin(), array.begin() + mid);
    std::vector<int> right(array.begin() + mid, array.end());

    // Рекурсивно сортируем две половины
    mergeSort(left, descending);
    mergeSort(right, descending);

    // Сливаем отсортированные половины
    merge(left, right, array, descending);
}

// Функция для сортировки строк массива сортировкой слиянием
void mergeSortRows(std::vector<std::vector<int>>& array) {
    int n = array.size();
    for (int i = 0; i < n; ++i) {
        // Каждую третью строку сортируем по убыванию, остальные - по возрастанию
        mergeSort(array[i], i % 3 == 2);
    }
}

void cocktailSortDiagonal(std::vector<std::vector<int>>& array, int startRow, int startCol) {
    bool swapped = true;
    int start = 0;
    int end = array.size() - 1 - startRow; // Уменьшаем размер на startRow, чтобы избежать выхода за пределы массива

    while (swapped) {
        swapped = false;

        // Проходим слева направо
        for (int i = start; i < end; ++i) {
            // Проверяем, не выходим ли мы за пределы массива
            if (startRow + i + 1 >= array.size() || startCol + i + 1 >= array.size()) {
                break; // Выходим из цикла, если вышли за пределы
            }
            if (array[startRow + i][startCol + i] < array[startRow + i + 1][startCol + i + 1]) {
                std::swap(array[startRow + i][startCol + i], array[startRow + i + 1][startCol + i + 1]);
                swapped = true;
            }
        }

        // Если ничего не переместили, то массив отсортирован
        if (!swapped) break;

        // Сдвигаем конечную точку на один элемент назад
        --end;

        // Проходим справа налево
        for (int i = end - 1; i >= start; --i) {
            // Аналогичная проверка на выход за пределы массива
            if (startRow + i + 1 >= array.size() || startCol + i + 1 >= array.size()) {
                break; // Выходим из цикла, если вышли за пределы
            }
            if (array[startRow + i][startCol + i] < array[startRow + i + 1][startCol + i + 1]) {
                std::swap(array[startRow + i][startCol + i], array[startRow + i + 1][startCol + i + 1]);
                swapped = true;
            }
        }

        // Сдвигаем начальную точку на один элемент вперед
        ++start;
    }
}

// Функция для сортировки всех диагоналей, параллельных побочной
void cocktailSortDiagonals(std::vector<std::vector<int>>& array) {
    int n = array.size();
    for (int i = 0; i < n - 1; ++i) {
        cocktailSortDiagonal(array, 0, i);
        if (i != 0) {
            cocktailSortDiagonal(array, i, 0);
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел
    const std::string inputFilename = "array.txt"; // Имя файла для исходного массива
    const std::string outputFilename = "sorted_array.txt"; // Имя файла для отсортированного массива
    int n; // Размерность массива
    std::cout << "Введите размерность массива ";
    std::cin >> n;

    // Создаем файл с массивом
    createFileWithArray(inputFilename, n);

    // Читаем массив из файла
    std::vector<std::vector<int>> array = readArrayFromFile(inputFilename, n);
    int sortType;
    std::cout << "Введите тип сортировки (1 - поразрядная, 2 - слиянием, 3 - перемешиванием): ";
    std::cin >> sortType;

    // Выбор типа сортировки
    switch (sortType) {
        case 1:
            radixSortColumns(array);
            break;
        case 2:
            mergeSortRows(array);
            break;
        case 3:
            cocktailSortDiagonals(array);
            break;
        default:
            std::cerr << "Неверный тип сортировки." << std::endl;
            return 1;
    }

    // После сортировки записываем отсортированный массив в новый файл
    writeSortedArrayToFile(outputFilename, array);

    // Выводим сообщение о успешной записи
    std::cout << "Отсортированный массив был записан в файл " << outputFilename << std::endl;

    // Вывод отсортированного массива
    for (const auto& row : array) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    return 0;
}