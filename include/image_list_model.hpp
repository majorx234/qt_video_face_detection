#ifndef IMAGE_LIST_MODEL_HPP
#define IMAGE_LIST_MODEL_HPP

#include <QAbstractListModel>
#include <vector>
#include "image_item.hpp"

class ImageListModel : public QAbstractItemModel {
  Q_OBJECT
 public:
  explicit ImageListModel(QObject* parent = 0);
  int rowCount(const QModelIndex& parent = QModelIndex()) const;
  int columnCount(const QModelIndex& parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role) const;
  QModelIndex index(int, int, const QModelIndex&) const;
  QModelIndex parent(const QModelIndex&) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
  void populate();
  void append(cv::Mat cv_image);
  std::vector<ImageItem*> list;
 public slots: 
  void data_changed(ImageItem* item, const QModelIndex &index);
};


#endif // IMAGE_LIST_MODEL_HPP
