#include "Polinom.h"
#include <math.h>

Polinom::Polinom() {
    expression = "0";
}

Polinom::Polinom(const std::string& expr) {
    expression = expr;
    monom.clear();

    if (expr.empty()) {
        return;
    }

    size_t pos = 0;
    while (pos < expr.length()) {
        while (pos < expr.length() && isspace(expr[pos])) {
            pos++;
        }
        if (pos >= expr.length()) {
            break;
        }

        int sign = 1;
        if (expr[pos] == '+') {
            pos++;
        }
        else if (expr[pos] == '-') {
            sign = -1;
            pos++;
        }

        double coef = 1.0;
        bool hasCoef = false;
        if (pos < expr.length() && (isdigit(expr[pos]) || expr[pos] == '.')) {
            hasCoef = true;
            coef = 0;
            bool hasFraction = false;
            double fraction = 0.1;

            while (pos < expr.length() && (isdigit(expr[pos]) || expr[pos] == '.')) {
                if (expr[pos] == '.') {
                    if (hasFraction) {
                        throw std::invalid_argument("Invalid coefficient format");
                    }
                    hasFraction = true;
                    pos++;
                    continue;
                }

                if (!hasFraction) {
                    coef = coef * 10 + (expr[pos] - '0');
                }
                else {
                    coef += (expr[pos] - '0') * fraction;
                    fraction *= 0.1;
                }
                pos++;
            }
        }
        coef *= sign;

        int degree = 0;
        bool hasVariables = false;

        while (pos < expr.length() && (expr[pos] == 'x' || expr[pos] == 'y' || expr[pos] == 'z')) {
            hasVariables = true;
            char var = expr[pos++];
            int power = 1;

            if (pos < expr.length() && expr[pos] == '^') {
                pos++;
                power = 0;
                while (pos < expr.length() && isdigit(expr[pos])) {
                    power = power * 10 + (expr[pos] - '0');
                    pos++;
                }

                if (power > 9) {
                    throw std::invalid_argument("Degree must be <= 9");
                }
            }

            switch (var) {
            case 'x': degree += 100 * power; break;
            case 'y': degree += 10 * power; break;
            case 'z': degree += power; break;
            }
        }

        if (!hasCoef && !hasVariables) {
            throw std::invalid_argument("Invalid term format");
        }

        if (hasCoef && !hasVariables) {
            degree = 0;
        }

        if (coef != 0) {
            insert(Monom(coef, degree));
        }
    }
}

Polinom::Polinom(const Polinom& other) {
    expression = other.expression;
    monom = other.monom;
}

void Polinom::insert(const Monom& m) {
    if (m.getCoef() == 0) return;

    TNode<Monom>* current = monom.getFirst();
    TNode<Monom>* prev = nullptr;

    while (current != nullptr && current->data.getDegree() > m.getDegree()) {
        prev = current;
        current = current->pNext;
    }

    if (current != nullptr && current->data.getDegree() == m.getDegree()) {
        Monom newMonom = current->data + m;
        if (newMonom.getCoef() == 0) {
            if (prev == nullptr) {
                monom.removefirst();
            }
            else {
                monom.remove(current->data);
            }
        }
        else {
            current->data = newMonom;
        }
    }
    else {
        TNode<Monom>* newNode = new TNode<Monom>(m);
        if (prev == nullptr) {
            monom.pushFront(newNode);
        }
        else {
            newNode->pNext = current;
            prev->pNext = newNode;
        }
    }

    updateExpression();
}

void Polinom::updateExpression() {
    expression.clear();
    bool firstTerm = true;

    TNode<Monom>* current = monom.getFirst();
    while (current != nullptr) {
        std::string term = current->data.Monom_tostr();

        if (!term.empty()) {
            if (!firstTerm && term[0] != '-') {
                expression += "+";
            }
            expression += term;
            firstTerm = false;
        }

        current = current->pNext;
    }

    if (expression.empty()) {
        expression = "0";
    }
}

Polinom& Polinom::operator=(const Polinom& other) {
    if (this != &other) {
        monom = other.monom;
        expression = other.expression;
    }
    return *this;
}

Polinom Polinom::operator+(const Polinom& other) const {
    Polinom result(*this);

    TNode<Monom>* current = other.monom.getFirst();
    while (current != nullptr) {
        result.insert(current->data);
        current = current->pNext;
    }

    return result;
}

Polinom Polinom::operator-(const Polinom& other) const {
    Polinom result(*this);

    TNode<Monom>* current = other.monom.getFirst();
    while (current != nullptr) {
        result.insert(current->data * -1.0);
        current = current->pNext;
    }

    return result;
}

Polinom Polinom::operator*(const Polinom& other) const {
    Polinom result;

    TNode<Monom>* thisCurrent = monom.getFirst();
    while (thisCurrent != nullptr) {
        TNode<Monom>* otherCurrent = other.monom.getFirst();
        while (otherCurrent != nullptr) {
            Monom product = thisCurrent->data * otherCurrent->data;
            result.insert(product);
            otherCurrent = otherCurrent->pNext;
        }
        thisCurrent = thisCurrent->pNext;
    }

    return result;
}

Polinom Polinom::operator+(const Monom& m) {
    Polinom result(*this);
    Monom m1(m);
    result.insert(m1);
    return result;
}

Polinom Polinom::operator-(const Monom& m) {
    Polinom result(*this);
    Monom m1(m.getDegree(), -m.getDegree());
    result.insert(m1);
    return result;
}

Polinom Polinom::operator*(const Monom& m) {
    Polinom result;

    TNode<Monom>* current = monom.getFirst();
    while (current != nullptr) {
        Monom product = current->data * m;
        result.insert(product);
        current = current->pNext;
    }

    return result;
}

Polinom Polinom::operator+(double c) const {
    Polinom result(*this);
    result.insert(Monom(c, 0));
    return result;
}

Polinom Polinom::operator-(double c) const {
    Polinom result(*this);
    result.insert(Monom(-c, 0));
    return result;
}

Polinom Polinom::operator*(double c) const {
    Polinom result;

    TNode<Monom>* current = monom.getFirst();
    while (current != nullptr) {
        Monom product = current->data * c;
        result.insert(product);
        current = current->pNext;
    }

    return result;
}

bool Polinom::operator==(const Polinom& other) const {
    return monom == other.monom;
}

bool Polinom::operator!=(const Polinom& other) const {
    return !(*this == other);
}

double Polinom::operator()(double x, double y, double z) const {
    double result = 0.0;

    TNode<Monom>* current = monom.getFirst();
    while (current != nullptr) {
        result += current->data(x, y, z);
        current = current->pNext;
    }

    return result;
}

std::ostream& operator<<(std::ostream& out, const Polinom& p) {
    out << p.expression;
    return out;
}

std::istream& operator>>(std::istream& in, Polinom& p) {
    std::string expr;
    getline(in, expr);
    p = Polinom(expr);
    return in;
}