#include "integral_image.h"
#include <iostream>

IntegralImage::IntegralImage(const cv::Mat &img)
    : m_rows(img.rows), m_cols(img.cols) {
  this->m_integralPixels = this->m_matToPixels(img);
  this->m_createIntegral(this->m_integralPixels);
}

IntegralImage::Pixels IntegralImage::m_matToPixels(const cv::Mat &img) {
  std::vector<std::vector<unsigned int>> rows;
  for (int m = 0; m < img.rows; m++) {
    std::vector<unsigned int> column;
    for (int n = 0; n < img.cols; n++) {
      column.push_back(img.at<uchar>(m, n));
    }
    rows.push_back(column);
  }
  return rows;
}

void IntegralImage::m_createIntegral(Pixels &p) {
  for (int m = 0; m < this->m_rows; m++) {
    for (int n = 0; n < this->m_cols; n++) {
      if (m - 1 >= 0) {
        p[m][n] += p[m - 1][n];
      }
      if (n - 1 >= 0) {
        p[m][n] += p[m][n - 1];
      }
      if (m - 1 >= 0 && n - 1 >= 0) {
        p[m][n] -= p[m - 1][n - 1];
      }
    }
  }
}

unsigned int IntegralImage::getSum(int m, int n, int mLength,
                                   int nLength) const {
  unsigned int sum = this->m_integralPixels[m + mLength - 1][n + nLength - 1];
  if (m - 1 >= 0) {
    sum -= this->m_integralPixels[m - 1][n + nLength - 1];
  }
  if (n - 1 >= 0) {
    sum -= this->m_integralPixels[m + mLength - 1][n - 1];
  }
  if (n - 1 >= 0 && m - 1 >= 0) {
    sum += this->m_integralPixels[m - 1][n - 1];
  }
  return sum;
}

unsigned int IntegralImage::getRows() const { return this->m_cols; }

unsigned int IntegralImage::getCols() const { return this->m_rows; }
