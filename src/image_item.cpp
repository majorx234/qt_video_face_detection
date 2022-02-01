#include "image_item.hpp"

ImageItem::ImageItem(unsigned int thumb_width) : thumbnail_width(thumb_width) {
}

void ImageItem::set_image(cv::Mat cv_image) {
  this->image = cv_image;
  cv::Size image_size = cv_image.size();
  double ratio = static_cast<double>(image_size.width) / static_cast<double>(image_size.height);
  cv::resize(cv_image, this->thumbnail, cv::Size(128,static_cast<int>(128 / ratio)), 0, 0, cv::INTER_CUBIC);
}

cv::Mat ImageItem::get_image() {
  return this->image;
}

cv::Mat ImageItem::get_thumbnail() {
  return this->thumbnail;
}
