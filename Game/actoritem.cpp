#include "actoritem.hh"

ActorItem::ActorItem(int x, int y, int type, QString iconPath)
    :CourseSide::SimpleActorItem{x,y,type}
{ 
    iconPath_ = iconPath;
}

void ActorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF bounds = boundingRect();
    QColor color;
    QBrush brush;

    if(iconPath_.isEmpty())
    {
        brush = Qt::black;
    }
    else
    {
        QPixmap icon(iconPath_);
        brush = icon;
    }

    painter->setBrush(brush);
    painter->drawEllipse(bounds);
}



