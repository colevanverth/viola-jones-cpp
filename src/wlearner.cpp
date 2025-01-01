#include "wlearner.h"

WLearner::WLearner(std::vector<Wavelet>& wavelets)
    : m_wavelets(wavelets) {}


void WLearner::train(const std::vector<IntegralImage>& imgs, const std::vector<float>& imgWeights, const std::vector<Prediction>& targets) {
    float minMinError = std::numeric_limits<float>::infinity();
    Wavelet bestWavelet;
    Wavelet::waveVal bestBestSplitVal;
    
    for (auto& wavelet : this->m_wavelets) {
        std::vector<Wavelet::waveVal> waveVals;
        for (auto& img : imgs) {
            waveVals.push_back(wavelet.getWaveVal(img));
        }
        float minError = std::numeric_limits<float>::infinity();
        Wavelet::waveVal bestSplitVal;
        for (auto& wVal : waveVals) {
            float error = this->m_error(wavelet, wVal, imgs, imgWeights, targets); 
            if (error < minError) {
                minError = error;
                bestSplitVal = wVal;
            }
        }
        if (minError < minMinError) {
            minMinError = minError;
            bestWavelet = wavelet;
            bestBestSplitVal = bestSplitVal;
        }
    }
    this->m_wavelet = bestWavelet;
    this->m_splitVal = bestBestSplitVal;
}

std::vector<Prediction> WLearner::predict(const std::vector<IntegralImage>& imgs) {
    std::vector<Prediction> predictions;
    for (int i = 0; i < imgs.size(); i++) {
        if (this->m_wavelet.getWaveVal(imgs[i]) <= this->m_splitVal) {
            predictions.push_back(Prediction::NON_FACE);
        }
        else {
            predictions.push_back(Prediction::FACE);
        }
    }
    return predictions;
}

float WLearner::m_error(const Wavelet& w, const Wavelet::waveVal wVal, const std::vector<IntegralImage>& imgs, const std::vector<float>& imgWeights, const std::vector<Prediction>& targets) {
    float error = 0; 
    for (int i = 0; i < imgs.size(); i++) {
        if (w.getWaveVal(imgs[i]) <= wVal && targets[i] == FACE) { 
            error += imgWeights[i];
        }
        else if (w.getWaveVal(imgs[i]) > wVal && targets[i] == NON_FACE) { 
            error += imgWeights[i];
        }
    }
    return error;
}

float WLearner::error(const std::vector<IntegralImage>& imgs, const std::vector<float>& imgWeights, const std::vector<Prediction>& targets) {
    return this->m_error(this->m_wavelet, this->m_splitVal, imgs, imgWeights, targets);
}
