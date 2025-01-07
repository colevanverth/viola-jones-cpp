#pragma once

#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <vector>
#include <mutex>
#include <functional>
#include <thread>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <limits>
#include <cmath>
#include <numeric>

enum Prediction {
    FACE = 1,
    NON_FACE = -1
};
