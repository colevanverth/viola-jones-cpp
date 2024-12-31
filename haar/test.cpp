#define private public

#include "vjlearner.h"
#include "integral_image.h"

int main() {
    /* // INTEGRAL IMAGE TEST. */
    /* IntegralImage::Pixels p; */
    /* std::vector<unsigned int> row1 = {5, 10, 2, 3}; */
    /* std::vector<unsigned int> row2 = {6, 1, 1, 3}; */
    /* std::vector<unsigned int> row3 = {3, 1, 2, 4}; */
    /* std::vector<unsigned int> row4 = {4, 2, 2, 2}; */
    /* p.push_back(row1); */
    /* p.push_back(row2); */
    /* p.push_back(row3); */
    /* p.push_back(row4); */
    /* IntegralImage im; */
    /* im.m_rows = 4; */
    /* im.m_cols = 4; */
    /* im.m_integralPixels = p; */

    /* IntegralImage::Pixels iP; */
    /* std::vector<unsigned int> irow1 = {5, 15, 17, 20}; */
    /* std::vector<unsigned int> irow2 = {11, 22, 25, 31}; */
    /* std::vector<unsigned int> irow3 = {14, 26, 31, 41}; */
    /* std::vector<unsigned int> irow4 = {18, 32, 39, 51}; */
    /* iP.push_back(irow1); */
    /* iP.push_back(irow2); */
    /* iP.push_back(irow3); */
    /* iP.push_back(irow4); */
    /* im.m_createIntegral(p); */
    /* assert(p == iP); */

    /* // HAARSUM TEST. */
    /* p.clear(); */
    /* row1 = {1, 2, 3, 4}; */
    /* row2 = {5, 6, 7, 8}; */
    /* row3 = {9, 10, 11, 12}; */
    /* row4 = {13, 14, 15, 16}; */
    /* p.push_back(row1); */
    /* p.push_back(row2); */
    /* p.push_back(row3); */
    /* p.push_back(row4); */
    /* im.m_integralPixels = p; */
    /* auto sum = im.getSum(1, 1, 2, 2); */
    /* assert(sum == 0); */
    
    /* // HAARSHAPE ONE TEST. */
    /* VJLearner l; */
    /* im.m_createIntegral(p); */
    /* im.m_integralPixels = p; */
    /* VJLearner::Wavelet w1(l.H1_MLENGTH, l.H1_NLENGTH, l.H1_ROWS, l.H1_COLS, 0, 0, 1, false); */
    /* auto osum = w1.getWaveVal(im); */
    /* assert(osum == -4); */

    /* // HAARSHAPE TWO TEST. */
    /* VJLearner::Wavelet w2(l.H2_MLENGTH, l.H2_NLENGTH, l.H2_ROWS, l.H2_COLS, 0, 0, 1, false); */ 
    /* osum = w2.getWaveVal(im); */
    /* assert(osum == -32); */

    /* // HAARSHAPE THREE TEST. */
    /* VJLearner::Wavelet w3(l.H3_MLENGTH, l.H3_NLENGTH, l.H3_ROWS, l.H3_COLS, 0, 0, 1, false); */ 
    /* osum = w3.getWaveVal(im); */
    /* assert(osum == 8); */

    return 0;
}
