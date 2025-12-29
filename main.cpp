#include <iostream>

#include "complex.hpp"
#include "matrix.hpp"
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
    std::cout << std::endl;
    
    std::vector<ComplexVector> test;
    for (int i = 0; i < 4; i++)
    {
        test.push_back(a);
    }

    Matrix mat = Matrix(test);
    std::cout << mat << std::endl;
    std::cout << std::endl;
    mat.add_zero_padding(4,4);
    Matrix mat2 = ifft2d(fft2d(mat));
    std::cout << mat2 << std::endl;
    return 0;
}