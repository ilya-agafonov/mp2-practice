#pragma once

#include "RingList.h"
#include "Monom.h"
#include <iostream>
#include <cmath>

class Polinom : public RingList<Monom> {

public:
    Polinom();
    Polinom(const std::string& expr);
    Polinom(const Polinom& list);
    ~Polinom();

    void insert(const Monom& m);

    Polinom& operator=(const Polinom& other);
    Polinom operator+(const Polinom& other) const;
    Polinom operator-(const Polinom& other) const;
    Polinom operator*(const Polinom& other) const;
    Polinom operator*(double scalar) const;
    bool operator==(const Polinom& other) const;
    bool operator!=(const Polinom& other) const;

    double evaluate(double x, double y, double z) const;

    friend std::ostream& operator<<(std::ostream& out, const Polinom& p);
    friend std::istream& operator>>(std::istream&, Polinom&);
};
