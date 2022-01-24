#include "qclicklabel.hpp"

QClickLabel::QClickLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {
    
}

QClickLabel::~QClickLabel() {}

void QClickLabel::mousePressEvent(QMouseEvent* event) {
    emit clicked();
}
