#include "common.h"
#include "vjlearner.h"
#include "integral_image.h"
#include "pool.h"
 
const int IMAGE_SIZE = 250;
const double DOWNSCALE = 0.25;
const int SUB_WINDOW_SIZE = 100;
const int BORDER_WIDTH = 3;
const int RECT_MOVE = 15;
const cv::Vec3b COLOR = {255, 0, 0};

void faceRectangle(cv::Mat& frame, int mPos, int nPos) {
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

int main(int, char**) {
    // Setup webcam.
    cv::Mat frame;
    cv::VideoCapture cap;
    int deviceID = 0; // Default camera.
    int apiID = cv::CAP_ANY; // Default API.
    cap.open(deviceID, apiID);
    if (!cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    // Load learner.
    std::ifstream fin("learner.json");
    json j = json::parse(fin);
    VJLearner learner = j.template get<VJLearner>();


    Pool<int> pool;
    for (;;) {
        cap.read(frame);

        /* cv::resize(frame, frame, cv::Size(1280, 720)); */
        /* faceRectangle(frame, 0, 0); */
        if (frame.empty()) {
            std::cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        cv::resize(frame, frame, cv::Size(), DOWNSCALE, DOWNSCALE);
        std::mutex rMutex;
        for (int m = 0; m + IMAGE_SIZE < frame.rows; m += RECT_MOVE) {
            for (int n = 0; n + IMAGE_SIZE < frame.cols; n += RECT_MOVE) {
                // Update face information if there is one. Need a lock on the
                // function itself?
                pool.queue([&rMutex, &learner, &frame,  n, m] () { 
                    cv::Rect roi(n, m, IMAGE_SIZE, IMAGE_SIZE);
                    cv::Mat slice = frame(roi);
                    std::vector<IntegralImage> datapoint = {IntegralImage(slice)};
                    Prediction p = learner.predict(datapoint)[0];
                    if (p == Prediction::FACE) {
                        std::lock_guard<std::mutex> rLock(rMutex);
                        int shift = (IMAGE_SIZE - SUB_WINDOW_SIZE) / 2; 
                        faceRectangle(frame, m + shift, n + shift);
                    }
                    return -1;
                }); 
                /* Prediction p = learner.predict(datapoint)[0]; */
                /* if (p == Prediction::FACE) { */
                /*     int shift = (IMAGE_SIZE - SUB_WINDOW_SIZE) / 2; */ 
                /*     faceRectangle(frame, m + shift, n + shift); */
                /*     m = std::min(m + SUB_WINDOW_SIZE, frame.rows - IMAGE_SIZE - 1); */
                /*     n += SUB_WINDOW_SIZE; */
                /* } */
            }
        }
        pool.getReturnVals();
        /* std::vector<Prediction> predictions = pool.getReturnVals(); */
        /* for (auto& p : predictions) { */
        /*     if (p == k */
        /* } */

        cv::imshow("Live", frame);
        if (cv::waitKey(5) >= 0)
            break; 
    }
    return 0;
}
