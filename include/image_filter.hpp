#ifndef IMAGE_FILTER_HPP_
#define IMAGE_FILTER_HPP_

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "detect_multiscale_param.hpp"

std::vector<cv::Rect> haarcascade_face_detection(cv::Mat cv_img, DetectMultiscaleParam params);
std::vector<cv::Rect> haarcascade_eye_detection(cv::Mat cv_img);

#endif // IMAGE_FILTER_HPP_
