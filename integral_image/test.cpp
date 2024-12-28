#include <assert.h>

#include "helpers.h"

int main() {
    // Simple integral image test.
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

    integral(p);
    assert(p == iP);

    return 0;
}
