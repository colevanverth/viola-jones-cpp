#pragma once

#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <mutex>
#include <cmath>
#include <functional>
#include <thread>
#include <iostream>
#include <atomic>
#include <filesystem>
#include <algorithm>
#include <semaphore>
#include <limits>
#include <cmath>
#include <numeric>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

enum Prediction {
    FACE = 1,
    NON_FACE = -1
};
