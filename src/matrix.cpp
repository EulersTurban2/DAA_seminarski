#include <assert.h>

#include "matrix.hpp"


void Matrix::add_zero_padding(const int exp_rows, const int exp_cols){
    int curr_rows = m_elems.size();
    int curr_cols = m_elems[0].size();

    m_elems.resize(curr_rows+exp_rows);
    for (int i = 0; i < m_elems.size(); i++)
    {
        m_elems[i].resize(curr_cols+exp_cols);
    }
}

bool Matrix::check_dimensions(Matrix& other){
    if(this->no_rows == other.no_rows && this->no_cols == other.no_cols)
        return true;
    return false;
}

Matrix Matrix::operator+(const Matrix& other) {
    assert(this->no_rows == other.no_rows && this->no_cols == other.no_cols);
    std::vector<std::vector<Complex>> tmp;
    for (int i = 0; i < no_rows; i++)
    {
        std::vector<Complex> tmp2;
        for (int j = 0; j < no_cols; j++)
        {
            tmp2.push_back(m_elems[i][j]+other.m_elems[i][j]);
        }
        tmp.push_back(tmp2);
    }
    return Matrix(tmp);
}

Matrix Matrix::operator*(const Matrix& other){
    assert(this->no_cols == other.no_rows);
    std::vector<std::vector<Complex>> tmp;
    for (int i = 0; i < no_rows; i++)
    {
        std::vector<Complex> tmp2;
        for (int j = 0; j < other.no_cols; j++)
        {
            Complex sum = Complex();
            for (int k = 0; k < no_cols; k++)
            {
                sum = sum + m_elems[i][k]*other.m_elems[k][j];
            }
            tmp2.push_back(sum);
        }
        tmp.push_back(tmp2);
    }
    return Matrix(tmp);
}
