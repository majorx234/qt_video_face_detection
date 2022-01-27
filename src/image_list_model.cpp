#include "image_list_model.hpp"
#include <QDebug> 

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
  int list_index = index.row();
  qDebug() << "ImageListodel::data: list_index: " << list_index;
  ImageItem* image_item = list[list_index];
  QVariant v;
  v.setValue(image_item);
  return v;  
}

void ImageListModel::populate() {
  
}

QModelIndex ImageListModel::index(int a, int b, const QModelIndex& foo) const {
  return foo;
}  
QModelIndex ImageListModel::parent(const QModelIndex& foo) const {
  return foo;
}

void ImageListModel::append(cv::Mat cv_image) {
  ImageItem* new_item = new ImageItem();
  new_item->set_image(cv_image);
  // connect(new_item,SIGNAL(valueChanged()),SLOT(dataChanged()));
  list.push_back(new_item);
  int list_index = list.size() - 1;
  qDebug() << "ImageListodel::data: list_append: " << list_index;
  QModelIndex index = createIndex(list_index, 0, new_item);
  emit dataChanged(index,index, {Qt::EditRole});
}

void ImageListModel::data_changed(ImageItem* item, const QModelIndex &index) {
  QVariant v;
  v.setValue(item);
  setData(index, v, Qt::EditRole);
}

bool ImageListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
  QAbstractItemModel::setData(index,value,role);
  QVariant data = index.data();
  ImageItem* item = data.value<ImageItem*>();
  emit dataChanged(index, index, {Qt::EditRole});
  return true;
}
