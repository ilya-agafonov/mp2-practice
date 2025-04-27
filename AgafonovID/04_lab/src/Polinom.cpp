#pragma once
#include <string>
#include <sstream>
#include "Polinom.h"

Polinom::Polinom() {
    
}

Polinom::Polinom(const std::string& expr) {
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
        if (negative) coef = -coef;
        int deg_x = 0, deg_y = 0, deg_z = 0;
        while (pos < str.length() && (str[pos] == 'x' || str[pos] == 'y' || str[pos] == 'z')) {
            char var = str[pos++];
            int degree = 1;

            if (pos < str.length() && str[pos] == '^') {
                pos++;
                if (pos >= str.length() || !isdigit(str[pos])) {
                    throw std::runtime_error("Invalid degree");
                }
                degree = str[pos++] - '0';
            }

            if (var == 'x') deg_x = degree;
            else if (var == 'y') deg_y = degree;
            else if (var == 'z') deg_z = degree;
        }

        int total_degree = deg_x * 100 + deg_y * 10 + deg_z;
        insert(Monom(coef, total_degree));
    }
}

Polinom::Polinom(const Polinom& list) : RingList<Monom>(list) {}

Polinom::~Polinom() {}

void Polinom::insert(const Monom& m) {
    if (m.getCoef() == 0.0) return;

    if (this->pFirst == this->pHead) {
        this->pushBack(m);
        return;
    }

    TNode<Monom>* prev = this->pHead;
    TNode<Monom>* curr = this->pFirst;

    while (curr != this->pHead && curr->data > m) {
        prev = curr;
        curr = curr->pNext;
    }

    if (curr != this->pHead && curr->data.getDegree() == m.getDegree()) {
        double newCoef = curr->data.getCoef() + m.getCoef();
        if (newCoef == 0) {
            prev->pNext = curr->pNext;
            if (curr == this->pFirst)
                this->pFirst = prev->pNext;
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
        if (prev == this->pHead) {
            this->pFirst = newNode;
        }
    }
}

Polinom Polinom::operator+(const Polinom& other) const {
    Polinom res(*this);
    TNode<Monom>* curr = other.pFirst;
    while (curr != other.pHead) {
        res.insert(curr->data);
        curr = curr->pNext;
    }
    return res;
}

Polinom Polinom::operator-(const Polinom& other) const {
    Polinom res(*this);
    TNode<Monom>* curr = other.pFirst;
    while (curr != other.pHead) {
        res.insert(Monom(-curr->data.getCoef(), curr->data.getDegree()));
        curr = curr->pNext;
    }
    return res;
}

Polinom Polinom::operator*(const Polinom& other) const {
    Polinom res;
    TNode<Monom>* curr1 = this->pFirst;
    while (curr1 != this->pHead) {
        TNode<Monom>* curr2 = other.pFirst;
        while (curr2 != other.pHead) {
            res.insert(curr1->data * curr2->data);
            curr2 = curr2->pNext;
        }
        curr1 = curr1->pNext;
    }
    return res;
}

Polinom Polinom::operator*(double scalar) const {
    Polinom res;
    TNode<Monom>* curr = this->pFirst;
    while (curr != this->pHead) {
        res.insert(curr->data * scalar);
        curr = curr->pNext;
    }
    return res;
}


bool Polinom::operator==(const Polinom& other) const {
    TNode<Monom>* curr1 = this->pFirst;
    TNode<Monom>* curr2 = other.pFirst;
    while (curr1 != this->pHead && curr2 != other.pHead) {
        if (!(curr1->data == curr2->data))
            return false;
        curr1 = curr1->pNext;
        curr2 = curr2->pNext;
    }
    return (curr1 == this->pHead && curr2 == other.pHead);
}

bool Polinom::operator!=(const Polinom& other) const {
    return !(*this == other);
}

Polinom& Polinom::operator=(const Polinom& other) {
    if (this == &other) {
        return *this;
    }
    RingList<Monom>::operator=(other);
    return *this;
}

double Polinom::evaluate(double x, double y, double z) const {
    double sum = 0.0;
    TNode<Monom>* curr = this->pFirst;
    while (curr != this->pHead) {
        sum += curr->data(x, y, z);
        curr = curr->pNext;
    }
    return sum;
}

std::ostream& operator<<(std::ostream& out, const Polinom& p) {
    if (p.pFirst == p.pHead) {
        out << "0";
        return out;
    }

    TNode<Monom>* curr = p.pFirst;
    bool firstTerm = true;

    while (curr != p.pHead) {
        std::string monomStr = curr->data.Monom_tostr();

        if (!firstTerm && monomStr[0] != '-') {
            out << "+";
        }

        out << monomStr;
        curr = curr->pNext;
        firstTerm = false;
    }

    return out;
}
std::istream& operator>>(std::istream& in, Polinom& p) {
    std::string expr;
    std::getline(in, expr);
    p = Polinom(expr);
    return in;
}
