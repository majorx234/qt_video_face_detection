#ifndef INCLUDE_IMAGE_ITEM_HPP_
#define INCLUDE_IMAGE_ITEM_HPP_

#include "qt/QtCore/QObject"
#include <opencv2/opencv.hpp>

class ImageItem : QObject {
  Q_OBJECT
 public:
  ImageItem(unsigned int thumb_width=128);
  void set_image(cv::Mat cv_image);
  cv::Mat get_image();
  cv::Mat get_thumbnail();
 signals:
  void valueChanged();
 private:
  cv::Mat image;
  cv::Mat thumbnail;
  unsigned int thumbnail_width; 
};

#endif // INCLUDE_IMAGE_ITEM_HPP_
