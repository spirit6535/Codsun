#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <list>
using namespace std;
void create_vector(vector<int>& v){
    setlocale(LC_ALL, "RUS");
    int add;
    int n;
    cout << "Введите кол-во чисел.\n";
    cin >> n;
    cout << "\nВведите числа.";
    for(int i=0; i < n; ++i){
        cin >> add;
        v.push_back(add);
    }
}

void print_vector(vector<int> v){
        int size = v.size();
        for (int i = 0; i < size; ++i){
            cout <<v[i] <<" ";
        }
            

}

void replace_min_elements(vector<int> &v){
    int size = v.size();
    int min = *min_element(v.begin(),v.end());//берем значение итератора 
    for (int i =0; i < size; ++i){
        if (v[i] % 2 == 0)
        v[i] = min;
    }
}

void delete_max(vector<int> &l) {
    int max = *max_element(l.begin(), l.end());
    for (vector<int>::iterator I = l.begin(); I != l.end();) { //Итератор — это указатель на элементы контейнера она возвращает указатель на начало 
        // до тех пор пока не конец
        int i =*I;
        if (i == max) {
            I = l.erase(I);//удаляет и сразу уменьшает размер контейнера и также он передвигает дальше идущие после удаленного
        }
        else
            ++I;// прибавим только тогда когда не max
    }

}

void remove(vector<int>& nums) {
    sort(nums.begin(), nums.end()); // Сортируем вектор
    nums.erase(unique(nums.begin(), nums.end()), nums.end()); // Удаляем дубликаты
}

int main() { 
    setlocale(LC_ALL, "RUS");
  vector<int> integers;
    create_vector(integers);
    print_vector(integers);
    cout << "\n__________________\n";
    delete_max(integers);
    print_vector(integers);
    cout << "\n ______________\n";
    vector<int> new_integers; //Cоздание нового вектора
    new_integers = integers;
        cout << "\n Новый вектор\n";
        for (int i = 0; i < new_integers.size(); ++i){
            cout <<" " << new_integers[i] <<" ";
        }
    vector<int> new_integers2; //Cоздание нового вектора
    new_integers2 = new_integers;
    replace_min_elements(new_integers2);
    cout << endl;
    print_vector(new_integers2);
    cout << endl;
    remove(new_integers2);
    cout << "\n 2 Новый вектор\n";
    print_vector(new_integers2);
    
        return 0;
}