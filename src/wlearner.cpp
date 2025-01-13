#include "wlearner.h"

void WLearner::train(const std::vector<IntegralImage>& imgs, const std::vector<float>& imgWeights, const std::vector<Prediction>& targets, const std::vector<Wavelet>& wavelets) {
    Pool<WErrorInfo> pool;
    for (auto& w : wavelets) {
        pool.queue([&] () { return this->m_bestSplit(w, imgs, imgWeights, targets); }); 
    }
    std::vector<WErrorInfo> infos = pool.getReturnVals();

    float minError = std::numeric_limits<float>::infinity();
    WErrorInfo bestInfo;
    for (auto& info : infos) {
        if (info.error < minError) {
            minError = info.error;
            bestInfo = info;
        }
    }
    std::cout << "Best split val: " << bestInfo.split << std::endl;
    std::cout << "Best error: " << bestInfo.error << std::endl;
    this->m_wavelet = bestInfo.w;
    this->m_splitVal = bestInfo.split;
}

WLearner::WErrorInfo WLearner::m_bestSplit(const Wavelet& w, const std::vector<IntegralImage>& imgs, const std::vector<float>& imgWeights, const std::vector<Prediction>& targets) {
    std::vector<Wavelet::waveVal> waveVals;
    for (auto& img : imgs) {
        waveVals.push_back(w.getWaveVal(img));
    }
    float minError = std::numeric_limits<float>::infinity();
    Wavelet::waveVal bestSplitVal;
    for (int i = 0; i < waveVals.size(); i += TRAINING_STRIDE) {
        float error = this->m_error(w, waveVals[i], imgs, imgWeights, targets); 
        if (error < minError) {
            minError = error;
            bestSplitVal = waveVals[i];
        }
    }
    return { w, minError, bestSplitVal };
    
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

void to_json(json& j, const WLearner& wL) {
    j = json{
        {"m_splitVal", wL.m_splitVal},
        {"m_wavelet", wL.m_wavelet}
    };
}

void from_json(const json& j, WLearner& wL) {
    j.at("m_splitVal").get_to(wL.m_splitVal);
    j.at("m_wavelet").get_to(wL.m_wavelet);
}

