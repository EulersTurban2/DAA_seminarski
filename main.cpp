#include <iostream>

#include "complex.hpp"
#include "utils.hpp"

int main(int argc,char** argv){

    ComplexVector a(4);
    a[0] = Complex(1,0);
    a[1] = Complex(2,0);
    a[2] = Complex(3,0);
    a[3] = Complex(4,0);

    ComplexVector rez = fft(ifft(a));
    for (int i = 0; i < rez.size() - 1; i++)
    {
        std::cout << rez[i] << ", ";
    }
    std::cout << rez[rez.size() - 1] << std::endl;
    return 0;
}