#include "image_list_model.hpp"

ImageListModel::ImageListModel(QObject *parent) {
  
}

int ImageListModel::rowCount(const QModelIndex &parent) const {
  return list.size();
}

int ImageListModel::columnCount(const QModelIndex &parent ) const {
  return 0;
}

QVariant ImageListModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= list.size())
    return QVariant();
  if ( role != Qt::DisplayRole )
    return QVariant();
  ImageItem image_item = list[index.row()];
  QVariant v;
  v.setValue(image_item);
  return v;  
}

void ImageListModel::populate() {
  
}
