#pragma once

#include "integral_image.h"

class Wavelet {

public:

    typedef long waveVal;

    Wavelet() = default;

    Wavelet(int mLength, int nLength, int rows, int cols, int mPos, int nPos, int scale, bool isNegative);

    Wavelet(const Wavelet& other, bool isNegative); 

    waveVal getWaveVal(const IntegralImage& img) const;

    bool onImage(int imageLength);

private:

    int m_mScaleLength;

    int m_nScaleLength;

    int m_rows;

    int m_cols;

    int m_nPos;

    int m_mPos;
    
    bool m_isNegative;

};
