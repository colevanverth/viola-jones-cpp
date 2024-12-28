#pragma once

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>

typedef std::vector<std::vector<long>> Pixels;

Pixels pixelize(const cv::Mat& img);

void integral(Pixels& p);

void print(Pixels& p);

void serialize(const std::string& fp, Pixels& p);
