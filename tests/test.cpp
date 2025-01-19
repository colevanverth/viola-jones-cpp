#define private public

#include <assert.h>

#include "../include/common.h"
#include "../include/integral_image.h"
#include "../include/vjlearner.h"

const IntegralImage::Pixels f_pixels = {
    {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

IntegralImage f_integralImage;

void f_setIntegralImage() {
  f_integralImage.m_rows = 4;
  f_integralImage.m_cols = 4;
}

void t_createIntegral() {
  auto p = f_pixels;
  f_integralImage.m_createIntegral(p);
  const IntegralImage::Pixels truth = {
      {1, 3, 6, 10}, {6, 14, 24, 36}, {15, 33, 54, 78}, {28, 60, 96, 136}};
  assert(p == truth);
}

int main() {
  f_setIntegralImage();

  t_createIntegral();
}
