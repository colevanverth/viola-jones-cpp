#pragma once

#include "common.h"
#include "integral_image.h"

class Wavelet {

public:
  typedef long waveVal;

  Wavelet() = default;

  Wavelet(int mLength, int nLength, int rows, int cols, int mPos, int nPos,
          int scale, bool isNegative);

  Wavelet(const Wavelet &other, bool isNegative);

  Wavelet transpose();

  waveVal getWaveVal(const IntegralImage &img) const;

  bool onImage(int imageLength);

  friend void to_json(json &j, const Wavelet &w);

  friend void from_json(const json &j, Wavelet &w);

private:
  int m_mScaleLength;

  int m_nScaleLength;

  int m_rows;

  int m_cols;

  int m_nPos;

  int m_mPos;

  bool m_isNegative;
};
