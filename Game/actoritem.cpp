#include "actoritem.hh"

ActorItem::ActorItem(int x, int y, int type, const std::shared_ptr<QImage> icon, std::shared_ptr<Interface::IActor> actor)
    :CourseSide::SimpleActorItem{x,y,type}
{ 
    icon_ = icon;
    actor_ = actor;
}

void ActorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //Ei piirretä matkustajia
    if (std::dynamic_pointer_cast<CourseSide::Passenger>(actor_) == 0)
    {
        QRectF bounds = boundingRect();
        QBrush brush;
        if(icon_== nullptr)
        {
            brush = Qt::black;
            painter->setBrush(brush);
            painter->drawEllipse(bounds);
        }
        else
        {
            painter->drawImage(bounds, *icon_);
        }
    }
}

void ActorItem::updateCoords()
{
    if(actor_ != nullptr)
    {
        Interface::Location loc = actor_->giveLocation();
        setCoord(loc.giveX(),loc.giveY());
    }
}



