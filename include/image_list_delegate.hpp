#include <QStyledItemDelegate>

class ImageListDelegate : public QStyledItemDelegate {
  Q_OBJECT
 public:
  ImageListDelegate(QObject * patent = nullptr);
};
