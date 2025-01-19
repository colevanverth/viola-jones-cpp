#include "common.h"
#include "integral_image.h"
#include "vjlearner.h"

namespace fs = std::filesystem;

const int NON_FACE_LIMIT = 5914;
const int FACE_LIMIT = 5914;
const int ADABOOST_ITERATIONS = 200;
const int IMAGE_SIZE = 250;
const int PADDING_SIZE = 100;

int main() {
  std::string path = std::string(fs::current_path()) + std::string("/rsrc/");
  std::string facePath = path + std::string("face_edited");
  std::string nonFacePath = path + std::string("non_face_edited");

  std::vector<IntegralImage> imgs;
  std::vector<Prediction> targets;

  std::cout << "Loading faces." << std::endl;
  int counter = 0;

  int faceLimit;
  if (FACE_LIMIT == -1) {
    faceLimit = std::distance(fs::directory_iterator(facePath),
                              fs::directory_iterator{});
  } else {
    faceLimit = FACE_LIMIT;
  }

  for (const auto &entry : fs::directory_iterator(facePath)) {
    if (counter++ == faceLimit) {
      break;
    }
    cv::Mat img;
    img = cv::imread(entry.path());
    IntegralImage iimg(img);
    imgs.push_back(iimg);
    targets.push_back(Prediction::FACE);
  }

  std::cout << "Loading non-faces." << std::endl;
  counter = 0;

  int nonFaceLimit;
  if (NON_FACE_LIMIT == -1) {
    nonFaceLimit = std::distance(fs::directory_iterator(facePath),
                                 fs::directory_iterator{});
  } else {
    nonFaceLimit = NON_FACE_LIMIT;
  }
  for (const auto &entry : fs::directory_iterator(nonFacePath)) {
    if (counter++ == nonFaceLimit) {
      break;
    }
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
  std::cout << std::endl
            << "Final error: " << learner.error(imgs, targets) << std::endl;
  std::cout << std::endl
            << "Final error (cascade): " << learner.error(imgs, targets)
            << std::endl;
}
