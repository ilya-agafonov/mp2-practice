#pragma once

#include <algorithm>
#include <cmath>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "Polinom.h"

Polinom::Polinom() : RingList<Monom>() {}

Polinom::Polinom(const std::string& expr) {
    parseExpression(expr);  
}

void Polinom::parseExpression(const std::string& expr) {
    std::string s = expr;
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());

    size_t pos = 0;
    while (pos < s.size()) {
        size_t next_pos = s.find_first_of("+-", pos + 1);
        if (next_pos == std::string::npos) next_pos = s.size();

        std::string monom_str = s.substr(pos, next_pos - pos);
        if (!monom_str.empty()) {
            try {
                Monom m(monom_str);
                insert(m);
            }
            catch (...) {
                throw  std::invalid_argument("Invalid monom format: " + monom_str);
            }
        }
        pos = next_pos;
    }
}

Polinom::Polinom(const Polinom& other) : RingList<Monom>(other) {}

Polinom::~Polinom() {}

void Polinom::insert(const Monom& m) {
    if (m.getCoef() == 0) return;

    TNode<Monom>* prev = pHead;
    TNode<Monom>* curr = pHead->pNext;

    while (curr != this->pHead && curr->data > m) {
        prev = curr;
        curr = curr->pNext;
    }

    if (curr != this->pHead && curr->data == m) {
       
        double newCoef = curr->data.getCoef() + m.getCoef();
        if (abs(newCoef) == 0) {
            prev->pNext = curr->pNext;
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
    Polinom result(*this);
    TNode<Monom>* tmp = other.pHead->pNext;
    while (tmp != other.pHead) {
        result.insert(tmp->data);
        tmp = tmp->pNext;
    }
    return result;
}

Polinom Polinom::operator-(const Polinom& other) const {
    Polinom result(*this);
    TNode<Monom>* tmp = other.pHead->pNext;
    while (tmp != other.pHead) {
        result.insert(Monom(-tmp->data.getCoef(), tmp->data.getDegree()));
        tmp = tmp->pNext;
    }
    return result;
}

Polinom Polinom::operator*(const Polinom& other) const {
    Polinom result;
    TNode<Monom>* a = pHead->pNext;
    while (a != pHead) {
        TNode<Monom>* b = other.pHead->pNext;
        while (b != other.pHead) {
            result.insert(a->data * b->data);
            b = b->pNext;
        }
        a = a->pNext;
    }
    return result;
}

Polinom Polinom::operator*(double scalar) const {
    Polinom result;
    TNode<Monom>* tmp = pHead->pNext;
    while (tmp != pHead) {
        result.insert(Monom(tmp->data.getCoef() * scalar, tmp->data.getDegree()));
        tmp = tmp->pNext;
    }
    return result;
}

bool Polinom::operator==(const Polinom& other) const {
    TNode<Monom>* a = pHead->pNext;
    TNode<Monom>* b = other.pHead->pNext;

    while (a != pHead && b != other.pHead) {
        if (a->data != b->data ||
            abs(a->data.getCoef() - b->data.getCoef()) > 1e-9) {
            return false;
        }
        a = a->pNext;
        b = b->pNext;
    }
    return a == pHead && b == other.pHead;
}

bool Polinom::operator!=(const Polinom& other) const {
    return !(*this == other);
}

Polinom& Polinom::operator=(const Polinom& other) {
    if (this != &other) {
        RingList<Monom>::operator=(other); 
    }
    return *this;
}

double Polinom::evaluate(double x, double y, double z) const {
    double result = 0.0;
    TNode<Monom>* curr = pHead->pNext;

    while (curr != pHead) {
        double coef = curr->data.getCoef();
        int deg = curr->data.getDegree();

        int x_deg = deg / 100;
        int y_deg = (deg / 10) % 10;
        int z_deg = deg % 10;

        result += coef * std::pow(x, x_deg) * std::pow(y, y_deg) * std::pow(z, z_deg);
        curr = curr->pNext;
    }

    return result;
}

std::ostream& operator<<(std::ostream& os, const Polinom& p) {
    TNode<Monom>* tmp = p.pHead->pNext;
    while (tmp != p.pHead) {
        os << tmp->data << " ";
        tmp = tmp->pNext;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Polinom& p) {
    int count;
    is >> count;
    for (int i = 0; i < count; ++i) {
        Monom m;
        is >> m;
        p.insert(m);
    }
    return is;
}
