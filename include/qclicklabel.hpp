#ifndef QCLICKLABEL_HPP
#define QCLICKLABEL_HPP

#include <QLabel>
#include <QWidget>
#include <Qt>

class QClickLabel : public QLabel { 
    Q_OBJECT 

public:
    explicit QClickLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~QClickLabel();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // QCLICKLABEL_HPP

