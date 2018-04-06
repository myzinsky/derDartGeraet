#ifndef SINGLEITEM_H
#define SINGLEITEM_H

#include <QGraphicsEllipseItem>
#include <qDebug>
#include <QBrush>

class Item : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Item(unsigned int m, unsigned int v);
    void virtual mousePressEvent(QGraphicsSceneMouseEvent *event);
    void virtual mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void callback(unsigned int m, unsigned int v);
private:
    unsigned int multiplicity;
    unsigned int value;
    QBrush lastBrush;
};

#endif // SINGLEITEM_H
