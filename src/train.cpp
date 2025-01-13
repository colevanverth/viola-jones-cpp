#include "common.h"
#include "integral_image.h"
#include "vjlearner.h"

namespace fs = std::filesystem;

const int TRAINING_LIMIT = 50;
const int ADABOOST_ITERATIONS = 1;
/* const int TRAINING_LIMIT = 200; */
/* const int ADABOOST_ITERATIONS = 25; */
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
    json j = learner;
    std::ofstream fout("learner.json");
    fout << std::setw(4) << j << std::endl;
    std::cout << std::endl << "Final error: " << learner.error(imgs, targets) << std::endl;
    std::cout << std::endl << "Final error: " << learner.error(imgs, targets) << std::endl;

    auto learner2 = j.template get<VJLearner>();
    std::ofstream fout2("learner2.json");
    json j2 = learner2;
    fout2 << std::setw(4) << j2 << std::endl;
    

    std::cout << std::endl << "Final error: " << learner2.error(imgs, targets) << std::endl;

}
