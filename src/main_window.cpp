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

  return true;
}

void MainWindow::createMenuBar()
{
  QMenu *fileMenu;
  QAction *openAct;

  openAct = new QAction(tr("&Open"), this);
  openAct->setShortcuts(QKeySequence::New);
  openAct->setStatusTip(tr("Create a new file"));
  connect(openAct, &QAction::triggered, this, &MainWindow::open);
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(openAct);
}

void MainWindow::createStatusBar()
{

}

bool MainWindow::saveFile(const QString &fileName)
{
  return true;
}

