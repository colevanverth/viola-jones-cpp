#include "wlearner.h"

namespace {
    template <typename T>
    std::vector<T> uniform(const std::vector<T>& v, int amount) {
        std::vector<T> result;
        size_t step = v.size() / amount;
        for (size_t i = 0; i < v.size(); i += step) {
            result.push_back(v[i]);
            if (result.size() == amount) break;
        }
        return result;
    }
}

void WLearner::train(const std::vector<IntegralImage>& imgs, const std::vector<float>& imgWeights, const std::vector<Prediction>& targets, std::vector<Wavelet>& wavelets) {
    Pool<WErrorInfo> pool;
    for (auto& w : wavelets) {
        pool.queue([&] () { return this->m_bestSplit(w, imgs, imgWeights, targets); }); 
    }
    std::vector<WErrorInfo> infos = pool.getReturnVals();

    WErrorInfo bestInfo;
    bestInfo = *std::min_element(infos.begin(), infos.end(), [](const WErrorInfo& i1, const WErrorInfo& i2) {
        return i1.error < i2.error;
    });
    std::cout << "Split: " << bestInfo.split << std::endl;
    this->m_wavelet = bestInfo.w;
    this->m_splitVal = bestInfo.split;
}

WLearner::WErrorInfo WLearner::m_bestSplit(const Wavelet& w, const std::vector<IntegralImage>& imgs, const std::vector<float>& imgWeights, const std::vector<Prediction>& targets) {
    std::vector<WSplitInfo> splitInfos;
    for (int i = 0; i < imgs.size(); i++) {
        splitInfos.push_back({imgWeights[i], targets[i], w.getWaveVal(imgs[i])});
    }
    std::sort(splitInfos.begin(), splitInfos.end(), [](const WSplitInfo& w1, const WSplitInfo& w2) {
            return w1.waveVal < w2.waveVal;
    });

    std::vector<float> faceError, nonFaceError;
    if (splitInfos[0].prediction == Prediction::FACE) {
        faceError.push_back(splitInfos[0].imgWeight);
    }
    else {
        faceError.push_back(0);
    }
    if (splitInfos.back().prediction == Prediction::NON_FACE) {
        nonFaceError.push_back(splitInfos.back().imgWeight);
    }
    else {
        nonFaceError.push_back(0);
    }

    for (int i = 1; i < splitInfos.size(); i++) {
        faceError.push_back(faceError.back() + ( (splitInfos[i].prediction == Prediction::FACE) ? splitInfos[i].imgWeight : 0 ));
    }
    for (int i = splitInfos.size() - 1; i >= 1; i--) {
        nonFaceError.push_back(nonFaceError.back() + ( (splitInfos[i].prediction == Prediction::NON_FACE) ? splitInfos[i].imgWeight : 0));
    }
    std::reverse(nonFaceError.begin(), nonFaceError.end());

    float mError = std::numeric_limits<float>::infinity();
    Wavelet::waveVal bSplit;
    for (int i = 0; i < splitInfos.size(); i++) {
        float error = faceError[i] + nonFaceError[i];
        if (error < mError) {
            bSplit = splitInfos[i].waveVal;
            mError = error;
        }
    }

    return { w, mError, bSplit};
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

