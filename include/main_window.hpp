/* 
 * This file is part of the rtaudio_example distribution (https://github.com/majorx234/rtaudio_example ).
 * Copyright (c) 2021 Majorx234
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAIN_WINDOW_HPP 
#define MAIN_WINDOW_HPP

#include <QtWidgets/QMainWindow>

#include "video_face_detection.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow();

  void loadFile(const QString &fileName);

signals:
  void closed();  
protected:
  void closeEvent(QCloseEvent *event) override;
  void resizeEvent(QResizeEvent* event) override;
private slots:
  void newFile();
  void open();
  bool save();
  void close();

private:
  void createMenuBar();
  void createStatusBar();
  bool saveFile(const QString &fileName);
  VideoFaceDetection* main_video_widget;

};        

#endif // MAIN_WINDOW_HPP
