#ifndef VIDEO_FACE_DETECTION_HPP
#define VIDEO_FACE_DETECTION_HPP
#include <QtWidgets>
#include "ui_video_face_detection.h"

namespace Ui 
{
  class VideoFaceDetection;
}

class VideoFaceDetection : public QWidget
{
  Q_OBJECT
 private:
  Ui::video_face_detection *ui;
  
 public:
  explicit VideoFaceDetection(QWidget *parent = Q_NULLPTR);
  ~VideoFaceDetection();

  void loadVideo();
  void setImage();
  void saveImage();

};

#endif // VIDEO_FACE_DETECTION_HPP
