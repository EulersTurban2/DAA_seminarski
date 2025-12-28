#include <iostream>

#include "complex.hpp"
#include "utils.hpp"

int main(int argc,char** argv){
    Complex tmp(3.0f,1.0f);
    Complex tmp2(0.0f,0.3f);

    tmp = tmp/tmp2;

    std::cout << tmp;
    return 0;
}