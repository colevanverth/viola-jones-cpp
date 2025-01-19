#pragma once

#include <opencv2/core.hpp>
#include <vector>

class IntegralImage {

public:
  IntegralImage() = default;

  IntegralImage(const cv::Mat &img);

  unsigned int getSum(int m, int n, int mLength, int nLength) const;

  unsigned int getRows() const;

  unsigned int getCols() const;

private:
  typedef std::vector<std::vector<unsigned int>> Pixels;

  Pixels m_matToPixels(const cv::Mat &img);

  Pixels m_integralPixels;

  void m_createIntegral(Pixels &p);

  unsigned int m_rows;

  unsigned int m_cols;
};
