#include "wlearner.h"

WLearner::waveVal WLearner::Wavelet::getWaveVal(const IntegralImage& img) const {
    waveVal sum = 0;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            int scaledMPos = this->mPos + (i * this->mScaleLength); int scaledNPos = this->nPos + (j * this->nScaleLength);
            auto pSum = img.getSum(scaledMPos, scaledNPos, this->mScaleLength, this->nScaleLength);
            if ( ( i + j ) % 2 == 0 ) {
                sum += pSum; 
            }
            else {
                sum -= pSum;
            }
        }
    }
    if (!this->isNegative) { return sum; }
    return -sum;
}
