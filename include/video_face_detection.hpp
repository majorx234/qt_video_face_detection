#ifndef VIDEO_FACE_DETECTION_HPP
#define VIDEO_FACE_DETECTION_HPP

namespace Ui 
{
  class VideoFaceDetection;
}

class VideoFaceDetection : QWidget
{
  Q_OBJECT  
public:
  explicit VideoFaceDetection(QWidget *parent = Q_NULLPTR):
  ~VideoFaceDetection();

  void loadVideo();
  void setImage();
  void saveImage();

};

#endif // VIDEO_FACE_DETECTION_HPP