#pragma once

#include "wavelet.h" 
#include "common.h"
#include "pool.h"


class WLearner {

public:

    WLearner() = default;

    void train(const std::vector<IntegralImage>& imgs, const std::vector<float>& imgWeights, const std::vector<Prediction>& targets, std::vector<Wavelet>& wavelets);

    std::vector<Prediction> predict(const std::vector<IntegralImage>& imgs); 

    float error(const std::vector<IntegralImage>& imgs, const std::vector<float>& imgWeights, const std::vector<Prediction>& targets); 

    friend void to_json(json& j, const WLearner& wL);

    friend void from_json(const json& j, WLearner& wL);
    
private:

    struct WErrorInfo {

        Wavelet w;

        float error;

        Wavelet::waveVal split;

    };

    struct WSplitInfo {

        float imgWeight;

        Prediction prediction;

        Wavelet::waveVal waveVal;
    };

    Wavelet m_wavelet;

    Wavelet::waveVal m_splitVal;

    float m_error(const Wavelet& w, const Wavelet::waveVal,  const std::vector<IntegralImage>& imgs, const std::vector<float>& imgWeights, const std::vector<Prediction>& targets); 

    WErrorInfo m_bestSplit(const Wavelet& w, const std::vector<IntegralImage>& imgs, const std::vector<float>& imgWeights, const std::vector<Prediction>& targets);

};
