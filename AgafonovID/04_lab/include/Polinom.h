#pragma once

#include "RingList.h"
#include "Monom.h"

class Polinom : public RingList<Monom> {
private:
    void parseExpression(const std::string& expr);
public:
    Polinom();
    Polinom(const std::string& expr);
    Polinom(const Polinom& other);
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

    friend std::ostream& operator<<(std::ostream&, const Polinom&);
    friend std::istream& operator>>(std::istream&, Polinom&);
};
