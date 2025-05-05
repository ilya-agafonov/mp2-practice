#include <iostream>
#include "Polinom.h"


void showMenu() {
    std::cout << "\nВыберите операцию:\n";
    std::cout << "1. Сложение двух полиномов\n";
    std::cout << "2. Вычитание двух полиномов\n";
    std::cout << "3. Умножение двух полиномов\n";
    std::cout << "4. Умножение на константу\n";
    std::cout << "5. Сравнение (==)\n";
    std::cout << "6. Сравнение (!=)\n";
    std::cout << "7. Вычисление значения полинома\n";
    std::cout << "0. Выход\n";
    std::cout << "Ваш выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    Polinom p1, p2, result;
    int choice;
    double scalar, x, y, z;
    std::string expr;
    std::cout << "Введите первый полином:\n";
    std::getline(std::cin, expr);
    try {
        p1 = Polinom(expr);
        std::cout << "p1 = " << p1 << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    std::cout << "Введите второй полином:\n";
    std::getline(std::cin, expr);
    try {
        p2 = Polinom(expr);
        std::cout << "p2 = " << p2 << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
        case 1: result = p1 + p2; std::cout << "Результат: " << result << std::endl; break;
        case 2: result = p1 - p2; std::cout << "Результат: " << result << std::endl; break;
        case 3: result = p1 * p2; std::cout << "Результат: " << result << std::endl; break;
        case 4:
            std::cout << "Введите константу: ";
            std::cin >> scalar;
            
            result = p1 * scalar;
            std::cout << "Результат: " << result << std::endl;
            break;
        case 5: std::cout << (p1 == p2 ? "Равны" : "Не равны") << std::endl; break;
        case 6: std::cout << (p1 != p2 ? "Не равны" : "Равны") << std::endl; break;
        case 7:
            std::cout << "Введите x, y, z: ";
            std::cin >> x >> y >> z;
            
            std::cout << "p1(x,y,z) = " << p1.evaluate(x, y, z) << std::endl;
            std::cout << "p2(x,y,z) = " << p2.evaluate(x, y, z) << std::endl;
            break;
        case 0: std::cout << "Выход" << std::endl; break;
        default: std::cout << "неверный выбор" << std::endl;
        }
    } while (choice != 0);

    return 0;
}