#ifndef __MATRIX_HPP
#define __MATRIX_HPP

#include <vector>
#include <iostream>
#include <cassert>
#include "complex.hpp"

class Matrix{

public:
    Matrix(const int rows,const int columns): no_rows(rows), no_cols(columns) {
        m_elems.resize(rows);
        for (int i = 0; i < rows; i++)
        {
            m_elems[i].resize(columns);
        }
    }
    Matrix(const std::vector<std::vector<Complex>>& elems) {
        no_rows = elems.size();
        assert(!(no_rows == 0));
        no_cols = elems[0].size();
        m_elems.resize(no_rows);

        for (int i = 0; i < no_rows; i++)
        {
            m_elems[i].resize(no_cols);
            for (int j = 0; j < no_cols; j++)
            {
                m_elems[i][j] = elems[i][j];
            }
        }
    }
    ~Matrix() {}

    //methods
    void add_zero_padding(const int exp_rows, const int exp_cols);
    bool check_dimensions(Matrix& other);

    int getNoRows() const;
    int getNoCols() const;

    std::vector<Complex> getIthColumn(const int i) const;
    std::vector<Complex> getIthRow(const int i) const;

    //operators
    Matrix operator+(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator~() const;

    friend std::ostream& operator<<(std::ostream& out,const Matrix& obj);
    friend std::istream& operator>>(std::istream& in, Matrix& obj);

    friend Matrix pointWise(const Matrix& mat1, const Matrix& mat2);

private:
    std::vector<std::vector<Complex>> m_elems;
    int no_rows, no_cols;

};

#endif