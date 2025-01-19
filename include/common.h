#pragma once

#include "json.hpp"
#include <algorithm>
#include <atomic>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <mutex>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <semaphore>
#include <thread>
#include <vector>

using json = nlohmann::json;

enum Prediction { FACE = 1, NON_FACE = -1 };
