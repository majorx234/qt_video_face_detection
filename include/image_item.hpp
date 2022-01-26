#ifndef INCLUDE_IMAGE_ITEM_HPP_
#define INCLUDE_IMAGE_ITEM_HPP_

#include <QObject>
#include <QVariant>
#include <opencv2/opencv.hpp>

class ImageItem : public QObject {
  Q_OBJECT
 public:
  ImageItem(const ImageItem &item) {
    this->image = item.image.clone();   
    this->thumbnail = item.thumbnail.clone();   
    this->thumbnail_width = item.thumbnail_width;
  }
  explicit ImageItem(unsigned int thumb_width = 128);
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

Q_DECLARE_METATYPE(ImageItem)
#endif // INCLUDE_IMAGE_ITEM_HPP_
