#pragma once

#include <iostream>


class Monom {
private:
    double coef;
    int degree; 
public:
    Monom(double c = 0, int d = 0);
    Monom(const std::string& expr);
    double getCoef() const;
    int getDegree() const;

    void setCoef(double c);
    void setDegree(int d);

    bool operator==(const Monom& other) const;
    bool operator!=(const Monom& other) const;
    bool operator<(const Monom& other) const;
    bool operator>(const Monom& other) const;

    Monom operator*(const Monom& m) const;

    friend std::istream& operator>>(std::istream& is, Monom& m);
    friend std::ostream& operator<<(std::ostream&, const Monom&);
};
