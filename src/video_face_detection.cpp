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
{
  ui->setupUi(this);
 
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
  
}

void VideoFaceDetection::setImage()  
{

}

void VideoFaceDetection::saveImage()
{

}

void VideoFaceDetection::onSlide( int pos) {
  cap.set( cv::CAP_PROP_POS_FRAMES, pos );
}
