#ifndef VIDEO_FACE_DETECTION_HPP
#define VIDEO_FACE_DETECTION_HPP

#include <QtWidgets>
#include <opencv2/opencv.hpp> 
#include "opencv2/imgproc/imgproc.hpp"

#include "ui_video_face_detection.h"

namespace Ui {
class VideoFaceDetection;
}

class VideoFaceDetection : public QWidget {
  Q_OBJECT
 private:
  Ui::video_face_detection *ui;
    
 public:
  explicit VideoFaceDetection(QWidget *parent = Q_NULLPTR);
  ~VideoFaceDetection();

  void loadVideo(const QString &fileName);
  void setSlider(unsigned int steps);
  void setImage(QImage &image);
  void saveImage();
 private:
  QImage scaledImageToLabel(QImage qt_image);
 public slots:  
  void onSlide( int pos);
 private:
  cv::VideoCapture cap;
  int frames;
  int video_width;
  int video_height;

  int label_width;
  int label_height;
  double scale_factor_width;
  double scale_factor_height;
};

#endif // VIDEO_FACE_DETECTION_HPP
