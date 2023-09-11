#include "image_item.hpp"

ImageItem::ImageItem(unsigned int thumb_width) : thumbnail_width(thumb_width) {
}

void ImageItem::set_image(cv::Mat cv_img) {
  if(!cv_img.empty()){
    this->image = cv_img;
    cv::Size image_size = cv_img.size();
    double ratio = static_cast<double>(image_size.width) / static_cast<double>(image_size.height);
    cv::resize(cv_img, this->thumbnail, cv::Size(128,static_cast<int>(128 / ratio)), 0, 0, cv::INTER_CUBIC);
  }
}

cv::Mat ImageItem::get_image() {
  return this->image;
}

cv::Mat ImageItem::get_thumbnail() {
  return this->thumbnail;
}

void ImageItem::save_image(std::string filename) {
  cv::imwrite(filename, this->image);
}
