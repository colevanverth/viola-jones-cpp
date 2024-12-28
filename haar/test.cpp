#define private public

#include <assert.h>

#include "haar_wavelets.h"


void integral(Pixels& img) {
    for (int m = 0; m < img.size(); m++) {
        for (int n = 0; n < img[0].size(); n++) {
            if (m - 1 >= 0) { img[m][n] += img[m-1][n]; }
            if (n - 1 >= 0) { img[m][n] += img[m][n - 1]; }
            if (m - 1 >= 0 && n - 1 >= 0) { img[m][n] -= img[m - 1][n - 1]; }
        }
    }
}

Pixels imgToPixels(const cv::Mat& img) {
    std::vector<std::vector<long>> rows;
    for (int m = 0; m < img.rows; m++) {
        std::vector<long> column;
        for (int n = 0; n < img.cols; n++) {
            column.push_back(img.at<uchar>(m, n));
        }
        rows.push_back(column);
    }
    return rows;
}

int main() {
    // INTEGRAL IMAGE TEST.
    Pixels p;
    std::vector<long> row1 = {5, 10, 2, 3};
    std::vector<long> row2 = {6, 1, 1, 3};
    std::vector<long> row3 = {3, 1, 2, 4};
    std::vector<long> row4 = {4, 2, 2, 2};
    p.push_back(row1);
    p.push_back(row2);
    p.push_back(row3);
    p.push_back(row4);

    Pixels iP;
    std::vector<long> irow1 = {5, 15, 17, 20};
    std::vector<long> irow2 = {11, 22, 25, 31};
    std::vector<long> irow3 = {14, 26, 31, 41};
    std::vector<long> irow4 = {18, 32, 39, 51};
    iP.push_back(irow1);
    iP.push_back(irow2);
    iP.push_back(irow3);
    iP.push_back(irow4);

    HaarWavelets hw;
    integral(p);
    assert(p == iP);

    // HAARSUM TEST.
    p.clear();
    row1 = {1, 2, 3, 4};
    row2 = {5, 6, 7, 8};
    row3 = {9, 10, 11, 12};
    row4 = {13, 14, 15, 16};
    p.push_back(row1);
    p.push_back(row2);
    p.push_back(row3);
    p.push_back(row4);
    auto sum = hw.m_haarSum(p, 1, 1, 2, 2);
    assert(sum == 0);
    
    // HAARSHAPE ONE TEST.
    hw.m_rows = 4;
    hw.m_cols = 4;
    integral(p);
    auto osum = hw.m_haar(p, 0, 0, HAAR1_ROWS, HAAR1_COLS, HAAR1_MLENGTH, HAAR1_NLENGTH, 1);
    assert(osum.value() == -4); 

    // HAARSHAPE TWO TEST.
    osum = hw.m_haar(p, 0, 0, HAAR2_ROWS, HAAR2_COLS, HAAR2_MLENGTH, HAAR2_NLENGTH, 1);
    assert(osum.value() == -32);

    // HAARSHAPE THREE TEST.
    osum = hw.m_haar(p, 0, 0, HAAR3_ROWS, HAAR3_COLS, HAAR3_MLENGTH, HAAR3_NLENGTH, 1);
    assert(osum.value() == 8);
    
    // HAARSHAPE FOUR TEST.
    osum = hw.m_haar(p, 0, 0, HAAR4_ROWS, HAAR4_COLS, HAAR4_MLENGTH, HAAR4_NLENGTH, 1);

    return 0;
}
