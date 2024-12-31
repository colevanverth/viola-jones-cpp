#pragma once 

#include <opencv2/core.hpp>
#include <vector>
#include <iostream>
#include <optional>
#include <algorithm>
#include <limits>
#include "integral_image.h"
#include "wlearner.h"

class VJLearner {

public:

    enum Prediction {
        FACE,
        NON_FACE
    };

    VJLearner() = default;

    VJLearner(int imageSize);

    bool predict(const IntegralImage& img); 

    void train(const std::vector<IntegralImage>& imgs, const std::vector<bool>& targets, int boostAmount);


private:

    /* struct Wavelet; */ 

    /* typedef long waveVal; */

    /* Wavelet m_bestWavelet(const std::vector<IntegralImage>& imgs, std::vector<float>& weights, const std::vector<bool>& targets); */

    /* void m_createWavelets(); */

    int m_imageSize;

    /* struct Wavelet { */

    /*     Wavelet() = default; */

    /*     Wavelet(int mLength, int nLength, int rows, int cols, int mPos, int nPos, int scale, bool isNegative) */
    /*         : rows(rows), cols(cols), mPos(mPos), nPos(nPos) { */
    /*             this->mScaleLength = mLength * scale; */
    /*             this->nScaleLength = nLength * scale; */
    /*     } */

    /*     waveVal getWaveVal(const IntegralImage& img) const; */

    /*     std::vector<Prediction> getPredictions(const std::vector<IntegralImage>& imgs, const std::vector<Prediction>& targets); */

    /*     bool onImage(int imageLength); */

    /*     int mScaleLength; */

    /*     int nScaleLength; */

    /*     int rows; */

    /*     int cols; */

    /*     int nPos; */

    /*     int mPos; */
        
    /*     bool isNegative; */

    /* }; */

    /* std::vector<Wavelet> m_wavelets; */


    /* std::vector<float> m_waveletAlphas; */

    const int H1_MLENGTH = 4;
    const int H1_NLENGTH = 1;
    const int H1_COLS = 2;
    const int H1_ROWS = 1;

    const int H2_MLENGTH = 2;
    const int H2_NLENGTH = 2;
    const int H2_COLS = 1;
    const int H2_ROWS = 2;

    const int H3_MLENGTH = 2;
    const int H3_NLENGTH = 1;
    const int H3_COLS = 3; 
    const int H3_ROWS = 1;

    const int H4_MLENGTH = 1;
    const int H4_NLENGTH = 2;
    const int H4_ROWS = 2;
    const int H4_COLS = 2;

};
