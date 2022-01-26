#include <QStyledItemDelegate>
#include <QEvent>

class ImageListDelegate : public QStyledItemDelegate {
  Q_OBJECT
 public:
  ImageListDelegate(QObject * patent = nullptr);
  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index);
  QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;      
  bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
 signals:
  void on_clicked(int, Qt::MouseButton);
};
