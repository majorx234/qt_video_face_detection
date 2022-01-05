#include "video_face_detection.hpp"
#include "ui_video_face_detection.h"

#include <QtWidgets>
#include <iostream>

VideoFaceDetection::VideoFaceDetection(QWidget *parent) : QWidget(parent), ui(new Ui::video_face_detection)
{
  ui->setupUi(this);
 
  //scene = new QGraphicsScene();
  //ui->graphicsView->setScene(scene);
}


VideoFaceDetection::~VideoFaceDetection() 
{

}

void VideoFaceDetection::loadVideo()
{

  
}

void VideoFaceDetection::setImage()  
{

}

void VideoFaceDetection::saveImage()
{

}
