#include "common.h"
#include "integral_image.h"
#include "vjlearner.h"

namespace fs = std::filesystem;

const int TRAINING_LIMIT = 100;
const int ADABOOST_ITERATIONS = 20;
const int IMAGE_SIZE = 250; 

int main() {
    std::string path = std::string(fs::current_path()) + std::string("/rsrc/");
    std::string facePath = path + std::string("face_edited");
    std::string nonFacePath = path + std::string("non_face_edited");

    std::vector<IntegralImage> imgs;
    std::vector<Prediction> targets;

    std::cout << "Loading faces." << std::endl;
    int counter = 0;
    for (const auto& entry : fs::directory_iterator(facePath)) {
        if (counter++ == TRAINING_LIMIT) { break; }
        cv::Mat img;
        img = cv::imread(entry.path());
        IntegralImage iimg(img);
        imgs.push_back(iimg);
        targets.push_back(Prediction::FACE);
    }

    std::cout << "Loading non-faces." << std::endl;
    counter = 0;
    for (const auto& entry : fs::directory_iterator(nonFacePath)) {
        if (counter++ == TRAINING_LIMIT) { break; } 
        cv::Mat img;
        img = cv::imread(entry.path());
        IntegralImage iimg(img);
        imgs.push_back(iimg);
        targets.push_back(Prediction::NON_FACE);
    }

    VJLearner learner(IMAGE_SIZE, ADABOOST_ITERATIONS);
    learner.train(imgs, targets);
    std::cout << std::endl << "Final error: " << learner.error(imgs, targets) << std::endl;
}
