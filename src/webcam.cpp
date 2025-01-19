#include "common.h"
#include "vjlearner.h"
#include "integral_image.h"
#include "pool.h"
 
const int SKIP_FRAMES = 3;

const int IMAGE_SIZE = 250;

const double DOWNSCALE = 0.25;

const int SUB_WINDOW_SIZE = 100;

const int BORDER_WIDTH = 3;

const int AVG_THRESHOLD = 25;

const int RECT_MOVE = 10;

const cv::Vec3b COLOR = {255, 0, 0};

const cv::Scalar PADDING_COLOR = cv::Scalar(128, 128, 128);

void faceRectangle(cv::Mat& frame, int mPos, int nPos);

void queuePool(Pool<int>& pool, VJLearner& learner, std::mutex& fMutex, std::vector<cv::Point>& facePoints, cv::Mat& frame);

std::vector<cv::Point> averages(std::vector<cv::Point>& p);

cv::Mat padded(const cv::Mat& frame);

int main() {
    // Setup webcam.
    cv::Mat frame;
    cv::VideoCapture cap;
    int deviceID = 0; 
    int apiID = cv::CAP_ANY;
    cap.open(deviceID, apiID);
    if (!cap.isOpened()) {
        std::cerr << "Camera failed to open." << std::endl;
        return EXIT_FAILURE;
    }

    // Load learner.
    std::ifstream fin("learner.json");
    json j = json::parse(fin);
    VJLearner learner = j.template get<VJLearner>();

    // Process incoming frames and display them.
    Pool<int> pool;
    std::vector<cv::Point> queueFaces;
    std::mutex fMutex;
    queuePool(pool, learner, fMutex, queueFaces, frame);
    std::vector<cv::Point> renderFaces;
    long long frameCount = 0;
    for (;;) {
        // Load frame.
        cap.read(frame);
        if (frame.empty()) { std::cerr << "Blank frame." << std::endl; break; }
        cv::resize(frame, frame, cv::Size(), DOWNSCALE, DOWNSCALE);

        // Face recognition via queue.
        frameCount++;
        if (frameCount % SKIP_FRAMES == 0) {
            pool.getReturnVals(); // Reset pool.
            renderFaces = queueFaces;
            renderFaces = averages(renderFaces);
            queueFaces.clear();
            queuePool(pool, learner, fMutex, queueFaces, frame);
        }

        // Render faces.
        for (const auto& p : renderFaces) {
            faceRectangle(frame, p.y, p.x);
        }
        cv::imshow("Live", padded(frame));
        if (cv::waitKey(1) >= 0)
            break; 
    }
    return 0;
}
void queuePool(Pool<int>& pool, VJLearner& learner, std::mutex& fMutex, std::vector<cv::Point>& facePoints, cv::Mat& frame) {
    for (int m = 0; m + IMAGE_SIZE < frame.rows; m += RECT_MOVE) {
        for (int n = 0; n + IMAGE_SIZE < frame.cols; n += RECT_MOVE) {
            pool.queue([&fMutex, &learner, &frame, &facePoints, n, m] () { 
                cv::Rect roi(n, m, IMAGE_SIZE, IMAGE_SIZE);
                cv::Mat slice = frame(roi);
                std::vector<IntegralImage> datapoint = {IntegralImage(slice)};
                Prediction p = learner.predict(datapoint)[0];
                if (p == Prediction::FACE) {
                    std::lock_guard<std::mutex> fLock(fMutex);
                    facePoints.push_back(cv::Point(n, m)); 
                }
                return -1;
            }); 
        }
    }
}

std::vector<cv::Point> averages(std::vector<cv::Point>& p) {
    std::vector<cv::Point> averages;
    while (!p.empty()) {
        auto average = p.back();
        p.pop_back();
        std::vector<size_t> toRemove;
        for (size_t i = 0; i < p.size(); i++) {
            auto deltaX = average.x - p[i].x;
            auto deltaY = average.y - p[i].y;
            auto distance = std::sqrt(std::pow(deltaX, deltaY));
            if (distance < AVG_THRESHOLD) {
                average.x = ( average.x + p[i].x ) / 2;
                average.y = ( average.y + p[i].y ) / 2;
            }
            toRemove.push_back(i);
        }
        std::reverse(toRemove.begin(), toRemove.end());
        for (size_t i : toRemove) {
            p.erase(p.begin() + i);
        }
        averages.push_back(average);
    }
    return averages;
}

cv::Mat padded(const cv::Mat& frame) {
    cv::Mat paddedFrame = cv::Mat(frame.rows + IMAGE_SIZE, frame.cols + IMAGE_SIZE, frame.type(), PADDING_COLOR);
    cv::Rect paddedRoi(IMAGE_SIZE / 2, IMAGE_SIZE / 2, frame.cols, frame.rows);
    frame.copyTo(paddedFrame(paddedRoi));
    return paddedFrame;
}

void faceRectangle(cv::Mat& frame, int mPos, int nPos) {
    int shift = (IMAGE_SIZE - SUB_WINDOW_SIZE) / 2; 
    mPos += shift;
    nPos += shift;

    // Left vertical bar.
    for (int m = 0; m < SUB_WINDOW_SIZE; m++) {
        for (int n = 0; n < BORDER_WIDTH; n++) {
            frame.at<cv::Vec3b>(m + mPos, n + nPos) = COLOR;
        }
    }
    // Right vertical bar.
    for (int m = 0; m < SUB_WINDOW_SIZE; m++) {
        for (int n = 0; n < BORDER_WIDTH; n++) {
            frame.at<cv::Vec3b>(m + mPos, n + nPos + SUB_WINDOW_SIZE - BORDER_WIDTH) = COLOR;
        }
    }
    // Top horizontal bar.
    for (int n = 0; n < SUB_WINDOW_SIZE; n++) {
        for (int m = 0; m < BORDER_WIDTH; m++) {
            frame.at<cv::Vec3b>(m + mPos, n + nPos) = COLOR;
        }
    }
    // Bottom horizontal bar.
    for (int n = 0; n < SUB_WINDOW_SIZE; n++) {
        for (int m = 0; m < BORDER_WIDTH; m++) {
            frame.at<cv::Vec3b>(m + mPos + SUB_WINDOW_SIZE - BORDER_WIDTH, n + nPos) = COLOR;
        }
    }
}

