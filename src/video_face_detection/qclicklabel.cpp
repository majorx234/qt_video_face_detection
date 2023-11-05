#include "qclicklabel.hpp"
#include <QMouseEvent>

QClickLabel::QClickLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {
    
}

QClickLabel::~QClickLabel() {}

void QClickLabel::mousePressEvent(QMouseEvent* event) {
  switch(event->button()) 
  {
    case Qt::MouseButton::LeftButton: {
          int x = event->x();
          int y = event->y();
          emit clicked(x, y);
          break;}
    case Qt::MouseButton::RightButton: {
      break;
    }
  }
}
