#include "actoritem.hh"

ActorItem::ActorItem(int x, int y, int type, QString iconPath, std::shared_ptr<Interface::IActor> actor)
    :CourseSide::SimpleActorItem{x,y,type}
{ 
    iconPath_ = iconPath;
    actor_ = actor;
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

void ActorItem::updateCoords()
{
    if(actor_ != nullptr)
    {
        Interface::Location loc = actor_->giveLocation();
        setCoord(loc.giveX(),loc.giveY());
    }
}



