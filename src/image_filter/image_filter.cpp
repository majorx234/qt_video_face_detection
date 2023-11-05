#include <string>
#include "image_filter.hpp"
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include "detect_multiscale_param.hpp"

std::vector<cv::Rect> haarcascade_face_detection(cv::Mat cv_img, DetectMultiscaleParam params) {
  std::vector<cv::Rect> faces;
  if(!cv_img.empty()){
    std::string face_cascade_name = cv::samples::findFile( "haarcascades/haarcascade_frontalface_default.xml",true,true);
    cv::CascadeClassifier face_cascade;
    face_cascade.load(face_cascade_name);
    cv::Mat mGray;
    cv::cvtColor(cv_img, mGray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(mGray, mGray);
    face_cascade.detectMultiScale(mGray, faces, params.scaleFactor, params.minNeighbors, params.flags, params.minSize);
  }
  return faces;
}

std::vector<cv::Rect> haarcascade_eye_detection(cv::Mat cv_img, DetectMultiscaleParam params) {
  std::vector<cv::Rect> eyes;
  if(!cv_img.empty()){
    cv::Mat mGray;
    cv::CascadeClassifier eye_cascade;
    std::string eye_cascade_name = cv::samples::findFile( "haarcascades/haarcascade_eye_tree_eyeglasses.xml",true,true );
    eye_cascade.load(eye_cascade_name);
    cv::cvtColor(cv_img, mGray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(mGray, mGray);
    eye_cascade.detectMultiScale(mGray, eyes, params.scaleFactor, params.minNeighbors, params.flags, params.minSize);
  }
  return eyes;
}

void pixelate_image(cv::Mat &cv_img, std::vector<cv::Rect> rectangle_list) {
  if(!cv_img.empty()) {
    for (cv::Rect rectangle : rectangle_list) {
      cv::Mat face_image = cv_img(rectangle);
      cv::resize(face_image, face_image, cv::Size(), 0.1, 0.1, cv::INTER_NEAREST);
      cv::resize(face_image, face_image, cv::Size(), 10.0, 10.0, cv::INTER_NEAREST);

      cv::Mat insert_image(cv_img, rectangle);
      face_image.copyTo(insert_image);
    }
  }
}
