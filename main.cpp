#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

#include "utils.hpp"
#include "matrix.hpp"
#include "complex.hpp"

#include "convolution.hpp"

int main(int argc,char** argv){

    ComplexVector a(4);
    a[0] = Complex(1,0);
    a[1] = Complex(2,0);
    a[2] = Complex(3,0);
    a[3] = Complex(4,0);
    
    
    std::vector<ComplexVector> test;
    for (int i = 0; i < 4; i++)
    {
        test.push_back(a);
    }

    std::vector<ComplexVector> test2;
    for (int i = 0; i < 16; i++)
    {
        test2.push_back(a);
    }
    

    Matrix mat = Matrix(test);
    Matrix mat2 = Matrix(test2);

    Matrix res = getSpatialDomainResponseMap(mat2,mat);
    std::cout << res << std::endl;
    std::cout << std::endl;
    Matrix threshold_map = thresholdMap(mat2,res);
    std::cout << threshold_map << std::endl;
    return 0;
}