#include <string>
#include <QtWidgets>

#include "main_window.hpp"
#include "video_face_detection.hpp"

MainWindow::MainWindow()
    : main_video_widget(new VideoFaceDetection(this))
{
  setGeometry( 100, 100, 980, 780 );
  setCentralWidget(main_video_widget);
  createMenuBar();
}

void MainWindow::loadFile(const QString &fileName) {
  this->main_video_widget->loadVideo(fileName);
}

void MainWindow::closeEvent(QCloseEvent *event) 
{
   QMainWindow::closeEvent(event);
     if (event->isAccepted())
        emit closed();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	QMainWindow::resizeEvent(event);
}

void MainWindow::newFile()
{

}

void MainWindow::open()
{
  QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open Video"), "~", tr("Video Files (*.mp4)"));
  if (!fileName.isEmpty()) {
        loadFile(fileName);
    } 
}
bool MainWindow::save()
{
  QString fileName = QFileDialog::getSaveFileName(this, tr("Open Video"),  "~", tr("Jpeg (*.jpg)"));
  if (!fileName.isEmpty()) {
        saveFile(fileName);
    }
  return true;
}

void MainWindow::close() {
  QMainWindow::close();    
}

void MainWindow::createMenuBar()
{
  QMenu *fileMenu;
  QAction *openAct;
  QAction *saveAct;
  QAction * exitAct;
  
  openAct = new QAction(tr("&Open"), this);
  openAct->setShortcuts(QKeySequence::New);
  openAct->setStatusTip(tr("Create a new file"));
  connect(openAct, &QAction::triggered, this, &MainWindow::open);
  saveAct = new QAction(tr("&Save"), this);
  saveAct->setShortcuts(QKeySequence::New);
  saveAct->setStatusTip(tr("Save Image"));
  connect(saveAct, &QAction::triggered, this, &MainWindow::save);
  exitAct = new QAction(tr("&Exit"), this);
  exitAct->setShortcuts(QKeySequence::New);
  exitAct->setStatusTip(tr("Exit Program"));
  connect(exitAct, &QAction::triggered, this, &MainWindow::close);
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(openAct);
  fileMenu->addAction(saveAct);
  fileMenu->addAction(exitAct);
}

void MainWindow::createStatusBar()
{

}

bool MainWindow::saveFile(const QString &fileName)
{
  this->main_video_widget->saveImage(fileName);
  return true;
}

