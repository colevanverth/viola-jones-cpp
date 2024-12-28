/*
Utility for converting a dataset of randomly sized images to be 250px*250px
by scaling up the dimension of the image and taking a random subset of it.
*/
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
 
namespace fs = std::filesystem;

const int IMAGE_SIZE = 250;

int main(int argc, char** argv) {
   if (argc != 3) {
      std::cerr << "Incorrect usage." << std::endl;
      return 1;
   }

   std::string inputFolder(argv[1]);
   std::string outputFolder(argv[2]); 

   std::string rawFp = std::string(fs::current_path()) + std::string("/") + inputFolder;
   for (const auto & entry : fs::directory_iterator(rawFp)) {
      cv::Mat img, rawImg = cv::imread(entry.path());
      if (rawImg.empty()) { continue; }

      // Rescale to have height/width at least 250 pixels.
      double scaleFactor = std::max(static_cast<double>(IMAGE_SIZE) / rawImg.rows, static_cast<double>(IMAGE_SIZE) / rawImg.cols);
      int newWidth = static_cast<int>(std::ceil(rawImg.cols * scaleFactor)); 
      int newHeight = static_cast<int>(std::ceil(rawImg.rows * scaleFactor)); 
      cv::resize(rawImg, img, cv::Size(newWidth, newHeight));

      // Pick random 250x250 subgroup.
      int colStart = rand() % (img.cols - IMAGE_SIZE + 1);
      int colEnd = colStart + IMAGE_SIZE; 
      int rowStart = rand() % (img.rows - IMAGE_SIZE + 1);
      int rowEnd = rowStart + IMAGE_SIZE; 
      cv::Mat croppedImg = img(cv::Range(rowStart, rowEnd), cv::Range(colStart, colEnd));
     
      // Dump converted file.
      std::string fp = entry.path();
      fp.replace(fp.find("non_face_raw"), 12, outputFolder); 
      cv::imwrite(fp, croppedImg);
   }

   return 0;
}
