#include <string>
#include "Polinom.h"
#include <limits>

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
    string expr;
    cout << "Введите первый полином (например, 2x^2y - 3z + 5):\n";
    getline(cin, expr);
    try {
        p1 = Polinom(expr);
        cout << "p1 = " << p1 << endl;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    cout << "Введите второй полином:\n";
    getline(cin, expr);
    try {
        p2 = Polinom(expr);
        cout << "p2 = " << p2 << endl;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: result = p1 + p2; cout << "Результат: " << result << endl; break;
        case 2: result = p1 - p2; cout << "Результат: " << result << endl; break;
        case 3: result = p1 * p2; cout << "Результат: " << result << endl; break;
        case 4:
            cout << "Введите константу: ";
            cin >> scalar;
            
            result = p1 * scalar;
            cout << "Результат: " << result << endl;
            break;
        case 5: cout << (p1 == p2 ? "Равны" : "Не равны") << endl; break;
        case 6: cout << (p1 != p2 ? "Не равны" : "Равны") << endl; break;
        case 7:
            cout << "Введите x, y, z: ";
            cin >> x >> y >> z;
            
            cout << "p1(x,y,z) = " << p1.evaluate(x, y, z) << endl;
            cout << "p2(x,y,z) = " << p2.evaluate(x, y, z) << endl;
            break;
        case 0: cout << "Выход." << endl; break;
        default: cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);

    return 0;
}