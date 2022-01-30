#ifndef IMAGE_LIST_MODEL_HPP
#define IMAGE_LIST_MODEL_HPP

#include <QAbstractListModel>
#include <vector>
#include "image_item.hpp"

class ImageListModel : public QAbstractItemModel {
  Q_OBJECT
 public:
  explicit ImageListModel(QObject* parent = 0);
  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QModelIndex index(int, int, const QModelIndex&) const override;
  QModelIndex parent(const QModelIndex&) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
  void populate();
  void append(cv::Mat cv_image);
  std::vector<ImageItem*> list;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
 public slots: 
  void data_changed(ImageItem* item, const QModelIndex &index);
};


#endif // IMAGE_LIST_MODEL_HPP
