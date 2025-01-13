#include "common.h"
#include "vjlearner.h"
#include "integral_image.h"
 
const int IMAGE_SIZE = 250;

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


    for (;;) {
        cap.read(frame);

        cv::resize(frame, frame, cv::Size(), 0.25, 0.25);
        if (frame.empty()) {
            std::cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        for (int m = 0; m + IMAGE_SIZE < frame.rows; m += 100) {
            for (int n = 0; n + IMAGE_SIZE < frame.cols; n += 100) {
                cv::Rect roi(n, m, IMAGE_SIZE, IMAGE_SIZE);
                cv::Mat slice = frame(roi);
                std::vector<IntegralImage> datapoint = {IntegralImage(slice)};
                Prediction p = learner.predict(datapoint)[0];
                if (p == Prediction::FACE) {
                    std::cout << "Face at " << m << " " << n << std::endl;
                }
            }
        }

        cv::imshow("Live", frame);
        if (cv::waitKey(5) >= 0)
            break; 
    }
    return 0;
}
