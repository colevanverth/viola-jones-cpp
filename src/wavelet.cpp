#include "wavelet.h"

Wavelet Wavelet::transpose() {
    Wavelet t = *this;
    std::swap(t.m_rows, t.m_cols);
    std::swap(t.m_mScaleLength, t.m_nScaleLength);
    return t;
}

Wavelet::Wavelet(int mLength, int nLength, int rows, int cols, int mPos, int nPos, int scale, bool isNegative)
    : m_rows(rows), m_cols(cols), m_mPos(mPos), m_nPos(nPos) {
        this->m_mScaleLength = mLength * scale;
        this->m_nScaleLength = nLength * scale;
}

Wavelet::waveVal Wavelet::getWaveVal(const IntegralImage& img) const {
    waveVal sum = 0;
    for (int i = 0; i < this->m_rows; i++) {
        for (int j = 0; j < this->m_cols; j++) {
            int scaledMPos = this->m_mPos + (i * this->m_mScaleLength); 
            int scaledNPos = this->m_nPos + (j * this->m_nScaleLength);
            auto pSum = img.getSum(scaledMPos, scaledNPos, this->m_mScaleLength, this->m_nScaleLength);
            if ( ( i + j ) % 2 == 0 ) {
                sum += pSum; 
            }
            else {
                sum -= pSum;
            }
        }
    }
    if (!this->m_isNegative) { return sum; }
    return -sum;
}

bool Wavelet::onImage(int imageLength) {
    if (this->m_mPos < 0 || this->m_nPos < 0) { return false; }
    int mTotalLength = this->m_mPos + ( this->m_mScaleLength * this->m_rows );
    int nTotalLength = this->m_nPos + ( this->m_nScaleLength * this->m_cols );
    if (mTotalLength > imageLength || nTotalLength > imageLength) {
        return false; 
    }
    return true;
}

Wavelet::Wavelet(const Wavelet& other, bool isNegative) {
    *this = other;
    this->m_isNegative = isNegative;
}
