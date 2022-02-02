#ifndef CV_UTILS_HPP_
#define CV_UTILS_HPP_

#include <opencv2/opencv.hpp> 
#include "opencv2/imgproc/imgproc.hpp"

cv::Mat scaledImageToConstrains(cv::Mat, size_t, size_t, double&, double&);
bool
cut_selecteced_rectangle_from_image(cv::Mat cv_image, cv::Mat &cv_dst_image, int p_x, int p_y, 
                                    std::vector<cv::Rect> rectangle_list);
void draw_rectangle_in_image(cv::Mat &cv_image,
                             const std::vector<cv::Rect> &rectangle_list,
                             const cv::Scalar &color);
#endif // CV_UTILS_HPP_
