#pragma once

#include <iostream>
#include <string>
#include <sstream>


class Monom {
private:
    double coef;
    int degree;     
public:
    Monom();
    Monom(double c, int d);
    Monom(const Monom&);
    double getCoef() const;
    int getDegree() const;

    void setCoef(double c);
    void setDegree(int d);

    bool operator==(const Monom& other) const;
    bool operator!=(const Monom& other) const;
    bool operator<(const Monom& other) const;
    bool operator>(const Monom& other) const;
    bool operator>=(const Monom& m) const;
    bool operator<=(const Monom& m) const;

    std::string Monom_tostr() const;

    double operator()(double x, double y, double z) const;
    
    Monom operator+(const Monom& m);
    Monom operator-(const Monom& m);
    Monom operator*(const Monom& p);
    Monom operator*(double p);

    const Monom& operator=(const Monom& m);

    
};
