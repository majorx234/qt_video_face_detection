#include "image_filter.hpp"
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc.hpp>

std::vector<cv::Rect> haarcascade_face_detection(cv::Mat cv_img) {
  cv::Mat mGray;
  cv::CascadeClassifier face_cascade;
  face_cascade.load("/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml");
  cv::cvtColor(cv_img, mGray, CV_RGB2GRAY);
  cv::equalizeHist(mGray, mGray);
  std::vector<cv::Rect> faces;
  face_cascade.detectMultiScale(mGray, faces, 1.1, 2, CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
  return faces;
}

