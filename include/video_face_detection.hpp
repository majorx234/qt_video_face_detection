#ifndef VIDEO_FACE_DETECTION_HPP
#define VIDEO_FACE_DETECTION_HPP

#include <QtWidgets>
#include <opencv2/opencv.hpp> 
#include "opencv2/imgproc/imgproc.hpp"

#include "ui_video_face_detection.h"
#include "image_list_model.hpp"
#include "image_list_delegate.hpp"


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
  void setImage(cv::Mat image);
  void saveImage();
  void setFaces(std::vector<cv::Rect> new_faces);
  void clearFaces();
 private:
  void setLastImage(cv::Mat);                                         
 public slots:  
  void onSlide( int pos);
  void cropVideoImage();
 private:
  cv::VideoCapture cap;
  cv::Mat last_image;
  int frames;
  int video_width;
  int video_height;

  int label_width;
  int label_height;
  double scale_factor_width;
  double scale_factor_height;

  std::vector<cv::Rect> faces;

  ImageListModel *selectedFacesListModel;
  ImageListDelegate* selectedFacesListDelegate;
};

#endif // VIDEO_FACE_DETECTION_HPP
