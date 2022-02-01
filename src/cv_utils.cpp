#include "cv_utils.hpp"

cv::Mat scaledImageToConstrains(cv::Mat cv_image, size_t label_width, size_t label_height) {
  cv::Size shape  = cv_image.size();
  size_t image_height = shape.height;
  size_t image_width = shape.width;
  double ratio = static_cast<double>(image_width) / static_cast<double>(image_height);
  double scaledFactorWidth = 1.0;
  double scaledFactorHeight = 1.0;
  cv::Mat resized_image;
  cv::Size dim;
  if (ratio == 1.0) {
    dim = cv::Size(label_width,label_width);
    scaledFactorWidth = static_cast<double>(label_width) / static_cast<double>(image_width);
    scaledFactorHeight = static_cast<double>(label_height) / static_cast<double>(image_height);
  } else if (ratio < 1.0) {
    double r = static_cast<double>(image_height) / static_cast<double>(label_height);
    dim = cv::Size(static_cast<int>(image_width / r), label_height);
    scaledFactorHeight = label_height / image_height;
    scaledFactorWidth = scaledFactorHeight;
  } else {  // ratio > 1
    double r = static_cast<double>(image_width) / static_cast<double>(label_width);
    dim = cv::Size(label_width, int(image_height / r));
    scaledFactorWidth = label_width / image_width;
    scaledFactorHeight = scaledFactorWidth;
  }
  cv::resize(cv_image, resized_image, dim, 0, 0,cv::INTER_AREA);    
  return resized_image;
}

