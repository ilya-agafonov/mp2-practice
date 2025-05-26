#pragma once

#include "RingList.h"
#include "Monom.h"
#include <iostream>
#include <cmath>
#include <string>

class Polinom {
private:
    RingList<Monom> monom;  
    std::string expression;   

    void updateExpression();  

public:
    Polinom();
    Polinom(const std::string& expr);
    Polinom(const Polinom& other);

    void insert(const Monom& m);

    Polinom& operator=(const Polinom& other);
    Polinom operator+(const Polinom& other) const;
    Polinom operator-(const Polinom& other) const;
    Polinom operator*(const Polinom& other) const;

    Polinom operator+(const Monom& m);
    Polinom operator-(const Monom& m);
    Polinom operator*(const Monom& m);

    Polinom operator+(double ñ) const;
    Polinom operator-(double ñ) const;
    Polinom operator*(double ñ) const;


    bool operator==(const Polinom& other) const;
    bool operator!=(const Polinom& other) const;

    
    double operator()(double x, double y, double z) const;

    friend std::ostream& operator<<(std::ostream& out, const Polinom& p);
    friend std::istream& operator>>(std::istream& in, Polinom& p);
};