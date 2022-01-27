#include <iostream>
#include <QtWidgets>
#include <opencv2/opencv.hpp> 
#include "opencv2/imgproc/imgproc.hpp"

#include "image_list_model.hpp"
#include "image_list_delegate.hpp"
#include "video_face_detection.hpp"
#include "ui_video_face_detection.h"


VideoFaceDetection::VideoFaceDetection(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::video_face_detection)
    , frames(0)
    , video_width(0)
    , video_height(0)
    , label_width(800)
    , label_height(600)
    , scale_factor_width(1.0)
    , scale_factor_height(1.0) {
  ui->setupUi(this);
  //ui->videoProgressSlider event valueChanged()
  connect(ui->videoProgressSlider, SIGNAL(valueChanged(int)), SLOT(onSlide(int)));

  selectedFacesListModel = new ImageListModel();
  selectedFacesListDelegate = new ImageListDelegate();

  ui->selectedFacesListView->setItemDelegate(selectedFacesListDelegate);
  ui->selectedFacesListView->setModel(selectedFacesListModel);
  
  connect(ui->videoLabel,SIGNAL(clicked()),SLOT(cropVideoImage()));
  // idea of graphic scene n.i.y.
  //scene = new QGraphicsScene();
  //ui->graphicsView->setScene(scene);
}


VideoFaceDetection::~VideoFaceDetection() {

}

void VideoFaceDetection::loadVideo(const QString &fileName) {
  cap.open( fileName.toStdString() );
  frames = static_cast<int>( cap.get(cv::CAP_PROP_FRAME_COUNT));
  video_width  = static_cast<int>( cap.get(cv::CAP_PROP_FRAME_WIDTH));
  video_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
  
  setSlider(frames);
  cv::Mat frame;
  cap >> frame;
  setLastImage(frame.clone());
  QImage image = QImage(static_cast<uchar*>(frame.data), frame.cols, frame.rows, frame.step, QImage::Format_BGR888);
  QImage scaled_image = scaledImageToLabel(image); 
  setImage(scaled_image);

}
QImage VideoFaceDetection::scaledImageToLabel(QImage qt_image) {
  double ratio = static_cast<double>(video_width) / static_cast<double>(video_height); 
  scale_factor_width = 1.0;
  scale_factor_height = 1.0;
  if (ratio == 1.0) {
    scale_factor_width  = static_cast<double>(label_width) / static_cast<double>(video_width);
    scale_factor_height = static_cast<double>(label_height) / static_cast<double>(video_height);
    return qt_image.scaledToWidth(label_width, Qt::SmoothTransformation);
  } else if (ratio < 1.0) {
    scale_factor_height = static_cast<double>(label_height) / static_cast<double>(video_height);
    scale_factor_width = scale_factor_height;
    return qt_image.scaledToWidth(label_width,Qt::SmoothTransformation);
  } else { // ratio > 1.0
    scale_factor_width  = static_cast<double>(label_width) / static_cast<double>(video_width);
    scale_factor_height = scale_factor_width;
    return qt_image.scaledToWidth(label_width, Qt::SmoothTransformation);
  }
}
 
void VideoFaceDetection::setSlider(unsigned int steps) {
   ui->videoProgressSlider->setMinimum(0);
   ui->videoProgressSlider->setMaximum(steps-1);
   ui->videoProgressSlider->setSingleStep(1);
}

void VideoFaceDetection::setImage(QImage &image) {
  // image.scaledToWidth(label_width).scaledToHeight(label_height)
  QPixmap vidPixmap = QPixmap::fromImage(image);
  ui->videoLabel->setPixmap(vidPixmap);
}

void VideoFaceDetection::saveImage() {

}

void VideoFaceDetection::onSlide( int pos) {
  // get opencv image on that opsition
  cv::Mat frame;
  cap.set( cv::CAP_PROP_POS_FRAMES, pos);
  cap >> frame;
  setLastImage(frame.clone());
  QImage image = QImage(static_cast<uchar*>(frame.data), frame.cols, frame.rows, frame.step, QImage::Format_BGR888);
  QImage scaled_image = scaledImageToLabel(image); 
  setImage(scaled_image);
  //  setImage(image);
}

void VideoFaceDetection::setLastImage(cv::Mat image) {
  last_image = image;
}

void VideoFaceDetection::cropVideoImage() {
  selectedFacesListModel->append(last_image);  
}
