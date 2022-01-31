#include "image_list_model.hpp"
#include <QDebug> 

ImageListModel::ImageListModel(QObject *parent)
    : QAbstractItemModel(parent) {
}

ImageListModel::~ImageListModel() {
  for(auto const& item: list) {
    delete item;
  }
}

int ImageListModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return list.size();
}


int ImageListModel::columnCount(const QModelIndex &parent ) const {
  if (list.size() > 0)
    return 1;
  return 1;
}

QVariant ImageListModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= list.size())
    return QVariant();
  if ( role != Qt::DisplayRole )
    return QVariant();
  int list_index = index.row();
  ImageItem* image_item = list[list_index];
  QVariant v;
  v.setValue(image_item);
  return v;  
}

QModelIndex ImageListModel::index(int row, int column, const QModelIndex& parent) const {
  return hasIndex(row, column, parent) ? createIndex(row, column, nullptr) : QModelIndex();
}  
QModelIndex ImageListModel::parent(const QModelIndex& child) const {
  Q_UNUSED(child);
  return QModelIndex();
}

void ImageListModel::append(cv::Mat cv_image) {
  ImageItem* new_item = new ImageItem();
  new_item->set_image(cv_image);
  //connect(new_item,SIGNAL(valueChanged()),SLOT(dataChanged()));
  list.push_back(new_item);
  int list_index = list.size()-1;
  QModelIndex index = createIndex(list_index, 0, new_item);
  emit dataChanged(index, index, {Qt::EditRole});
  int row = index.row();
  int column = index.column();
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

Qt::ItemFlags ImageListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return {};
    return QAbstractItemModel::flags(index);
}
