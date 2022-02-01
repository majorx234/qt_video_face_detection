#include "image_list_delegate.hpp"
#include <QPainter>
#include <QMouseEvent>
#include "image_item.hpp"

#include <QDebug> 

ImageListDelegate::ImageListDelegate(QObject *patent)
    : QStyledItemDelegate() {
  
}

void ImageListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
  QVariant data = index.data();
  ImageItem* item = data.value<ImageItem*>();
  if (data.canConvert<ImageItem*>()) {
    painter->save();
    cv::Mat cv_thumbnail = item->get_thumbnail().clone();
    QImage qt_thumbnail = QImage((uchar*)cv_thumbnail.data, cv_thumbnail.cols, cv_thumbnail.rows, cv_thumbnail.step, QImage::Format_BGR888);
    painter->drawImage(option.rect.left(), option.rect.top(),qt_thumbnail);
    painter->restore();
  }
}

QSize ImageListDelegate::sizeHint(const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const {
  QVariant data = index.data();
  int row = index.row();
  int column = index.column();
  if (data.canConvert<ImageItem*>()) {
    ImageItem *item = data.value<ImageItem*>();
    int height = item->get_thumbnail().rows;
    int width = item->get_thumbnail().cols;
    return QSize(width,height);
  }
  return QSize();
}

bool ImageListDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) {
  if (!index.isValid()) {
        return false;
  }
  
  if (event->type() == QEvent::MouseButtonPress) {
    auto mouseEvent = static_cast<QMouseEvent*>(event);
    Qt::MouseButton button = mouseEvent->button();
    int item_index = index.row();
    emit on_clicked(item_index,button);
  }
  return true;  
}
