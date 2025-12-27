#include <iostream>

#include "complex.hpp"

int main(int argc,char** argv){
    Complex tmp(3.0f,0.0f);
    Complex tmp2(0.0f,0.3f);

    Complex tmp3 = tmp/tmp2;

    std::cout << tmp3;
    return 0;
}