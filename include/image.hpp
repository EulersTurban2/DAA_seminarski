#ifndef __IMAGE_HPP
#define __IMAGE_HPP

#include <string>
#include <opencv2/opencv.hpp>

#include "matrix.hpp"

class Image{
public:
    Image() {}
    Image(const std::string& path){
        cv::Mat img = cv::imread(path,cv::IMREAD_GRAYSCALE);
        if(img.empty()) {
            std::cerr << "Could not load image!" << std::endl;
        }

        int rows = img.rows;
        int cols = img.cols;

        std::vector<std::vector<Complex>> tmp(rows,std::vector<Complex>(cols));

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                float pixelValue = static_cast<float>(img.at<uchar>(i,j));
                tmp[i][j] = Complex(pixelValue,0.0f);
            }
        }        
        this->gray_scale = Matrix(tmp);
    }

    ~Image() {}

    Matrix returnMatrix();
    void setMatrix(Matrix& mat);

    cv::Mat returnImage();

private:
    Matrix gray_scale;
};

#endif