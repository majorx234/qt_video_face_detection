#include <iostream>
#include <QtWidgets>
#include <opencv2/opencv.hpp> 
#include "opencv2/imgproc/imgproc.hpp"

#include "image_list_model.hpp"
#include "image_list_delegate.hpp"
#include "video_face_detection.hpp"
#include "ui_video_face_detection.h"

#include "cv_utils.hpp"
#include "image_filter.hpp"

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
  selectedFacesListDelegate = new ImageListDelegate(ui->selectedFacesListView);

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
  setImage(frame);
}
 
void VideoFaceDetection::setSlider(unsigned int steps) {
   ui->videoProgressSlider->setMinimum(0);
   ui->videoProgressSlider->setMaximum(steps-1);
   ui->videoProgressSlider->setSingleStep(1);
}

void VideoFaceDetection::setImage(cv::Mat cv_image) {
  cv::Mat cv_image_with_faces = cv_image;
  if (ui->faceDetectionCheckBox->isChecked()) {
    
    std::vector<cv::Rect> new_faces = haarcascade_face_detection(cv_image);
    //setFaces(new_faces);
    cv::Scalar red( 255,0,0 );
    draw_rectangle_in_image(cv_image_with_faces, new_faces, red);
  } else {
    
  }
  cv::Mat cv_scaled_image = scaledImageToConstrains(cv_image_with_faces,label_width,label_height);
  QImage qt_image = QImage(static_cast<uchar*>(cv_scaled_image.data), cv_scaled_image.cols, cv_scaled_image.rows, cv_scaled_image.step, QImage::Format_BGR888);
  QPixmap vidPixmap = QPixmap::fromImage(qt_image);
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
  setImage(frame);
}

void VideoFaceDetection::setLastImage(cv::Mat image) {
  last_image = image;
}

void VideoFaceDetection::cropVideoImage() {
  selectedFacesListModel->append(last_image);  
}

void VideoFaceDetection::setFaces(std::vector<cv::Rect> new_faces) {
  this->faces.clear();
  this->faces.insert(new_faces.end(), new_faces.begin(), new_faces.end());
}

void VideoFaceDetection::clearFaces() {
  this->faces.clear();  
}

