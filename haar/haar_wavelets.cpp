#include "haar_wavelets.h"

std::vector<pixel> HaarWavelets::getFeatures(const Pixels& img) {
    std::vector<pixel> features;
    this->m_rows = img.size();
    this->m_cols = img[0].size();

    for (int m = 0; m < this->m_rows; m++) {
        for (int n = 0; n < this->m_cols; n++) {
            auto optSum = this->m_haar(img, m, n, HAAR1_ROWS, HAAR1_COLS, HAAR1_MLENGTH, HAAR1_NLENGTH, 1);
            if (optSum.has_value()) { features.push_back(optSum.value()); }
            optSum = this->m_haar(img, m, n, HAAR2_ROWS, HAAR2_COLS, HAAR2_MLENGTH, HAAR2_NLENGTH, 1);
            if (optSum.has_value()) { features.push_back(optSum.value()); }
            optSum = this->m_haar(img, m, n, HAAR3_ROWS, HAAR3_COLS, HAAR3_MLENGTH, HAAR3_NLENGTH, 1);
            if (optSum.has_value()) { features.push_back(optSum.value()); }
            optSum = this->m_haar(img, m, n, HAAR4_ROWS, HAAR4_COLS, HAAR4_MLENGTH, HAAR4_NLENGTH, 1);
            if (optSum.has_value()) { features.push_back(optSum.value()); }
        }
    }
    return features;
}


pixel HaarWavelets::m_haarSum(const Pixels& img, int m, int n, int mLength, int nLength) {
    pixel sum = img[m + mLength - 1][n + nLength - 1];
    if (m - 1 >= 0) {
        sum -= img[m - 1][n + nLength - 1];
    }
    if (n - 1 >= 0) {
        sum -= img[m + mLength - 1][n - 1];
    }
    if (n - 1 >= 0 && m - 1 >= 0) {
        sum += img[m - 1][n - 1];
    }
    return sum;
}

std::optional<pixel> HaarWavelets::m_haar(const Pixels& img, int m, int n, int numRows, int numCols, int mLength, int nLength, int scale) {
    int mScaleLength = mLength * scale;
    int nScaleLength = nLength * scale;
    pixel sum = 0;

    if ( m + ( mScaleLength * numRows ) > this->m_rows ) {
        return std::nullopt;
    }
    if ( n + ( nScaleLength * numCols ) > this->m_cols ) {
        return std::nullopt;
    }

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            int mPos = m + (i * mScaleLength);
            int nPos = n + (j * nScaleLength);
            pixel partialSum = this->m_haarSum(img, mPos, nPos, mScaleLength, nScaleLength);
            if ( ( i + j ) % 2 == 0 ) {
                sum += partialSum; 
            }
            else {
                sum -= partialSum;
            }
        }
    }
    return sum;
}
