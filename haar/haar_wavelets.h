#include <opencv2/core.hpp>
#include <vector>
#include <iostream>
#include <optional>

const int HAAR1_ROWS = 1;
const int HAAR1_NLENGTH = 1;
const int HAAR1_COLS = 2;
const int HAAR1_MLENGTH = 4; 

const int HAAR2_ROWS = 2;
const int HAAR2_NLENGTH = 2;
const int HAAR2_COLS = 1;
const int HAAR2_MLENGTH = 2;

const int HAAR3_ROWS = 1;
const int HAAR3_NLENGTH = 1;
const int HAAR3_COLS = 3;
const int HAAR3_MLENGTH = 2;

const int HAAR4_ROWS = 2;
const int HAAR4_NLENGTH = 2;
const int HAAR4_COLS = 2;
const int HAAR4_MLENGTH = 1;

typedef long pixel;

typedef std::vector<std::vector<pixel>> Pixels;

class HaarWavelets {

public:

    HaarWavelets() = default;

    std::vector<pixel> getFeatures(const Pixels& img);

private:

    int m_rows;

    int m_cols;

    struct Point;

    const cv::Mat m_img;

    pixel m_haarSum(const Pixels& img, int m, int n, int mLength, int nLength);

    std::optional<pixel> m_haar(const Pixels& img, int m, int n, int numRows, int numCols, int mLength, int nLength, int scale);

    struct Point {

        Point() = default;

        Point(size_t x, size_t y) : x(x), y(y) {}

        size_t x, y;

        bool operator==(const Point& other) const {
            return this->x == other.x && this->y == other.y;
        }

    };

};
