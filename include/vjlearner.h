#pragma once 

#include "integral_image.h"
#include "wavelet.h"
#include "wlearner.h"
#include "common.h"

class VJLearner {

public:

    VJLearner() = delete;

    VJLearner(int imageSize, int boostAmount);

    std::vector<Prediction> predict(const std::vector<IntegralImage>& imgs); 

    float error(const std::vector<IntegralImage>& imgs, const std::vector<Prediction>& targets); 

    void train(const std::vector<IntegralImage>& imgs, const std::vector<Prediction>& targets);

private:

    const int WAVELET_STRIDE = 2;

    void m_createWavelets();

    int m_imageSize;

    std::vector<Wavelet> m_wavelets;

    std::vector<WLearner> m_wLearners;

    std::vector<float> m_alphas;

    int m_boostAmount;

    const int H1_MLENGTH = 4, H1_NLENGTH = 1, H1_COLS = 2, H1_ROWS = 1;

    const int H2_MLENGTH = 2, H2_NLENGTH = 2, H2_COLS = 1, H2_ROWS = 2;

    const int H3_MLENGTH = 2, H3_NLENGTH = 1, H3_COLS = 3, H3_ROWS = 1;

    const int H4_MLENGTH = 1, H4_NLENGTH = 2, H4_ROWS = 2, H4_COLS = 2;

};
