#include <iostream>
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

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    setlocale(LC_ALL, "Russian");

    while (true) {
        try {
            cout << "Введите полином (например: 2x2y + 3x - 5):\n";
            string expr;
            getline(cin, expr);

            if (expr.empty()) {
                cout << "Ошибка: пустой ввод\n";
                continue;
            }

            Polinom p1(expr);

            showMenu();
            int choice;
            cin >> choice;
            clearInput();

            if (choice == 0) break;

            switch (choice) {
            case 1: {
                cout << "Введите второй полином:\n";
                string expr2;
                getline(cin, expr2);
                Polinom p2(expr2);
                Polinom res = p1 + p2;
                cout << "Результат: " << res << "\n";
                break;
            }
            case 2: {
                cout << "Введите второй полином:\n";
                string expr2;
                getline(cin, expr2);
                Polinom p2(expr2);
                Polinom res = p1 - p2;
                cout << "Результат: " << res << "\n";
                break;
            }
            case 3: {
                cout << "Введите второй полином:\n";
                string expr2;
                getline(cin, expr2);
                Polinom p2(expr2);
                Polinom res = p1 * p2;
                cout << "Результат: " << res << "\n";
                break;
            }
            case 4: {
                cout << "Введите константу: ";
                double k;
                cin >> k;
                clearInput();
                Polinom res = p1 * k;
                cout << "Результат: " << res << "\n";
                break;
            }
            case 5: {
                cout << "Введите второй полином:\n";
                string expr2;
                getline(cin, expr2);
                Polinom p2(expr2);
                cout << (p1 == p2 ? "Полиномы равны\n" : "Полиномы не равны\n");
                break;
            }
            case 6: {
                cout << "Введите второй полином:\n";
                string expr2;
                getline(cin, expr2);
                Polinom p2(expr2);
                cout << (p1 != p2 ? "Полиномы разные\n" : "Полиномы одинаковые\n");
                break;
            }
            case 7: {
                cout << "Введите x, y, z через пробел: ";
                double x, y, z;
                cin >> x >> y >> z;
                clearInput();
                double res = p1.evaluate(x, y, z);
                cout << "Значение полинома: " << res << "\n";
                break;
            }
            default:
                cout << "Неверный выбор\n";
                break;
            }
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
            clearInput();
        }

        cout << "\nПродолжить? (1 - да, 0 - нет): ";
        int cont;
        cin >> cont;
        clearInput();
        if (cont == 0) break;
    }

    return 0;
}