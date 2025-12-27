#include <cmath>

#include "complex.hpp"


float Complex::module() const
{
    return std::sqrt(this->m_real*this->m_real + this->m_imag*this->m_imag);
}

Complex Complex::operator+(const Complex& other ) const {
    return Complex(other.m_real+this->m_real,other.m_imag+this->m_imag);
}

Complex Complex::operator-(const Complex& other ) const {
    return Complex(-other.m_real+this->m_real,-other.m_imag+this->m_imag);
}

Complex Complex::operator*(const Complex& other ) const {
    return Complex(this->m_real*other.m_real-this->m_imag*other.m_imag,this->m_real*other.m_imag+other.m_real*this->m_imag);
}

Complex Complex::operator/(const Complex& other ) const {
    return (*this)*(~other)*(Complex(1/pow(other.module(),2),0));
}

Complex Complex::operator~() const {
    return Complex(this->m_real,-this->m_imag);
}

std::ostream &operator<<(std::ostream &out, const Complex &obj)
{
    out << "Realni dio: " << obj.m_real << "\n" << "Imaginarni dio: " << obj.m_imag << "\n";
    return out;
}

std::istream &operator>>(std::istream &in, Complex &obj)
{
    in >> obj.m_real >> obj.m_imag;
    return in;
}
