#ifndef __COMPLEX_HPP
#define __COMPLEX_HPP

#include <iostream>

class Complex{
    public:
        Complex() {}
        Complex(float real, float imag): m_real(real), m_imag(imag) {}
        ~Complex() {}

        //functions for complex numbers
        float module() const;
        float angle() const;

        // operators
        Complex operator+(const Complex& other) const;
        Complex operator-(const Complex& other) const;
        Complex operator*(const Complex& other) const;
        Complex operator/(const Complex& other) const;
        Complex operator~() const;
        bool operator==(const Complex& other) const;

        friend std::ostream& operator<<(std::ostream& out, const Complex &obj);
        
        friend std::istream& operator>>(std::istream& in, Complex &obj);
    private:
        float m_real, m_imag;
};

#endif
