#include "Monom.h"
#include <cmath>
#include <iostream>


Monom::Monom() {
    coef = 0;
    degree = -1;
}

Monom::Monom(double c, int d) {
    coef = c;

    int deg_x = d / 100;      
    int deg_y = (d / 10) % 10; 
    int deg_z = d % 10;       

    if (deg_x > 9 || deg_y > 9 || deg_z > 9) {
        throw std::exception("degree must <= 9");
    }
    if (d >= 0 && d <= 999) {
        degree = d;
    }
    else {
        throw std::exception("Incorrect degree");
    }
   
}

Monom::Monom(const Monom& m) {
    coef = m.coef;
    degree = m.degree;
}

double Monom::getCoef() const {
    return coef;
}
int Monom::getDegree() const {
    return degree;
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

bool Monom::operator>=(const Monom& m) const {
    return degree >= m.degree;
}

bool Monom::operator<=(const Monom& m) const {
    return degree <= m.degree;
}

std::string Monom::Monom_tostr() const {
    std::string s;
    bool is_first_term = (s.empty());
    if (coef > 0) {
        if (!is_first_term) {
            s += "+";  
        }
        if (coef != 1 || degree == 0) {
            std::stringstream ss;
            ss << std::defaultfloat << coef;
            s += ss.str();
        }
    }
    else if (coef < 0) {
        if (coef != -1 || degree == 0) {
            std::stringstream ss;
            ss << std::defaultfloat << coef;
            s += ss.str();
        }
        else {
            s += "-";  
        }
    }
    else {
        return ""; 
    }
    int tmp = degree;
    if (tmp / 100) {  
        s += "x";
        if (tmp / 100 != 1) {
            s += "^" + std::to_string(tmp / 100);
        }
    }
    if ((tmp % 100) / 10) {
        s += "y";
        if ((tmp % 100) / 10 != 1) {
            s += "^" + std::to_string((tmp % 100) / 10);
        }
    }
    if (tmp % 10) {  
        s += "z";
        if (tmp % 10 != 1) {
            s += "^" + std::to_string(tmp % 10);
        }
    }

    return s;
}

double Monom::operator()(double x, double y, double z) const
{
    int d = degree;
    double res = coef;
    if (d / 100) {
        res *= pow(x, d / 100);
    }
    if ((d - 100 * (d / 100)) / 10) {
        res *= pow(y, ((d - 100 * (d / 100)) / 10));
    }
    if (d % 10) {
        res *= pow(z, d % 10);

    }
    return res;
}

Monom Monom::operator+(const Monom& m)
{
    if (degree == m.degree) {
        return Monom(coef + m.coef, degree);
    }
    else {
        throw std::exception("diff degree");
    }
}

Monom Monom::operator-(const Monom& m)
{
    if (degree == m.degree) {
        return Monom(coef - m.coef, degree);
    }
    else {
        throw std::exception("diff degree");
    }
}

Monom Monom::operator*(const Monom& p) 
{
    int x, px, y, py, z, pz;
    x = degree / 100;
    px = p.degree / 100;

    if ((x + px) > 9) {
        throw std::exception("incorrect degree");;
    }
    y = ((degree - 100 * (degree / 100)) / 10);
    py = ((p.degree - 100 * (p.degree / 100)) / 10);
    if ((y + py) > 9) {
        throw std::exception("incorrect degree");;
    }
    z = degree % 10;
    pz = p.degree % 10;
    if ((z + pz) > 9) {
        throw std::exception("incorrect degree");;
    }

    return Monom(coef * p.coef, degree + p.degree);
}

Monom Monom::operator*(double p)
{
    return Monom(coef * p, degree);
}

const Monom& Monom::operator=(const Monom& m) {
    if (this == &m)
    {
        return *this;
    }
    coef = m.coef;
    degree = m.degree;
    return *this;
}


