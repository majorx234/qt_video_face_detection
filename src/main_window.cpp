#include <QtWidgets>

#include "main_window.hpp"
#include "video_face_detection.hpp"

MainWindow::MainWindow()
    : main_video_widget(new VideoFaceDetection(this))
{
  setGeometry( 100, 100, 935, 650 );
  setCentralWidget(main_video_widget);
}

void MainWindow::loadFile(const QString &fileName)
{

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

}
bool MainWindow::save()
{

}

void MainWindow::createMenuBar()
{

}

void MainWindow::createStatusBar()
{

}

bool MainWindow::saveFile(const QString &fileName)
{

}
