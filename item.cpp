#include "item.h"
#include <QDebug>

Item::Item(unsigned int m, unsigned int v)
{
    multiplicity = m;
    value = v;
}

void Item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit callback(multiplicity, value);
    lastBrush = this->brush();
    this->setBrush(Qt::white);
}

void Item::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setBrush(lastBrush);
}
