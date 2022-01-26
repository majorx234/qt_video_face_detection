#ifndef IMAGE_LIST_MODEL_HPP
#define IMAGE_LIST_MODEL_HPP
#include "image_item.hpp"

#include <vector>
#include <qt/QtCore/QAbstractListModel>

class ImageListModel : public QAbstractItemModel {
  Q_OBJECT
 public:
  ImageListModel(QObject* parent = 0);
  int rowCount(const QModelIndex& parent = QModelIndex()) const;
  int columnCount(const QModelIndex& parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role) const;
  void populate();
  void append(cv::Mat cv_image);
  std::vector<ImageItem> list;
};


#endif // IMAGE_LIST_MODEL_HPP
