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

#include "detect_multiscale_param.hpp"

VideoFaceDetection::VideoFaceDetection(QWidget *parent)
    : QWidget(parent), ui(new Ui::video_face_detection), frames(0),
      video_width(0), video_height(0), label_width(800), label_height(600),
      scale_factor_width(1.0), scale_factor_height(1.0), video_loaded(false) {
  ui->setupUi(this);
  // ui->videoProgressSlider event valueChanged()
  connect(ui->videoProgressSlider, SIGNAL(valueChanged(int)), SLOT(onSlide(int)));

  selectedFacesListModel = new ImageListModel();
  selectedFacesListDelegate = new ImageListDelegate(ui->selectedFacesListView);

  ui->selectedFacesListView->setItemDelegate(selectedFacesListDelegate);
  ui->selectedFacesListView->setModel(selectedFacesListModel);
  ui->selectedFacesListView->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(ui->selectedFacesListView, &QListView::customContextMenuRequested,
          this, &VideoFaceDetection::onContextMenu);

  connect(ui->videoLabel, &QClickLabel::clicked,
          this, &VideoFaceDetection::getFaceAtPos);
  connect(ui->faceDetectionCheckBox, &QCheckBox::stateChanged,
          this, &VideoFaceDetection::onChangeFacedetection);

  cv::samples::addSamplesDataSearchPath("/usr/share/opencv");
  cv::samples::addSamplesDataSearchPath("/usr/share/opencv4");
  // idea of graphic scene n.i.y.
  // scene = new QGraphicsScene();
  // ui->graphicsView->setScene(scene);
}

VideoFaceDetection::~VideoFaceDetection() {
}

void VideoFaceDetection::onContextMenu(QPoint pose) {
  QModelIndex model_index = ui->selectedFacesListView->indexAt(pose);
  int index = model_index.row();
  QMenu *menu = new QMenu(this);
  QAction *save_img = new QAction("Save",this);
  QAction *save_all_img = new QAction("SaveAll", this);
  QAction *delete_img = new QAction("Delete", this);

  menu->addAction(save_img);
  menu->addAction(save_all_img);
  menu->addAction(delete_img);
  //menu->popup(ui->selectedFacesListView->viewport()->mapToGlobal(pose));
  QAction* choosen_action = menu->exec(ui->selectedFacesListView->viewport()->mapToGlobal(pose));
  if (choosen_action == save_img) {
    QString filename = QFileDialog::getSaveFileName(this,
    tr("Save Image"), "~", tr("JPG (*.jpg);;PNG (*.png);;TIFF (*.tiff);;BMP (*.bmp)"));
    if (!filename.isEmpty()) {
      selectedFacesListModel->saveItemAt(index, filename.toStdString());
    }
  } else if (choosen_action == save_all_img) {
    QString filename = QFileDialog::getExistingDirectory(this, tr("~"));
    if (!filename.isEmpty()) {
      selectedFacesListModel->saveItems(filename.toStdString());
    }
  } else if (choosen_action == delete_img) {
    selectedFacesListModel->deleteItem(index);
  }
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
  video_loaded = true;
}

void VideoFaceDetection::setSlider(unsigned int steps) {
   ui->videoProgressSlider->setMinimum(0);
   ui->videoProgressSlider->setMaximum(steps-1);
   ui->videoProgressSlider->setSingleStep(1);
}

void VideoFaceDetection::setImage(cv::Mat cv_image) {
  std::vector<cv::Rect> new_faces;
  std::vector<cv::Rect> new_eyes;
  
  /* face & eye detection */
  if (ui->faceDetectionCheckBox->isChecked()) {
    DetectMultiscaleParam face_params = getFaceDetectionParams();
    new_faces = haarcascade_face_detection(cv_image, face_params);
    setFaces(new_faces);
  }
  if (ui->eyesDetectionCheckBox->isChecked()) {
    DetectMultiscaleParam eyes_params = getEyesDetectionParams();
    new_eyes = haarcascade_eye_detection(cv_image, eyes_params);
  }

  if (ui->pixelateFaceCheckBox->isChecked()) {
    //cv_image =
    pixelate_image(cv_image, new_faces);
  }

  /* drawing faces and eyes as rectangle in cv_image */
  if (ui->faceDetectionCheckBox->isChecked()) {
    cv::Scalar red( 0, 0, 255 );
    draw_rectangle_in_image(cv_image, new_faces, red);
  }
  if (ui->eyesDetectionCheckBox->isChecked()) {
    cv::Scalar blue( 255, 0, 0 );
    draw_rectangle_in_image(cv_image, new_eyes, blue);
  }
  cv::Mat cv_scaled_image = scaledImageToConstrains(cv_image,label_width,label_height, scale_factor_width, scale_factor_height);
  QImage qt_image = QImage(static_cast<uchar*>(cv_scaled_image.data), cv_scaled_image.cols, cv_scaled_image.rows, cv_scaled_image.step, QImage::Format_BGR888);
  QPixmap vidPixmap = QPixmap::fromImage(qt_image);
  ui->videoLabel->setPixmap(vidPixmap);
}

void VideoFaceDetection::saveImage(const QString &fileName) {
  cv::Mat image_to_write = getLastImage();
  if(image_to_write.empty())
  {
    std::cerr << "Something is wrong with last image, could not get frame." << std::endl;
  }
  cv::imwrite(fileName.toStdString(), image_to_write);
}

void VideoFaceDetection::onSlide( int pos) {
  // get opencv image on that opsition
  cv::Mat frame;
  cap.set( cv::CAP_PROP_POS_FRAMES, pos);
  cap >> frame;
  setLastImage(frame.clone());
  setImage(frame);
}

void VideoFaceDetection::onChangeFacedetection() {
  if (video_loaded) {
    cv::Mat frame;
    frame = getLastImage();
    setImage(frame);
  }
}

void VideoFaceDetection::onChangePixelateFace() {
  if (video_loaded) {
    cv::Mat frame = getLastImage();
    setImage(frame);
  }
}

void VideoFaceDetection::setLastImage(cv::Mat image) {
  last_image = image;
}

cv::Mat VideoFaceDetection::getLastImage() {
  return last_image.clone();  
}


void VideoFaceDetection::cropVideoImage() {
  selectedFacesListModel->append(last_image);  
}

DetectMultiscaleParam VideoFaceDetection::getFaceDetectionParams() {
  DetectMultiscaleParam params;
  params.scaleFactor = ui->scaleFactorTextEdit->toPlainText().toDouble();
  params.minNeighbors =ui->minNeighborsTextEdit->toPlainText().toInt();
  params.flags = cv::CASCADE_FIND_BIGGEST_OBJECT | cv::CASCADE_SCALE_IMAGE;
  params.minSize = cv::Size(ui->minSizeXTextEdit->toPlainText().toInt(),
                            ui->minSizeYTextEdit->toPlainText().toInt());
  params.maxSize = cv::Size(ui->maxSizeXTextEdit->toPlainText().toInt(),
                            ui->maxSizeYTextEdit->toPlainText().toInt());
  params.outputRejectLevels = false;
  return params;
}

DetectMultiscaleParam VideoFaceDetection::getEyesDetectionParams() {
  DetectMultiscaleParam params;
  params.scaleFactor = ui->scaleFactorTextEdit_2->toPlainText().toDouble();
  params.minNeighbors =ui->minNeighborsTextEdit_2->toPlainText().toInt();
  params.flags = cv::CASCADE_FIND_BIGGEST_OBJECT | cv::CASCADE_SCALE_IMAGE;
  params.minSize = cv::Size(ui->minSizeXTextEdit_2->toPlainText().toInt(),
                            ui->minSizeYTextEdit_2->toPlainText().toInt());
  params.maxSize = cv::Size(ui->maxSizeXTextEdit_2->toPlainText().toInt(),
                            ui->maxSizeYTextEdit_2->toPlainText().toInt());
  params.outputRejectLevels = false;
  return params;
}

void VideoFaceDetection::getFaceAtPos(int x, int y) {
  int p_x = static_cast<int>(x / scale_factor_width);
  int p_y = static_cast<int>(y / scale_factor_height);
  cv::Mat face_image;
  bool success = cut_selecteced_rectangle_from_image(last_image, face_image, p_x, p_y, faces ); 
  if(success)
    selectedFacesListModel->append(face_image);
}

void VideoFaceDetection::setFaces(std::vector<cv::Rect> &new_faces) {
  this->faces.clear();
  this->faces.insert(faces.end(), new_faces.begin(), new_faces.end());
}

void VideoFaceDetection::clearFaces() {
  this->faces.clear();  
}

