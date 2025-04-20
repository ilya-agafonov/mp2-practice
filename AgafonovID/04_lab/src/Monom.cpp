#include "Monom.h"
#include <sstream>
#include <iostream>
#include <stdexcept>

Monom::Monom(double c, int d) : coef(c), degree(d) {}

Monom::Monom(const std::string& expr) {
    coef = 1.0;
    degree = 0;

    size_t x_pos = expr.find('x');
    size_t y_pos = expr.find('y');
    size_t z_pos = expr.find('z');

    if (x_pos != std::string::npos) {
        std::string coef_str = expr.substr(0, x_pos);
        if (coef_str.empty() || coef_str == "+") coef = 1.0;
        else if (coef_str == "-") coef = -1.0;
        else coef = stod(coef_str);
    }
    else {
        coef = stod(expr);
        degree = 0;
        return;
    }

    auto parseDegree = [](const std::string& s, size_t pos) {
        if (pos == std::string::npos) return 0;
        if (pos + 1 >= s.size() || s[pos + 1] != '^') return 1;
        return std::stoi(s.substr(pos + 2));
        };

    int x_deg = parseDegree(expr, x_pos);
    int y_deg = parseDegree(expr, y_pos);
    int z_deg = parseDegree(expr, z_pos);

    degree = x_deg * 100 + y_deg * 10 + z_deg;
}

double Monom::getCoef() const {
    return coef;
}
int Monom::getDegree() const { 
    return degree;
}

void Monom::setCoef(double c) {
    coef = c;
}
void Monom::setDegree(int d) {
    degree = d;
}

bool Monom::operator==(const Monom& m) const {
    return degree == m.degree;
}
bool Monom::operator!=(const Monom& m) const {
    return degree != m.degree;
}
bool Monom::operator<(const Monom& m) const {
    return degree < m.degree;
}
bool Monom::operator>(const Monom& m) const {
    return degree > m.degree;
}

Monom Monom::operator*(const Monom& m) const {
    int x = (degree / 100 + m.degree / 100);
    int y = (degree / 10 % 10 + m.degree / 10 % 10);
    int z = (degree % 10 + m.degree % 10);

    if (x > 9 || y > 9 || z > 9) {
        throw std::overflow_error("Degree overflow in multiplication");
    }

    return Monom(coef * m.coef, x * 100 + y * 10 + z);
}

std::istream& operator>>(std::istream& is, Monom& m) {
    double c;
    int x, y, z;
    std::cout << "Введите коэффициент и степени x y z: ";
    is >> c >> x >> y >> z;
    m.coef = c;
    m.degree = x * 100 + y * 10 + z;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Monom& m) {
    int x = m.degree / 100;
    int y = (m.degree / 10) % 10;
    int z = m.degree % 10;
    os << m.coef << "x^" << x << "y^" << y << "z^" << z;
    return os;
}

