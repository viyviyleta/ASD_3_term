#include <iostream>
#include <Windows.h>
using namespace std;

void hanoiTower(int n, int i, int k) {
    if (n == 1) {
        cout << "Переместить диск 1 с " << i << " на " << k << " стержень" << endl;
    }
    else {
        int temporary = 6 - i - k;
        hanoiTower(n - 1, i, temporary);
        cout << "Переместить диск " << n << " с " << i << " на " << k << " стержень" << endl;
        hanoiTower(n - 1, temporary, k);
    }
}

int main() {
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n, i, k;

    cout << "Введите количество дисков n: ";
    cin >> n;

    if (n < 1) {
        cout << "Ошибка! n может быть числом больше илии равным 1" << endl;
        return 1;
    }

    cout << "Введите номер начального стержня i (от 1 до 3): ";
    cin >> i;

    if (i < 1 || i > 3) {
        cout << "Ошибка! Номер стержня должен быть от 1 до 3" << endl;
        return 1;
    }

    cout << "Введите номер стержня k, на который надо переместить пирамиду (от 1 до 3): ";
    cin >> k;

    if ( k < 1 || k > 3) {
        cout << "Ошибка! Номер стержня должен быть от 1 до 3" << endl;
        return 1;
    }

    if (i == k) {
        cout << "Ошибка! Начальный и конечный стержни должны быть разными" << endl;
        return 1;
    }

    hanoiTower(n, i, k);

    return 0;
}
