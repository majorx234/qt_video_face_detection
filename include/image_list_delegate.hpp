#include <QStyledItemDelegate>

class ImageListDelegate : public QStyledItemDelegate {
  Q_OBJECT
 public:
  ImageListDelegate(QObject * patent = nullptr);
  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index);
  QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;      
};
