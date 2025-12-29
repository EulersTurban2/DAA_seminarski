#include "image.hpp"

Matrix Image::returnMatrix()
{
    return this->gray_scale;
}

void Image::setMatrix(Matrix &mat)
{
    this->gray_scale = mat;
}

cv::Mat Image::returnImage()
{
    std::vector<std::vector<Complex>> elems = this->gray_scale.getElems();
    int rows = elems.size();
    int cols = elems[0].size();

    cv::Mat returner = cv::Mat(rows,cols,CV_8UC1,cv::Scalar(0));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            returner.at<uchar>(i,j) = elems[i][j].real();
        }
    }
    return returner;
}
