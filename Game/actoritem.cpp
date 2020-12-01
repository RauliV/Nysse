#include "actoritem.hh"

ActorItem::ActorItem(int x, int y, int type)
    :CourseSide::SimpleActorItem{x,y,type}
{

}

void ActorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF bounds = boundingRect();
    QColor color;
    QPixmap icon(":/graphics/walk_or_passenger_icon.png");
    QBrush brush(icon);
    painter->setBrush(brush);
    painter->drawEllipse(bounds);
}


