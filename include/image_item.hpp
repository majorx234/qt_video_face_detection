#ifndef INCLUDE_IMAGE_ITEM_HPP_
#define INCLUDE_IMAGE_ITEM_HPP_

//#include "qt/QtCore/QObject"
#include <QVariant>
#include <opencv2/opencv.hpp>

class ImageItem {
 public:
  ImageItem(const ImageItem &item) {
    this->image = item.image.clone();   
    this->thumbnail = item.thumbnail.clone();   
    this->thumbnail_width = item.thumbnail_width;
  };
  ImageItem(unsigned int thumb_width = 128);
  void set_image(cv::Mat cv_image);
  cv::Mat get_image();
  cv::Mat get_thumbnail();
  // signals:
  //  void valueChanged();
 private:
  cv::Mat image;
  cv::Mat thumbnail;
  unsigned int thumbnail_width; 
};

Q_DECLARE_METATYPE(ImageItem)
#endif // INCLUDE_IMAGE_ITEM_HPP_
