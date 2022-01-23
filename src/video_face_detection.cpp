#include <iostream>
#include <QtWidgets>
#include <opencv2/opencv.hpp> 
#include "opencv2/imgproc/imgproc.hpp"

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
{
  ui->setupUi(this);
  //ui->videoProgressSlider event valueChanged()
  connect(ui->videoProgressSlider, SIGNAL(valueChanged(int)), SLOT(onSlide(int)));
  //scene = new QGraphicsScene();
  //ui->graphicsView->setScene(scene);
}


VideoFaceDetection::~VideoFaceDetection(){

}

void VideoFaceDetection::loadVideo(const QString &fileName)
{
  cap.open( fileName.toStdString() );
  frames = (int) cap.get(cv::CAP_PROP_FRAME_COUNT);
  video_width   = (int) cap.get(cv::CAP_PROP_FRAME_WIDTH);
  video_height   = (int) cap.get(cv::CAP_PROP_FRAME_HEIGHT);
  setSlider(frames);
  cv::Mat frame;
  cap >> frame;
  QImage image = QImage((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
  setImage(image);
  // anpassen des sliders  
}

void VideoFaceDetection::setSlider(unsigned int steps) {
  ui->videoProgressSlider->setMinimum( 0 );
  ui->videoProgressSlider->setMaximum( steps );
  ui->videoProgressSlider->setSingleStep( 1 );
}

void VideoFaceDetection::setImage(QImage image)  
{
  QPixmap vidPixmap = QPixmap::fromImage(image.scaledToWidth(label_width).scaledToHeight(label_height));
  ui->videoLabel->setPixmap(vidPixmap);
}

void VideoFaceDetection::saveImage()
{

}

void VideoFaceDetection::onSlide( int pos) {
  // get opencv image on that opsition
  cv::Mat frame;
  cap.set( cv::CAP_PROP_POS_FRAMES, pos);
  cap >> frame;
  QImage image = QImage((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_BGR888);
  setImage(image);
}
