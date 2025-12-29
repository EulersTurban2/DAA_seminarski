#ifndef __CONVOLUTION_HPP
#define __CONVOLUTION_HPP

#include <vector>

#include "utils.hpp"
#include "matrix.hpp"

// preparing the matrices
void padd_in_the_matrices(Matrix& mat1, Matrix& mat2){
    int mat1_rows = mat1.getNoRows(), mat2_rows = mat2.getNoRows();
    int mat1_cols = mat1.getNoCols(), mat2_cols = mat2.getNoCols();

    int n1 = mat1_rows + mat2_rows - 1;
    int n2 = mat1_cols + mat2_cols - 1;

    int pow2n1 = getNearestPower(n1,2);
    int pow2n2 = getNearestPower(n2,2);

    mat1.add_zero_padding(pow2n1-mat1_rows,pow2n2-mat1_cols);
    mat2.add_zero_padding(pow2n1-mat2_rows,pow2n2-mat2_cols);
}

Matrix& getSpatialDomainResponseMap(Matrix& base, Matrix& templ) {
    padd_in_the_matrices(base,templ);
    Matrix fft_base = fft2d(base);
    Matrix fft_templ = fft2d(templ);
    Matrix fft_r = pointWise(fft_base,fft_templ);
    Matrix spatialDomain = ifft2d(fft_r);
    
    return spatialDomain;
}

#endif