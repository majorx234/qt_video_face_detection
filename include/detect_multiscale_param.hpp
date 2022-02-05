#ifndef DETECT_MULTISCALE_PARAM_HPP_
#define DETECT_MULTISCALE_PARAM_HPP_

#include <opencv2/opencv.hpp> 

struct DetectMultiscaleParam {
  double scaleFactor;
  int minNeighbors;
  cv::Size minSize;
  cv::Size maxSize;
  int flags;
  bool outputRejectLevels;
};


#endif // DETECT_MULTISCALE_PARAM_HPP_
