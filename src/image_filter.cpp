#include <string>
#include "image_filter.hpp"
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include "detect_multiscale_param.hpp"

std::vector<cv::Rect> haarcascade_face_detection(cv::Mat cv_img, DetectMultiscaleParam params) {
  cv::Mat mGray;
  cv::CascadeClassifier face_cascade;
  std::string face_cascade_name = cv::samples::findFile( "haarcascades/haarcascade_frontalface_default.xml",true,true);
  face_cascade.load(face_cascade_name);
  cv::cvtColor(cv_img, mGray, cv::COLOR_BGR2GRAY);
  cv::equalizeHist(mGray, mGray);
  std::vector<cv::Rect> faces;
  face_cascade.detectMultiScale(mGray, faces, params.scaleFactor, params.minNeighbors, params.flags, params.minSize);
  return faces;
}

std::vector<cv::Rect> haarcascade_eye_detection(cv::Mat cv_img, DetectMultiscaleParam params) {
  cv::Mat mGray;
  cv::CascadeClassifier eye_cascade;
  std::string eye_cascade_name = cv::samples::findFile( "haarcascades/haarcascade_eye_tree_eyeglasses.xml",true,true );
  eye_cascade.load(eye_cascade_name);
  cv::cvtColor(cv_img, mGray, cv::COLOR_BGR2GRAY);
  cv::equalizeHist(mGray, mGray);
  std::vector<cv::Rect> eyes;
  eye_cascade.detectMultiScale(mGray, eyes, params.scaleFactor, params.minNeighbors, params.flags, params.minSize);
  return eyes;
}
