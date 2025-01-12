#include "vjlearner.h"

namespace {
    template <typename T>
    void vectorPrint(const std::vector<T>& v) {
        for (const auto& e : v) {
            std::cout << e << " ";
        }
        std::cout << std::endl;
    }
}

VJLearner::VJLearner(int imageSize, int boostAmount)
    : m_imageSize(imageSize), m_boostAmount(boostAmount) {}

std::vector<Prediction> VJLearner::predict(const std::vector<IntegralImage>& imgs) {
    std::vector<Prediction> predictions;
    for (const auto& img : imgs) {
        float total = 0;
        for (int i = 0; i < this->m_boostAmount; i++) {
            total += this->m_alphas[i] * static_cast<float>(this->m_wLearners[i].predict({img})[0]);
        }
        Prediction p = (total <= 0) ? Prediction::NON_FACE : Prediction::FACE;
        predictions.push_back(p);
    }
    return predictions;
}

float VJLearner::error(const std::vector<IntegralImage>& imgs, const std::vector<Prediction>& targets) {
    auto predictions = this->predict(imgs);
    float error = 0;
    for (int i = 0; i < predictions.size(); i++) {
        if (predictions[i] != targets[i]) {
            error += 1;
        }
    }
    return error / imgs.size(); 
}

void VJLearner::train(const std::vector<IntegralImage>& imgs, const std::vector<Prediction>& targets) {
    this->m_wLearners.clear();
    this->m_alphas.clear();
    this->m_createWavelets();

    std::vector<float> imgWeights;
    for (int i = 0; i < imgs.size(); i++) { 
        imgWeights.push_back(1.0f / imgs.size());
    }; 

    for (int i = 0; i < this->m_boostAmount; i++) {
        std::cout << std::endl << "Iteration: " << i << std::endl;
        WLearner learner(this->m_wavelets);
        learner.train(imgs, imgWeights, targets);
        float error = learner.error(imgs, imgWeights, targets); 
        std::cout << "Error: " << error << std::endl;
        this->m_wLearners.push_back(learner);
        if (error == 0) { error = 0.0001; }
        float alpha = 0.5f * log( ( 1 - error ) / error );
        std::cout << "Alpha: " << alpha << std::endl;
        this->m_alphas.push_back(alpha);
        auto predictions = learner.predict(imgs); 
        for (int j = 0; j < imgs.size(); j++) {
            if (predictions[j] == targets[j]) {
                imgWeights[j] *= exp(-alpha); 
            }
            else {
                imgWeights[j] *= exp(alpha);
            }
        }
        float sum = std::accumulate(imgWeights.begin(), imgWeights.end(), 0.0f);
        std::transform(imgWeights.begin(), imgWeights.end(), imgWeights.begin(), [sum](float val) { return val / sum; });
    }
}

void VJLearner::m_createWavelets() {
    for (int m = 0; m < this->m_imageSize; m += this->WAVELET_STRIDE) {
        for (int n = 0; n < this->m_imageSize; n += this->WAVELET_STRIDE) {
            for (int scale : this->WAVELET_BASES) {
                std::vector<Wavelet> wavelets;
                wavelets.push_back({H1_MLENGTH, H1_NLENGTH, H1_ROWS, H1_COLS, m, n, scale, false});
                wavelets.push_back(wavelets.back().transpose());
                wavelets.push_back({H2_MLENGTH, H2_NLENGTH, H2_ROWS, H2_COLS, m, n, scale, false});
                wavelets.push_back(wavelets.back().transpose());
                wavelets.push_back({H3_MLENGTH, H3_NLENGTH, H3_ROWS, H3_COLS, m, n, scale, false});
                wavelets.push_back(wavelets.back().transpose());
                wavelets.push_back({H4_MLENGTH, H4_NLENGTH, H4_ROWS, H4_COLS, m, n, scale, false});
                wavelets.push_back(wavelets.back().transpose());
                for (auto& w : wavelets) {
                    if (w.onImage(this->m_imageSize)) {
                        this->m_wavelets.push_back(w);
                        this->m_wavelets.push_back(Wavelet(w, true));
                    }
                }
            }
        }
    }
    std::cout << "Wavelets: " << this->m_wavelets.size() << std::endl;
}
