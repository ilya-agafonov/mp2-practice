#include "Polinom.h"
#include <sstream>
#include <algorithm>

Polinom::Polinom() : expression("0") {}

Polinom::Polinom(const std::string& expr) {
    //std::cout << "expr: " << expr << std::endl;
    std::string str = expr;
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

    size_t pos = 0;
    while (pos < str.length()) {
        bool negative = false;
        if (str[pos] == '-') {
            negative = true;
            pos++;
        }
        else if (str[pos] == '+') {
            pos++;
        }

        double coef = 1.0;
        if (isdigit(str[pos]) || str[pos] == '.') {
            size_t end_pos;
            coef = stod(str.substr(pos), &end_pos);
            pos += end_pos;
        }
        if (negative) {
            coef = -coef;
        }

        int deg_x = 0, deg_y = 0, deg_z = 0;
        while (pos < str.length() && (str[pos] == 'x' || str[pos] == 'y' || str[pos] == 'z')) {
            char var = str[pos++];
            int degree = 1;

            if (pos < str.length() && str[pos] == '^') {
                pos++;
                if (pos >= str.length() || !isdigit(str[pos])) {
                    throw std::exception("Invalid degree");
                }
                degree = str[pos++] - '0';
                while (pos < str.length() && isdigit(str[pos])) {
                    degree = degree * 10 + (str[pos] - '0');
                    pos++;
                }
                if (degree > 9) {
                    throw std::exception("Degree > 9");
                }
            }

            if (var == 'x') deg_x = degree;
            else if (var == 'y') deg_y = degree;
            else if (var == 'z') deg_z = degree;
        }

        int total_degree = deg_x * 100 + deg_y * 10 + deg_z;
        if (total_degree < 0 || total_degree > 999) {
            throw std::exception("Degree out of range (0-999)");
        }

        insert(Monom(coef, total_degree));
    }
    updateExpression();
}

Polinom::Polinom(const Polinom& other) : monom(other.monom) {
    updateExpression();
}

void Polinom::updateExpression() {
    std::ostringstream oss;
    if (monom.isEmpty()) {
        oss << "0";
    }
    else {
        bool firstTerm = true;
        TNode<Monom>* curr = monom.getFirst();
        while (curr != monom.getHead()) {
            std::string monomStr = curr->data.Monom_tostr();
            if (!firstTerm && monomStr[0] != '-') {
                oss << "+";
            }
            oss << monomStr;
            curr = curr->pNext;
            firstTerm = false;
        }
    }
    expression = oss.str();
}

void Polinom::insert(const Monom& m) {
    if (m.getCoef() == 0.0) return;

    if (monom.isEmpty()) {
        monom.pushBack(m);
        updateExpression();
        return;
    }

    TNode<Monom>* prev = monom.getHead();
    TNode<Monom>* curr = monom.getFirst();

    while (curr != monom.getHead() && curr->data > m) {
        prev = curr;
        curr = curr->pNext;
    }

    if (curr != monom.getHead() && curr->data.getDegree() == m.getDegree()) {
        double newCoef = curr->data.getCoef() + m.getCoef();
        if (newCoef == 0.0) {
            prev->pNext = curr->pNext;
            if (curr == monom.getFirst()) {
                monom.setFirst(prev->pNext);
            }
            delete curr;
        }
        else {
            curr->data.setCoef(newCoef);
        }
    }
    else {
        TNode<Monom>* newNode = new TNode<Monom>(m);
        prev->pNext = newNode;
        newNode->pNext = curr;
        if (prev == monom.getHead()) {
            monom.setFirst(newNode);
        }
    }
    updateExpression();
}

Polinom Polinom::operator+(const Polinom& other) const {
    Polinom res(*this);
    TNode<Monom>* curr = other.monom.getFirst();
    while (curr != other.monom.getHead()) {
        res.insert(curr->data);
        curr = curr->pNext;
    }
    return res;
}

Polinom Polinom::operator-(const Polinom& other) const {
    Polinom res(*this);
    TNode<Monom>* curr = other.monom.getFirst();
    while (curr != other.monom.getHead()) {
        res.insert(Monom(-curr->data.getCoef(), curr->data.getDegree()));
        curr = curr->pNext;
    }
    return res;
}

Polinom Polinom::operator*(const Polinom& other) const {
    Polinom res;
    TNode<Monom>* curr1 = this->monom.getFirst();
    while (curr1 != this->monom.getHead()) {
        TNode<Monom>* curr2 = other.monom.getFirst();
        while (curr2 != other.monom.getHead()) {
            res.insert(curr1->data * curr2->data);
            curr2 = curr2->pNext;
        }
        curr1 = curr1->pNext;
    }
    return res;
}

Polinom Polinom::operator+(const Monom& m)
{
    Polinom p(*this);
    Monom m1(m);
    p.insert(m1);
    return p;
}


Polinom Polinom::operator*(double scalar) const {
    Polinom res;
    TNode<Monom>* curr = this->monom.getFirst();
    while (curr != this->monom.getHead()) {
        res.insert(curr->data * scalar);
        curr = curr->pNext;
    }
    return res;
}

bool Polinom::operator==(const Polinom& other) const {
    TNode<Monom>* curr1 = this->monom.getFirst();
    TNode<Monom>* curr2 = other.monom.getFirst();
    while (curr1 != this->monom.getHead() && curr2 != other.monom.getHead()) {
        if (!(curr1->data == curr2->data))
            return false;
        curr1 = curr1->pNext;
        curr2 = curr2->pNext;
    }
    return (curr1 == this->monom.getHead() && curr2 == other.monom.getHead());
}

Polinom& Polinom::operator=(const Polinom& other) {
    if (this == &other) {
        return *this;
    }
    monom = other.monom;
    updateExpression();
    return *this;
}

bool Polinom::operator!=(const Polinom& other) const {
    return !(*this == other);
}

double Polinom::operator()(double x, double y, double z) const {
    double res = 0.0;
    
    
    return res;
}

std::ostream& operator<<(std::ostream& out, const Polinom& p) {
    out << p.expression;
    return out;
}

std::istream& operator>>(std::istream& in, Polinom& p) {
    std::string expr;
    std::getline(in, expr);
    p = Polinom(expr);
    return in;
}