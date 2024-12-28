#define private public

#include "haar_wavelets.h"

int main() {
    HaarWavelets wv;
    auto points = wv.m_getPoints(5, 5, 2, 3, 1);
    for (auto p : points) {
        std::cout << p.x << " " << p.y << std::endl;
    }
    
    return 0;
}
