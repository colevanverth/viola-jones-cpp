#pragma once

#include "wavelet.h" 
#include "common.h"

class WLearner {

public:

    WLearner() = delete;

    WLearner(std::vector<Wavelet>& wavelets);

    void train(const std::vector<IntegralImage>& imgs, const std::vector<float>& imgWeights, const std::vector<Prediction>& targets);

    std::vector<Prediction> predict(const std::vector<IntegralImage>& imgs); 

    float error(const std::vector<IntegralImage>& imgs, const std::vector<float>& imgWeights, const std::vector<Prediction>& targets); 

private:

    struct WErrorInfo {

        Wavelet w;

        float error;

        Wavelet::waveVal split;

    };

    const int TRAINING_STRIDE = 20;

    Wavelet m_wavelet;

    Wavelet::waveVal m_splitVal;

    std::vector<Wavelet>& m_wavelets;

    float m_error(const Wavelet& w, const Wavelet::waveVal,  const std::vector<IntegralImage>& imgs, const std::vector<float>& imgWeights, const std::vector<Prediction>& targets); 

    WErrorInfo m_bestSplit(const Wavelet& w, const std::vector<IntegralImage>& imgs, const std::vector<float>& imgWeights, const std::vector<Prediction>& targets);

};
