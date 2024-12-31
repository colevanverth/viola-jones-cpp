#pragma once

#include "vjlearner.h"

class WLearner {
    typedef long waveVal;

    struct Wavelet {

        Wavelet() = default;

        Wavelet(int mLength, int nLength, int rows, int cols, int mPos, int nPos, int scale, bool isNegative)
            : rows(rows), cols(cols), mPos(mPos), nPos(nPos) {
                this->mScaleLength = mLength * scale;
                this->nScaleLength = nLength * scale;
        }

        waveVal getWaveVal(const IntegralImage& img) const;

        bool onImage(int imageLength);

        int mScaleLength;

        int nScaleLength;

        int rows;

        int cols;

        int nPos;

        int mPos;
        
        bool isNegative;

    };

};
