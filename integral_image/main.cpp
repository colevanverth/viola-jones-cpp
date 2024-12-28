#include "helpers.h"

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    if (argc != 3) {
      std::cerr << "Incorrect usage." << std::endl;
      return 1;
    }

    std::string inputFolder(argv[1]);
    std::string outputFolder(argv[2]); 

    std::string rawFp = std::string(fs::current_path()) + std::string("/") + inputFolder;
    for (const auto& entry : fs::directory_iterator(rawFp)) {
        std::string fp = entry.path();
        cv::Mat img = cv::imread(fp);
        if (img.empty()) { continue; }

        cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
        Pixels p = pixelize(img);
        integral(p);
        fp.replace(fp.find(inputFolder), inputFolder.length(), outputFolder); 
        fp.replace(fp.find(".jpg"), 4, ".bytes");
        serialize(fp, p);
   }
   return 0;
}
