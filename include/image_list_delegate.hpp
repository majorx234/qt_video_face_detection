#ifndef IMAGE_LIST_DELEGATE_HPP
#define IMAGE_LIST_DELEGATE_HPP

#include <QStyledItemDelegate>
#include <QEvent>

class ImageListDelegate : public QStyledItemDelegate {
  Q_OBJECT
 public:
  ImageListDelegate(QObject * patent = nullptr);

  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
  QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;      
  bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
 signals:
  void on_clicked(int, Qt::MouseButton);
};

#endif // IMAGE_LIST_DELEGATE_HPP
