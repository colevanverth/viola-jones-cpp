#include "vjlearner.h"

VJLearner::VJLearner(int imageSize)
    : m_imageSize(imageSize) {}

/* VJLearner::waveVal VJLearner::Wavelet::getWaveVal(const IntegralImage& img) const { */
/*     waveVal sum = 0; */
/*     for (int i = 0; i < this->rows; i++) { */
/*         for (int j = 0; j < this->cols; j++) { */
/*             int scaledMPos = this->mPos + (i * this->mScaleLength); int scaledNPos = this->nPos + (j * this->nScaleLength); */
/*             auto pSum = img.getSum(scaledMPos, scaledNPos, this->mScaleLength, this->nScaleLength); */
/*             if ( ( i + j ) % 2 == 0 ) { */
/*                 sum += pSum; */ 
/*             } */
/*             else { */
/*                 sum -= pSum; */
/*             } */
/*         } */
/*     } */
/*     if (!this->isNegative) { return sum; } */
/*     return -sum; */
/* } */

/* bool VJLearner::predict(const IntegralImage& img) { */
/*     // TODO. */
/*     return false; */
/* } */

/* void VJLearner::train(const std::vector<IntegralImage>& imgs, const std::vector<bool>& targets, int boostAmount) { */
/*     this->m_wavelets.clear(); */
/*     this->m_createWavelets(); */

/*     std::vector<float> imgWeights; */
/*     for (auto& _ : imgs) { imgWeights.push_back(1 / imgs.size()); } */

/*     for (int i = 0; i < boostAmount; i++) { */
/*         Wavelet w = this->m_bestWavelet(imgs, imgWeights, targets); */
        
/*     } */
/* } */

/* // Given a wavelet, find the optimal split over a bunch of images. */
/* // Given a wavelet and a split, find the error over a bunch of images. */
/* // Given a wavele and a split, find the predictions from some images. */
/* VJLearner::Wavelet VJLearner::m_bestWavelet(const std::vector<IntegralImage>& imgs, std::vector<float>& weights, const std::vector<bool>& targets) { */
/*     /1* float minMinError = std::numeric_limits<float>::infinity(); *1/ */
/*     /1* Wavelet bestWavelet; *1/ */
    
/*     /1* for (auto& wavelet : this->m_wavelets) { *1/ */
/*     /1*     std::vector<waveVal> waveVals; *1/ */
/*     /1*     for (auto& img : imgs) { *1/ */
/*     /1*         waveVals.push_back(wavelet.getWaveVal(img)); *1/ */
/*     /1*     } *1/ */
/*     /1*     float minError = std::numeric_limits<float>::infinity(); *1/ */
/*     /1*     for (auto& fVal : waveVals) { // Loop over feature values. *1/ */
/*     /1*         float error = 0; *1/ */
/*     /1*         for (int i = 0; i < imgs.size(); i++) { *1/ */
/*     /1*             if (wavelet.getWaveVal(imgs[i]) <= fVal && targets[i]) { // Predict non-face but image is face. *1/ */
/*     /1*                 error += weights[i]; *1/ */
/*     /1*             } *1/ */
/*     /1*             else if (wavelet.getWaveVal(imgs[i]) > fVal && !targets[i]) { // Predict face but image is non-face. *1/ */
/*     /1*                 error += weights[i]; *1/ */
/*     /1*             } *1/ */
/*     /1*         } *1/ */
/*     /1*         if (error < minError) { *1/ */
/*     /1*             minError = error; *1/ */
/*     /1*         } *1/ */
/*     /1*     } *1/ */
/*     /1*     if (minError < minMinError) { *1/ */
/*     /1*         minMinError = minError; *1/ */
/*     /1*         bestWavelet = wavelet; *1/ */
/*     /1*     } *1/ */
/*     /1* } *1/ */
/*     /1* return bestWavelet; *1/ */
/* } */

/* bool VJLearner::Wavelet::onImage(int imageLength) { */
/*     if (this->mPos < 0 || this->nPos < 0) { return false; } */
/*     int mTotalLength = this->mPos + ( this->mScaleLength * this->rows ); */
/*     int nTotalLength = this->nPos + ( this->nScaleLength * this->cols ); */
/*     if (mTotalLength > imageLength || nTotalLength > imageLength) { */
/*         return false; */ 
/*     } */
/*     return true; */
/* } */

/* void VJLearner::m_createWavelets() { */
/*     for (int m = 0; m < this->m_imageSize; m++) { */
/*         for (int n = 0; n < this->m_imageSize; n++) { */
/*             Wavelet w1(H1_MLENGTH, H1_NLENGTH, H1_ROWS, H1_COLS, m, n, 1, false); */
/*             if (w1.onImage(this->m_imageSize)) { */
/*                 this->m_wavelets.push_back(w1); */ 
/*                 w1.isNegative = true; */
/*                 this->m_wavelets.push_back(w1); */
/*             } */
/*             Wavelet w2(H2_MLENGTH, H2_NLENGTH, H2_ROWS, H2_COLS, m, n, 1, false); */
/*             if (w2.onImage(this->m_imageSize)) { */ 
/*                 this->m_wavelets.push_back(w2); */ 
/*                 w2.isNegative = true; */
/*                 this->m_wavelets.push_back(w2); */
/*             } */
/*             Wavelet w3(H3_MLENGTH, H3_NLENGTH, H3_ROWS, H3_COLS, m, n, 1, false); */
/*             if (w3.onImage(this->m_imageSize)) { */
/*                  this->m_wavelets.push_back(w3); */ 
/*                  w3.isNegative = true; */
/*                  this->m_wavelets.push_back(w3); */
/*             } */
/*             Wavelet w4(H4_MLENGTH, H4_NLENGTH, H4_ROWS, H4_COLS, m, n, 1, false); */
/*             if (w4.onImage(this->m_imageSize)) { */
/*                  this->m_wavelets.push_back(w4); */ 
/*                  w4.isNegative = true; */
/*                  this->m_wavelets.push_back(w4); */ 
/*             } */
/*         } */
/*     } */
/* } */
