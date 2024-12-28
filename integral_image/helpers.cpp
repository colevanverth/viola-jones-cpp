#include "helpers.h"

Pixels pixelize(const cv::Mat& img) {
    std::vector<std::vector<long>> rows;
    uchar value = img.at<uchar>(2, 2); // Access element at row 2, column 3
    for (int m = 0; m < img.rows; m++) {
        std::vector<long> column;
        for (int n = 0; n < img.cols; n++) {
            column.push_back(img.at<uchar>(m, n));
        }
        rows.push_back(column);
    }
    return rows;
}

void integral(Pixels& p) {
    for (int m = 0; m < p.size(); m++) {
        for (int n = 0; n < p[0].size(); n++) {
            if (m - 1 >= 0) { p[m][n] += p[m-1][n]; }
            if (n - 1 >= 0) { p[m][n] += p[m][n - 1]; }
            if (m - 1 >= 0 && n - 1 >= 0) { p[m][n] -= p[m - 1][n - 1]; }
        }
    }
}

void print(Pixels& p) {
    for (int m = 0; m < p.size(); m++) {
        for (int n = 0; n < p[0].size(); n++) {
            std::cout << p[m][n] << " "; 
        }
        std::cout << std::endl;
    }
}


void serialize(const std::string& fp, Pixels& p) {
    std::ofstream fout(fp, std::ios::binary);
    for (int m = 0; m < p.size(); m++) {
        for (int n = 0; n < p[0].size(); n++) {
            fout.write(reinterpret_cast<char*>(&p[m][n]), sizeof(long));
        }
    }
    fout.close();
}
