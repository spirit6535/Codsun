#include <string>
#include <iostream>

using namespace std;

struct tochka {
    double x;
    double y;
};

void treug() {
    tochka A;
    tochka B;
    tochka C;
    int* X = new int[10];
    int* Y = new int[10];
    for (int i = 0; i < 10; i++) {
        X[i] = i;
        Y[i] = i;
    }

    cout << "Введите координаты точки A:"; cout << endl;
    cin >> A.x; cin >> A.y;
    cout << "Введите координаты точки B:"; cout << endl;
    cin >> B.x; cin >> B.y;
    cout << "Введите координаты точки C:"; cout << endl;
    cin >> C.x; cin >> C.y;

    int k = 0;
    for (int i = 0; i < 10; i++) {
        if ((((A.x - X[i]) * (B.y - A.y) - (B.x - A.x) * (A.y - Y[i])) >= 0 &&
            ((B.x - X[i]) * (C.y - B.y) - (C.x - B.x) * (B.y - Y[i])) >= 0 &&
            ((C.x - X[i]) * (A.y - C.y) - (A.x - C.x) * (C.y - Y[i])) >= 0) ||
            (((A.x - X[i]) * (B.y - A.y) - (B.x - A.x) * (A.y - Y[i])) < 0 &&
                ((B.x - X[i]) * (C.y - B.y) - (C.x - B.x) * (B.y - Y[i])) < 0 &&
                ((C.x - X[i]) * (A.y - C.y) - (A.x - C.x) * (C.y - Y[i])) < 0)) {
            k++;
        }
    }
    if (k == 2 && k == 3 && k == 4) {
        cout << "Внутри треугольника " << k << " точки";
    }
    else if (k == 1) {
        cout << "Внутри треугольника " << k << " точка";
    }
    else {
        cout << "Внутри треугольника " << k << " точек";
    }

}

int main() {
    setlocale(LC_ALL, "RUS");
    treug();
}


//1 1      4 5     2 3      
//3 2      5 7     6 4
//0 0      3 0     0 3