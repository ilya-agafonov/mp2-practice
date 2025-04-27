
#include <string>
#include "Polinom.h"

using namespace std;

void showMenu() {
    cout << "\nВыберите операцию:\n";
    cout << "1. Сложение двух полиномов\n";
    cout << "2. Вычитание двух полиномов\n";
    cout << "3. Умножение двух полиномов\n";
    cout << "4. Умножение на константу\n";
    cout << "5. Сравнение (==)\n";
    cout << "6. Сравнение (!=)\n";
    cout << "7. Вычисление значения полинома\n";
    cout << "0. Выход\n";
    cout << "Ваш выбор: ";
}


int main() {
    setlocale(LC_ALL, "Russian");

    Polinom p1, p2, result;
    int choice;
    double scalar, x, y, z;

    cout << "Введите первый полином (формат: ..., через пробел, конец строки - конец ввода):\n";
    cin >> p1;
    cout << "p1 = " << p1 << endl;

    cout << "Введите второй полином:\n";
    cin >> p2;
    cout << "p2 = " << p2 << endl;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            result = p1 + p2;
            cout << "Результат сложения: " << result << endl;
            break;

        case 2:
            result = p1 - p2;
            cout << "Результат вычитания: " << result << endl;
            break;

        case 3:
            result = p1 * p2;
            cout << "Результат умножения: " << result << endl;
            break;

        case 4:
            cout << "Введите константу: ";
            cin >> scalar;
            result = p1 * scalar;
            cout << "Результат умножения первого полинома на " << scalar << ": " << result << endl;
            break;

        case 5:
            if (p1 == p2)
                cout << "Полиномы равны.\n";
            else
                cout << "Полиномы не равны.\n";
            break;

        case 6:
            if (p1 != p2)
                cout << "Полиномы различны.\n";
            else
                cout << "Полиномы одинаковы.\n";
            break;

        case 7:
            cout << "Введите значения переменных x, y, z через пробел: ";
            cin >> x >> y >> z;
            cout << "Значение первого полинома: " << p1.evaluate(x, y, z) << endl;
            cout << "Значение второго полинома: " << p2.evaluate(x, y, z) << endl;
            break;

        case 0:
            cout << "Выход.\n";
            break;

        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }

    } while (choice != 0);

    return 0;
}